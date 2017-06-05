# c_五子棋
###学习了一点小东西###
* c语言里的输入缓冲区
```
void clear_buf(void) //清除缓冲区
{
    int a;
    while ((a = getchar()) != '\n' && a != EOF);
}

setbuf(stdout,buf); //Linux 下清除缓冲区
fflush(stdin); //Windows 下清除缓冲区
```
可以清除缓冲区,解决很多Bug.

* 加了悔棋代码

有点傻逼,但想不出来更好的方式.

* 加了下完所有棋子,没有结果的情况

也是不太可能出现的情况,但是会出现就要去解决.

* 差不多

看看还有什么不足的,可以接着更改.