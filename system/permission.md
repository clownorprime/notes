## 关于权限
### 进程权限
一般情况下，某个进程的uid,gid在整个会话期间都不会发生改变
而euid通常等于进程的uid,但是
### 文件权限
新文件的uid等于进程的euid, 例如在shell中使用touch命令创建一个文件，那么该文件的uid等于shell的euid.
而新文件的gid则取决于具体的实现，POSIX.1规定，新文件的guid的设置有以下两种情况:
1. 新文件的gid等于进程的egid
2. 新文件的gid等于所在目录的gid.
### 进程访问文件
某个进程是否能够访问某个文件取决于进程的有效ID,有效组ID,附属组ID,以及文件的所有者(st\_uid, st\_gid).
1. 若某个进程的有效ID等于0（超级用户），那么允许访问该文件。
2. 若某个进程的有效ID等于文件的uid, 那么如果所有者适当的访问权限被设置，那么则允许访问。
3. 若某个进程的有效组ID或者附属组ID等于文件的组ID, 那么如果所有者适当的访问权想被设置，那么允许访问
3. 若其他用户的适当访问权限被设置，则允许访问，否则拒绝访问。