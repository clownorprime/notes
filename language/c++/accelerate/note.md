### P9:
1. 变量是一个有名字的对象，而对象是计算机中具有某种类型的内存空间。变量和对象之间是有区别的，有些对象没有名称。
2. 局部变量有限的生命期是区分变量和对象的一个重要依据。

### p68
1. 尽量在头文件中不要使用using std::vector等语句。因为，如果在头文件中使用的话，那么所有包含该头文件的客户程序都会得到一个using std::vector语句，这可能并不是用户程序想要做的事情。我们想要为用户保留最大程度的灵活性。所以，头文件中应该使用完整的限定

### p84
库定义了几个异常类，异常类的名称可以报告它们的问题种类
logic\_error(), domain\_error(), invalid\_argument, length\_error, out\_of\_range, e.what()返回一个值，它报告了问题的所在

### p94
使用如下方式打印出一个vector
```c++
    ostream_iterator<int> ofile(cout, "\n");
    copy(vector.begin(), vector.end(), ofile);
```
使用string.substr(ite1, ite2 - ite1)来获得一个substring.

常用算法
copy(first, last, back\_inserter(vec2)); //copy the elements in the vec to the end of the vec2
copy(first, last, front\_inserter(vec)); // copy to the front of the vec2
find(first, last, val); / return an iterator to the first element in the range, if not found, return last.
find\_if(first, last, pred); /pred is an unar funcion which accept an elemnt and returns a bool
transform(first, last,, back\_inserter(vec2), function); /applies the function to the elements, store results into vec2;
accumulate(first, last, init, function); /return the results of accumulating all the values in the ranges[first, end) to init.
partition(first, last, func); /所有func返回true的元素放在前面，false的元素放在后面
stable\_partition(first,  last, func); /stable会让两个区域内元素的相对位置保持不变。
算法作用域容器中的元素，而并不会作用于元素本身，这也就意味着算法不会改变容器的大小，只会改变容器中的元素，如将一个容器中的元素排序。

### 关联容器
关联容器和顺序容器的区别是关联容器是主动排序的，对容器内元素的顺序进行修改往往会出错。
