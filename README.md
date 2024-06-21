# <b>数据库练手项目<br> 🧐
## <b>Keyword: C++, ODBC, MySQL, Boost::regex

<b>cpp 对于
``` C++
#include<iostream>

std::string str;
std::cin>>str; //input utf-8 chars
std::getline(std::cin,str);// input utf-8  chars end with Enter
```
utf-8 字符集的原生中文输入存在问题<br>
即使使用对应的宽字符版本 std::wcin 也无济于事<br>
虽然Win10有对于utf-8 的实验性支持，且
``` C++
#include<Windows.h>

SetConsoleCP(65001);//设置控制台输入为utf-8编码
SetConsole(65001);//设置控制台输出为utf-8编码
```
但依然无法解决cpp标准库输入流的问题<br>
故本项目中的所有字符编码(包括ODBC数据源，MySQL数据库记录，cpp文件)均为gbk(936)编码标准 😢😢😢<br>
<br>

update:🥳<br>
在github找到一个很有意思的改进方案，通过魔改std::cin 实现:<br>
blog: https://chariri.moe/archives/408/windows-cin-read-utf8/ 🥳🥳🥳<br>
source : https://github.com/cqjjjzr/utf8-console/blob/main/src/utf8_cin_windows.cpp 🧐🧐🧐

