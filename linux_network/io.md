# P13 - p20
## 五种I/O模型
阻塞I/O
非阻塞I/O
I/O复用(select和poll)
信号驱动I/O
异步I/O

### 阻塞I/O
直到满足某种特定条件时，才解除阻塞, 一般来说，对于read来说，特定条件表示内核缓冲区内存在数据；对于write来说，该条件表明内核缓冲区内有多余空间可写。

一旦满足特定条件时，read/recv函数就会把数据从内核空间即套接口接受缓冲区内拷贝数据到用户定义的buffer中，一旦拷贝完成，recv函数就返回。

### 非阻塞I/O
可以用fcntl(fd, F\_SETFL, flag | ONONBLOCK)将套接口设置为非阻塞模式。那么这个时候，即使没有内核缓冲区即套接口接收缓冲区内即使没有数据，recv/read函数也不会阻塞，会返回一个错误，errno == EWOULDBLOCK， 返回值为-1，这时候，应该重新调用recv函数，判断其是否返回-1，如果还等于-1，那么继续调用recv函数，直至内核缓冲区内有数据，recv就将数据从内核空间拷贝到用户空间。进而进行用户空间的操作。

非阻塞I/O不常用，原因在于非阻塞I/O将会一直运行，直至有数据到来，是一种忙等待，对CPU的浪费。

### I/O复用
主要通过select来实现，使用select来管理多个文件描述符，一旦其中的一个文件描述符或多个文件描述符满足了相应条件，select函数就返回,那么这个时候就可以使用recv等I/O函数而不必阻塞。实际上这里阻塞的位置提前到了select函数。

### 信号驱动I/O
这种模型也不经常使用。
首先建立一个SIGIO的信号处理程序，即调用signal或者sigaction函数来安装SIGIO信号处理程序，程序就可以处理其他任务，一旦有数据到来，就以信号形式通知给进程处理SIGIO，然后我们就可以在信号处理程序中调用recv等函数，此时recv等I/O函数并不会阻塞。

### 异步I/O
效率最高
使用aio\_read函数来实现，这个函数提交一个请求，并提供一个缓冲区，即使不满足特定条件，该函数也不会阻塞，也是可以继续执行其他的任务。当有数据到来，内核就会自动将该数据从内核空间即内核接收缓存区拷贝到用户空间，然后以信号形式通知应用进程的程序，然后应用进程程序处理该数据。

这一种模型和信号驱动模型区别在于，异步I/O模型在得到信号，这时内核已经将主动将数据从内核拷贝到用户空间，这时用户空间可以直接使用该数据, 用户空间没有必要使用recv等函数从内核接收数据。因此，异步I/O模型效率最高。

因此，我们可以说异步I/O是推的机制，由内核将数据推过来，而信号驱动I/O是拉的机制，需要主动使用recv函数将数据从内核来到用户空间。

异步I/O没有得到很好的推广，是因为aio\_read函数完成始终有些问题。


## select
并发指的是在一个时间段内由多个程序在运行，而并行指的是同一个时刻有多个程序在运行。
我们通常将使用select实现的服务器称为并发服务器, 我们通过select函数检测到多个事件发生时，我们是一个一个的处理这些事件，因此，我们的处理是并发的，而不能做到并行，实际上在单核处理器中做不到真正的并行。 

### select读、写、异常事件发生条件
#### 可读
1. 套接字缓存区中有数据可读
2. 连接套接字的读一半关闭，即接收到FIN段，读操作将返回0   // readline 函数返回0
3. 如果是监听套接字，已完成连接队列不为空时
4. 套接口上发生了一个错误待处理
#### 可写
1. 套接口发送缓冲区有数据可写
2. 连接的写一半关闭。即收到RST段之后，再次调用write操作
3. 套接口上发生了一个错误待处理。

### 异常
套接口存在带外数据（紧急数据）


## chapter15
###close与shutdown函数
若将tcp看作是一个全双工的管道，那么close同时关闭读管道和写管道，而shutdown是可选的，可以只关闭读管道，只关闭写管道，也可以同时关闭读管道和写管道。

shutdown函数的用途，考虑一个echo服务器，先后收到了AAAA、BBBB、CCCC以及FIN(代表客户端使用close关闭通信套接字), 我们想把AAAA、BBBB、CCCC写回到客户端，但是客户端使用close函数会关闭通信套接字，无法写入AAAA，BBBB，CCCC（假设服务器在接收数据后并不立即写回，可使用sleep函数).强制写入会收到RST及SIGPIPE信号等.

那么这个时候，我们想要写回AAAA,BBBB, CCCC, 我们可以使用shutdown函数关闭客户端通信套接字的写功能，保留其接收功能。

close与shutdown函数的具体区别在于：
1. close终止了数据传送的两个方向
2. shutdown可以有选择的终止某个方向上的数据。
3. 当通信描述符由于fork等原因，存在多个引用计数时，close并不意味着发送一个FIN报文段到目的端口，而仅仅将引用计数减一，仅当引用计数变为0时，才会发送FIN报文段。而shutdown不存在此项限制，发送FIN报文段到目的端口，使read函数返回0. 

## chapter16
###套接字超时设置方法
1.使用alarm函数
2. 使用套接字选项，SO\_RCVTIMEO
3. 使用select函数的第三个参数

## chapter17
### select限制
select实现的并发服务器，能达到的并发数，受到两方面限制：
1. 一个进程所能打开的文件描述符数量，可以通过ulimit -n来设置
2. select中的fd\_set集合的容量限制(FD\_SETSIZE), 要更改只能重新编译内核

在这个限制下，服务器端最多能连接的通信套接字的个数为1024-3-1(3代表0，1，2； 1代表监听套接字）， 而客户端能建立的最多的通信套接字的个数为1024-3 = 1021.

我们可以通过poll函数来增大上面的数字，具体操作方法见man poll及17章源码

## chapter18
### epoll
poll只受到一个限制：一个进程可以打开的文件描述符的数量。

poll和select的共同点在于内核需要遍历所有感兴趣的描述符，直到找到发生事件的文件描述符。
随着感兴趣描述符的不断增加， I/O效率就会下降，有时甚至呈指数形式下降。

这可以通过epoll来使用，epoll相对于select和poll而言，不会因监听fd数目的增加而效率降低，原因在于：
1. 在内部实现上来说，select和poll的实现是基于轮询来实现的，select的轮询目标是第一个参数maxfd, 而poll的轮询目标是第二个参数nfds.而epoll的实现是基于回调的，如果fd中有期望的事件发生，就将其通过回调函数加入epoll就绪队列，即它只关心活跃的fd, 与fd的数目无关。
2. 内核/用户空间拷贝问题，如何让内核把消息通知给用户空间？在这个问题上select/poll采用了内存拷贝的方法，而epoll则采用了共享内存的方法。
3. 应用程序代码问题，select和poll必须要遍历整个fd集合，才能定位到相应的事件，而epoll不仅能够告诉应用程序事件的到来，还能告诉应用程序相关的信息，是通过结构体epoll\_event来实现。

### epoll模式(EPOLLLT和EPOLLET)
EPOLLLT：电平触发模式
EPOLLET: 边缘触发模式

EPOLLET:
    触发只发生在fd由空闲变为就绪状态；假设pipe writer发送了2KB的数据，接收端只读了1KB数据，fd在之后一直处于就绪状态，从而从EPOLL队列中删除，无法再次触发，直到应用程序通过读写操作触发EAGAIN状态，epoll就会认为这个fd又变为了空闲状态。那么epoll就会重新关注这个fd的状态变化。而EPOLLLT模式，只要事件没有处理完，就会触发，因此，LT模式触发的次数更多，效率相对较低。
    边缘触发模式推荐采用的方式：
    1. 采用非阻塞的文件描述符(这里为什么?)
    2. 读完之后触发一个EAGAIN, 表示数据全部都读完了。

综上：如果没有处理完全部的事务，那么调用epoll就有可能出现问题。
