#pragma warning(disable:4996)
#pragma warning(disable:6031)
// 在VS中使用scanf时，如果顶端不加这两行代码会报错


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

定义变量或函数时，一个单词用纯小写，多个单词时，第一个单词小写，之后的单词首字母大写
定义常量或文件指针时，用纯大写

清屏操作：system("cls");

时间结构体 ↓ time.h中源代码
struct tm
{
    int tm_sec;   // seconds after the minute - [0, 60] including leap second
    int tm_min;   // minutes after the hour - [0, 59]
    int tm_hour;  // hours since midnight - [0, 23]
    int tm_mday;  // day of the month - [1, 31]
    int tm_mon;   // months since January - [0, 11]
    int tm_year;  // years since 1900
    int tm_wday;  // days since Sunday - [0, 6]
    int tm_yday;  // days since January 1 - [0, 365]
    int tm_isdst; // daylight savings time flag
};

struct tm

       {
              int tm_min;    /* 分 - 取值区间为[0,59]  */

              int tm_hour;   /* 时 - 取值区间为[0,23] */

              int tm_mday;  /* 一个月中的日期 - 取值区间为[1,31]  */

              int tm_mon;   /* 月份（从一月开始，0代表一月） - 取值区间为[0,11]  */

       };
