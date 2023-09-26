##终端与shell之间的区别与联系
终端是一个输入输出设备，提供输入输出命令的交互界面，终端的主要任务是接收用户输入的命令，并将其传递给shell.
shell则是一个命令解析器，shell不处理键盘事件，不负责字符显示，只翻译命令，将终端输入的命令转化为内核能够理解的语言之后传递给内核，由内核执行命令，并将结果返回给终端。
当我们打开终端时，shell也会跟着启动，操作系统会将终端和shell关联起来，接着我们在终端输入命令，由shell解析命令。
我们可以通过ps -axo pid,ppid,pgid,sid,comm命令，可以看到bash的父进程是gnome\_terminal,也就是说bash的父进程即gnome终端
