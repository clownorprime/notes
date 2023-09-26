## chapter19

###UDP报文可能会丢失、重复、乱序
###UDP缺乏流量控制
###UDP协议报文被截断
这意味着如果接收端程序定义的缓冲区大小小于发动端消息的大小，那么此时报文消息就会被截断，例如消息本身为"ABCD", 缓冲区大小为2，那么接收端接收到的消息为"AB"，剩余的消息都会被截断。
###recvfrom返回0，不代表连接关闭，因为udp是无连接的
###ICMP异步错误与UPD connect
由于UDP是无连接的，不会维护连接的状态，sendto函数仅仅将buffer的数据复制到sockfd的缓冲区内；而假设服务器端程序尚未打开，而客户端首先运行时，sendto函数中的参数servaddr不存在，此时sendto函数也不会返回-1, 而是返回已复制的字节的数目。客户端程序会阻塞于recvfrom函数，而sendto函数却不会出现错误，这是一种ICMP异步错误。

tcp/ip规定异步错误不能返回给未连接套接字, 所以我们要使得ICMP错误能够被recvfrom函数识别出，就要使用connect函数, 即UDP connect.
###UDP外出接口的确定
假设客户端有多个ip地址，那么怎样确定其与服务器端通信的ip地址呢？规则在于同一子网优先，即客户端的ip地址尽可能应与服务器端的ip地址位于同一子网之中。

## chapter20 unix域编程
### unix域编程特点
1. unix域往往用来本机之间进行传输，而TCP套接字即可以用来本机之间传输，也可以用来不同网络之间传送数据。unix域在同一台主机上传输速度是TCP套接字的两倍
2. unix域套接字可以在同一台主机上个进程之间传递描述符
3. unix域协议字与传统的套接字的区别是用路径名来表示协议族的描述
###  unix域编程注意事项
1. bind成功之后会创建一个文件，即servaddr.sun\_path， 该文件的权限为0777&umask
2. sun\_path应该定义为一个绝对路径，否则若客户端和服务器端不在同一个目录时，connect会报错
3. unix域协议支持流式套接字和报式套接字
4. unix域流式套接字connect发现监听队列满时，会立即返回一个ECONNECTFUSED, 这与TCP不同，TCP会忽略SYN, 导致对方重发SYN

## chapter21 unix域套接字传递文件描述符
通过fork创建的子进程能够共享父进程的文件描述符，但父进程能不能够共享子进程的文件描述符呢。答案是可以的，可以通过建立unix域套接字并使用recvmsg和sendmsg来实现, 普通的套接字如TCP套接字、UDP套接字不能用于传递文件描述符。

### socketpair
socketpair函数有些类似于named pipe(命名管道），命名管道是半双工的，只能用于亲缘关系的进程进行通信，如父子进程、兄弟进程等, 因为该管道是没有名称的，父子进程可以通过共享文件描述符的方式来实现通信。

而socketpair是一个双全工的管道，既可以读也可以写。

至于如何通过unix域套接字和recvmsg、sendmsg来实现进程之间传递文件描述符，可以查看chapter21的代码，辅助以UNP chapter14.6加以理解。