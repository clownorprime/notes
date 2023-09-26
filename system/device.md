## 设备篇
### 写完这篇笔记应该回答的几个问题
1. 设备与文件的区别
2. block special file和character special file的区别

### 设备文件与设备驱动程序
设备文件分为block special file和character special file.
block devices (also called block special files) usually behave a lot like ordinary files: they are an array of bytes, and the value that is read at a given location is the value that was last written there. Data from block device can be cached in memory and read back from cache; writes can be buffered. Block devices are normally seekable (i.e. there is a notion of position inside the file which the application can change). The name “block device” comes from the fact that the corresponding hardware typically reads and writes a whole block at a time (e.g. a sector on a hard disk).

Character devices (also called character special files) behave like pipes, serial ports, etc. Writing or reading to them is an immediate action. What the driver does with the data is its own business. Writing a byte to a character device might cause it to be displayed on screen, output on a serial port, converted into a sound, ... Reading a byte from a device might cause the serial port to wait for input, might return a random byte (/dev/urandom), ... The name “character device” comes from the fact that each character is handled individually.

从上面可以看出，/dev/pts/2是character special file.而常见的block special file, 而硬盘，软盘，闪存等是block speical file.

主次设备号二者标明了设备的驱动程序，通过ls可以查看到设备文件的st\_dev和st\_rdev. 通过major和minor两个宏可以获取到设备的主次设备号。
