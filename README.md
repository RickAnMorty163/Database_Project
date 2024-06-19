# <b>数据库练手项目<br> 🧐
## <b>Keyword: C++, ODBC, MySQL, Boost

<b>cpp 对于std::getline() std::cin的utf-8 字符集的中文输入存在问题
即使使用对应的宽字符版本 std::wcin 也无济于事
虽然Win10有对于utf-8 的实验性支持，但依然无法解决cpp标准库输入流的问题
故本项目中的所有字符编码(包括ODBC数据源，MySQL数据库记录，cpp文件)均为gbk(936)编码标准 😢😢😢
