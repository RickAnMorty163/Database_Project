# <b>数据库练手项目<br> 🧐
## <b>Keyword: C++, ODBC, MySQL, Boost::regex

<b>cpp 对于std::getline() std::cin的utf-8 字符集的中文输入存在问题<br>
即使使用对应的宽字符版本 std::wcin 也无济于事<br>
虽然Win10有对于utf-8 的实验性支持，但依然无法解决cpp标准库输入流的问题<br>
故本项目中的所有字符编码(包括ODBC数据源，MySQL数据库记录，cpp文件)均为gbk(936)编码标准 😢😢😢<br>
微软现在也没在windows上整明白unicode,使用原生的std::cin读入utf-8字符非常麻烦<br>
这是一个很有意思的改进方案，通过魔改std::cin 实现: https://chariri.moe/archives/408/windows-cin-read-utf8/ 🥳🥳🥳
