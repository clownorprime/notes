# 基本的CMakeLists.txt的编写
cmake最小项目只需要三行：
    cmake_mimumum_required:指定cmake的最小版本号.
    project:指定项目名称
    add_executable:生成可执行文件.

## 构建、编译、运行
cmake可以指定构建树和源代码树.
    cmake -S <source tree> -B <build tree>.

## 优化CMakeLists.txt文件

之前的CMakeLists.txt文件如下:
```cmake
    cmake_mimimun_required(VERSION 3.16.0)
    project(Tutorial)
    add_executable(Tutorial tutorial.cpp)
```
今后可能会对项目文件的名称更改，为了程序的可修改性，这里可以使用PROJECT\_NAME来更改项目名称.  
这里可以把第三行程序改为：
    add_executable(${PROJECT_NAME} tutorial.cpp)

生成可执行文件如果需要多个源文件，可以使用set指令
```cmake
    set(SRC_LIST a.cpp b.cpp c.cpp)
    add_executable(${PROJECT_NAME} ${SRC_LIST})
```

## 增加版本号和配置头文件
我们怎么样把CMakeLists.txt文件中的信息传递给其他文件呢？增加版本号提供了一个例子.
需要添加的程序有:
```cmake
    project(Tutorial VERSION 1.0) #将项目版本号设为1.0
    configure_file(TutorialConfig.h.in TutorialConfig.h)
    target_include_directories(${PROJECT_NAME} PUBLIC
                        ${PROJECT_BINARY_DIR}
                        )
```
然后在源代码目录中创建一个TutorialConfig.h.in文件，文件的内容是：
```txt
    #define Tutorial_VERSION_MAJOR @Tutorial_VERSION_MAJOR@
    #define Tutorial_VERSION_MINOR @Tutorial_VERSION_MINOR@
```

这里configure\_file的作用是从输入文件复制到输出文件，并替换掉输出文件中被@VAR@或${VAR}引用的变量名。这里，这里我们将项目版本号设置为1.0，那么这里的Tutorial\_VERSION\_MAJOR值为1，Tutorial\_VERSION\_MINOR值被设置为0，于是在TutorialConfig.h的文件内容为:
```txt
    #define Tutorial_VERSION_MAJOR 1
    #define Tutorial_VERSION_MINOR 0
```
另外，target\_include\_directories指令将配置文件写入PROJECT\_BINARY\_DIR文件中，即build文件中。

include\_directories(x/y)影响的是所有构建的target范围,使用这个命令，所有的target都被包含了这个路径；而target\_include\_directories(t x/y)仅仅影响了t的路径范围，而对于其他的target的include路径并不影响，支持PUBLIC PRIVATE INTERFACE三个属性。

使用c++标准，可以使用set显示指令：
```cmake
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED True);
```
