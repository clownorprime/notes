# 一个程序的前世今生

## 实验目的
<<程序员的自我修养>>在第四章静态链接中，提到ld会自动寻找函数如printf的位置和所依赖的目标文件，最终形成可执行文件。本文将探究动态链接下形成可执行文件所依赖的目标文件是什么，这些目标文件又是怎样链接成为可执行文件。
## 实验环境

Linux 5.10.16.3-microsoft-standard-WSL2
gcc version: 11.3.0

## 源代码
首先来看一个最简单的c程序

    #file: simple.c

    int global_val = 2;
    int main() {
        int local_val;
        local_val = global_val + 1;
            return local_val;
       }

该程序仅仅将一个全局变量加1赋值给一个局部变量，然后将其返回。

## 编译运行
使用默认参数，将该程序使用gcc编译，得到一个可执行文件

    gcc simple.c -o simple

然后使用readelf -S simple查看simple可执行文件的section headers，可以看到simple中包含了.text, .data, .init, .fini等section, 使用objdump -ds simple还可以查看这些section中的具体内容。

可能你学过csapp，了解编译、静态链接、动态链接的概念，但是你考虑过这些sections是从哪里来的吗？

## 从汇编到链接
gcc不使用任何参数，那么就默认进行了预处理、编译、汇编、链接四个过程，使用-c参数，我们可以使gcc停在汇编阶段，不进行链接。

    gcc -c -o simple.o simple.c
使用file命令，可以看出simple.o是可重定位文件。使用objdump命令，我们可以查看simple.o的二进制代码。


	simple.o:     file format elf64-x86-64


	Disassembly of section .text:

	0000000000000000 <main>:
	   0:	f3 0f 1e fa          	endbr64 
	   4:	55                   	push   %rbp
	   5:	48 89 e5             	mov    %rsp,%rbp
	   8:	8b 05 00 00 00 00    	mov    0x0(%rip),%eax        # e <main+0xe>
	   e:	83 c0 01             	add    $0x1,%eax
	  11:	89 45 fc             	mov    %eax,-0x4(%rbp)
	  14:	8b 45 fc             	mov    -0x4(%rbp),%eax
	  17:	5d                   	pop    %rbp
	  18:	c3                   	ret    

可以看到simple.o只包含.text, .data, .comment, .note.gnu.property, .eh\_frame段，与simple可执行文件相比，缺失了.init, .init\_array, .rela.dyn, .dynamic等段，那么很明显，这些缺失的段来自于gcc的最后一个过程：链接。

另外，还可以看到simple.o中的main函数和simple中的main函数是完全一样的，且main函数都位于.text段中，不同的是simple的.text段中还包含其他函数，所以simple的.text段大小大于simple.o。

## 链接
使用gcc的--verbose参数，我们可以把编译链接的中间步骤打印出来

	gcc --verbose -o simple simple.c
	
	...
	 /usr/lib/gcc/x86_64-linux-gnu/11/collect2 -plugin /usr/lib/gcc/x86_64-linux-gnu/11/liblto_plugin.so
	 -plugin-opt=/usr/lib/gcc/x86_64-linux-gnu/11/lto-wrapper -plugin-opt=-fresolution=/tmp/ccZX4ABo.res 
	-plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s -plugin-opt=-pass-through=-lc 
	-plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s --build-id --eh-frame-hdr -m elf_x86_64 
	--hash-style=gnu --as-needed -dynamic-linker /lib64/ld-linux-x86-64.so.2 -pie -z now -z relro -o simple 
	/usr/lib/gcc/x86_64-linux-gnu/11/../../../x86_64-linux-gnu/Scrt1.o 
	/usr/lib/gcc/x86_64-linux-gnu/11/../../../x86_64-linux-gnu/crti.o 
	/usr/lib/gcc/x86_64-linux-gnu/11/crtbeginS.o -L/usr/lib/gcc/x86_64-linux-gnu/11 
	-L/usr/lib/gcc/x86_64-linux-gnu/11/../../../x86_64-linux-gnu 
	-L/usr/lib/gcc/x86_64-linux-gnu/11/../../../../lib -L/lib/x86_64-linux-gnu -L/lib/../lib 
	-L/usr/lib/x86_64-linux-gnu -L/usr/lib/../lib -L/usr/lib/gcc/x86_64-linux-gnu/11/../../.. 
	/tmp/ccsvVfED.o -lgcc --push-state --as-needed -lgcc_s --pop-state -lc -lgcc --push-state 
	--as-needed -lgcc_s --pop-state /usr/lib/gcc/x86_64-linux-gnu/11/crtendS.o 
	/usr/lib/gcc/x86_64-linux-gnu/11/../../../x86_64-linux-gnu/crtn.o
	COLLECT_GCC_OPTIONS='-v' '-o' 'simple' '-mtune=generic' '-march=x86-64' '-dumpdir' 'simple.'

这里，我们只保留了gcc链接过程的命令，我们可以看到，这里的链接器实际上是collect2, 这里的collect2函数可以视为ld链接器, 本质上是一个静态链接过程。我们可以看到，collect2的参数包括以下文件：

	liblto_plugin.so
	ld-linux-x86-64.so.2
	Scrt1.o
	crti.o
	crtbeginS.o
	ccsvVfED.o
	crtendS.o
	crtn.o

那么我们现在可以回答上面提到的一个问题，simple可执行文件中的section一部分来自于simple.o，另外一部分来自于以上文件。

比方说，simple中有一个叫做.init的段，主要是完成main函数调用之前的初始化工作。simple, crti.o, crtn.o都有.init段，并且simple中的.init开始部分来自于crti.o, 结束部分来自于crtn.o。其实不仅仅是.init, 对于.fnit段，simple, crti.o, crtn.o也有着相同的关系。


.text段中的\_start函数来自于Scrt1.o;
crtbeginS.o提供了.text段中的\_\_do\_global\_dtors\_aux、deregister\_tm\_clones、register\_tm\_clones、frame\_dummy函数。crtbeginS.o和crtendS.o主要是用于C++全局对象的构造和析构。 详见 <<程序员的自我修养>> p345。
.interp段来自于ld-linux-x86-64.so.2, 它是一个字符串，保存了动态链接器的路径。

.dynamic段包含了动态链接器所需要的全部信息，这个段我猜测是在其他段的基础之上完成的，因为这个段中包含了符号表、重定位表、初始化代码、结束代码等位置。


## 总结
本文，使用gcc的--verbose参数，列举出了在链接过程中所需要的目标文件, 然后对这些目标文件与可执行文件之间的关系进行了分析。 可以看出，可执行文件中包含了这些目标文件，这些目标文件就像静态库，在链接的过程和源代码编译出的可重定位文件(本例中的simple.o)链接在一起形成了一个可执行文件。

## 后续
仔细查看simple的section, 我们发现其中既有.init，又有.init\_array, 那么.init\_array的作用是什么，simple中的\_start段和glibc中的\_start段的关系又是什么？这些我们留在以后的文章中进行探究。

ld-linux-x86-64.so.2是动态链接器, 我们使用objdump -ds 命令查看simple的二进制代码，发现可执行文件中的.interp段是一个字符串，保存了动态链接器的路径，然而在二进制代码中，并没有动态链接器的实际内容，表明动态链接器是在装载的过程中才被映射到进程的虚拟空间中去。

我们稍稍改变simple.c，增加一个无限循环，以方便我们查看进程虚拟空间。

    #file: simple1.c

    int global_val = 2;
    int main() {
        int local_val;
        local_val = global_val + 1;
            return local_val;
		while(1) {
		}
       }

编译，并在后台运行simple1.c

	gcc simple1.c -o simple1 && ./simple1 &

shell返回进程的pid, 在我的电脑上该进程的pid为18672,我们使用cat命令查看进程18672的虚拟空间地址。

	cat /proc/18672/maps

	...
	7f006ba6e000-7f006ba70000 rw-p 00000000 00:00 0 
	7f006ba70000-7f006ba72000 r--p 00000000 08:10 6292                       /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
	7f006ba72000-7f006ba9c000 r-xp 00002000 08:10 6292                       /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
	7f006ba9c000-7f006baa7000 r--p 0002c000 08:10 6292                       /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
	7f006baa7000-7f006baa8000 r--p 00000000 08:10 2332                       /usr/lib/locale/C.utf8/LC_IDENTIFICATION
	7f006baa8000-7f006baaa000 r--p 00037000 08:10 6292                       /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
	7f006baaa000-7f006baac000 rw-p 00039000 08:10 6292                       /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
	...

输出结果中，我们只保留了ld-linux-x86.so.2的部分，省略了其余部分。可以看到，ld-linux-x86.so.2被映射到了虚拟地址空间7f006ba6e000-7f006baac000。结合上文， 这也就证明了动态链接器是在程序装载的过程中被加载到进程的虚拟地址空间，其本身也是一个共享对象。


