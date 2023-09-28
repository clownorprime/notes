##进程和线程
OS调度的基本单位就是线程，线程需要以进程作为容器和使用进程相关的环境，所以应用态线程不能脱离开进程

我们可以通过fork函数来创建一个进程，而操作系统同时又会为我们创建一个Main thread, 我们可以调用pthread\_create接口来创建一个worker thread.

进程中的每个线程共享进程的代码段、数据段和堆。
共享代码段，因此每个线程都能够调用任何函数
共享数据段，因此每个线程都能够调用任何全局变量
共享堆，所以我们可以在一个线程访问另外一个线程malloc/new出来的内存对象。

每个线程都有自己独立了的栈空间，所以可以独立调用执行函数而不受影响.

CPU调度的基本单位是线程，如果两个线程之间是属于不同的进程，那么这时候线程调度也可以称为进程切换.

## 进程同步方式
1. 匿名管道
通过匿名管道可以实现进程间的通信，不过这种通信必须建立在两个进程是父子关系.
2. 有名管道
有名管道(FIFO)和匿名管道的区别在于匿名管道之间的通信要求进程间是父子关系，而有名管道没有这项要求，我们可以用mknod来创建一个有名管道, 然后该进程可以通过该有名管道的文件名创建一个文件描述符，然后使用write函数调用向这个有名管道中写数据，其他进程可以通过这个文件名打开有名管道，从而实现进程间的通信。另外，有名管道和匿名管道都是半双工的，要实现双全工，可以创建两个管道.
3. 消息队列
消息队列相对于管道的优点在于对每个消息可以指定特定的消息类型，在接受的时候可以根据自定义条件接受特定类型的消息，不需要按照队列排队.
4. 共享内存
共享内存是最快的IPC方式，管道和消息队列的实现过程为服务器端从文件中读取数据到用户空间，然后再将数据写到内核，然后客户端从内核中读取数据到用户空间，再将数据从用户空间写到文件中。而共享内存，由于两个或者多个进程共享了同一块内存区域，这意味着他们的虚拟内存地址被映射到了同一块物理内存区域，因此，这里的数据只复制两次，一次从服务器端的文件复制到共享内存区，另一次从共享内存区复制到客户端的文件中。
5. 信号量
与前几个同步机制不同，前几个机制只能实现进程的同步或者说协作关系，而信号量既能实现进程的同步机制又可以实现进程的互斥关系. 一个经典的例子是生产者和消费者问题，其解决方法可以是：
semaphore mutex = 1;
semaphore empty = n;
semaphore full = 0;

producer() {
    while(1) {
        p(empty);
        p(mutex);
        .. // write the data into the queue.
        v(mutex);
        v(full);
    }
}

consumer() {
    while(1) {
        p(full);
        p(mutex);
        .. // read the data in the queue.
        v(mutex);
        v(full);
    }
}

这里p(full)和p(mutex)以及p(empty)、p(mutex)的顺序不能颠倒，否则会引发死锁问题。假设empty = 0; full = n;调换p(mutex)和p(empty)，那么producer会阻塞与p(empty)，而consumer会阻塞与p(mutex),引发死锁.

## 线程间同步方式
1. mutex(互斥锁)
2. 读写锁
互斥锁只有两种状态，lock和unlock, 而读写锁有三种状态，lock in write, lock in read and unlock.

如果一个线程持有写锁，那么其他线程尝试获取读锁或者写锁都会阻塞；如果一个线程持有读锁，那么其他线程尝试获取写锁会阻塞，但读锁并不会阻塞.

读写锁的使用场景，读多写少的场合。
3. spinlock
旋转锁和互斥锁的区别在于，互斥锁如果发生阻塞，这时就会发生线程调度，CPU执行其他线程。而旋转锁不同，如果发生阻塞，则不停的占据CPU，直到可以获得锁。旋转锁使用的场景是：锁在很短的时间可以获得，且该线程的优先程度较高，不能承受被调度的损失。
spinlock一般可以用于实现互斥锁扽等锁.
4. 条件变量
条件变量主要用于线程的同步，也就是通信，而不是为了线程的互斥。条件变量经常和互斥锁同时使用，是为了弥补互斥锁在线程通信方面的不足，因为互斥锁只有两种状态，锁和非锁，而条件变量的使用可以使一个线程向另外一个线程发送信号，因此，条件变量其实可以用在这种场景下：一个线程执行到某个时间节点，必须要等待其他线程执行. 其实，这也是barrier所要做的事情，所以我们可以通过条件变量来实现barrier.
5. barrier（屏障）
barrier和pthread\_join函数的区别在于，pthread\_join函数会一直阻塞，直到相应线程退出。而barrier会一直阻塞，直到一定数目的线程都运行到了barrier\_wait, (我们可以把barrier\_wait放置在线程的start\_routine中)，然后这几个线程再重新从barrier\_wait之后运行.
使用场景：多个线程等待同一个事情结束在这之后再一起运行.

## 死锁
### 可能出现的原因
1.  同一个进程持有一把锁，然后又尝试获取该把锁
2.  有两个进程和两把锁，一个进程持有锁a, 请求锁b, 另外一个进程持有锁b, 请求锁a
### 避免的方式
1. 合理的安排锁获取的顺序，比如同时有两把锁，必须要先获取锁a，才能获取锁b
2. 当锁的个数过多时，保持锁获取的顺序不是一件简单的事情，因此，我们可以使用pthread\_mutex\_trylock和pthread\_mutex\_timedlock函数，当多次尝试获取一把锁都不能成功时，我们可以尝试释放自身目前持有的锁，然后过一段时间再次尝试.

### 线程状态
线程有可结合和可分离两种状态
在默认状态下，线程是可结合的，即只有当pthread\_join函数返回时，创建的线程才算终止，线程所占据的资源才能被释放.

而我们可以使用pthread\_attr\_setdetachstate函数设为某一个线程为可分离状态，即线程调用exit函数或者return返回时，线程马上终止，持有的资源立马会被释放.