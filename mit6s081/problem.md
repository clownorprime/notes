#Trap.c:213中为什么scause == 0x80000001代表timer interrupt.(参考riscv-privileged page71)
# 锁与中断之间的关系
为什么acquire的时候，需要关闭中断, 而release的时候，又需要打开中断
