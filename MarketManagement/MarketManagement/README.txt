#pragma warning(disable:4996)
#pragma warning(disable:6031)
// ��VS��ʹ��scanfʱ��������˲��������д���ᱨ��


// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ����ʹ�ü���: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�

�����������ʱ��һ�������ô�Сд���������ʱ����һ������Сд��֮��ĵ�������ĸ��д
���峣�����ļ�ָ��ʱ���ô���д

����������system("cls");

ʱ��ṹ�� �� time.h��Դ����
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
              int tm_min;    /* �� - ȡֵ����Ϊ[0,59]  */

              int tm_hour;   /* ʱ - ȡֵ����Ϊ[0,23] */

              int tm_mday;  /* һ�����е����� - ȡֵ����Ϊ[1,31]  */

              int tm_mon;   /* �·ݣ���һ�¿�ʼ��0����һ�£� - ȡֵ����Ϊ[0,11]  */

       };
