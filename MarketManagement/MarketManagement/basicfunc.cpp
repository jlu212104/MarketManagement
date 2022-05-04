#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

#include "struct.h"

void Back() //返回菜单
{
	printf("\n\n\n请按任意键返回菜单>>>");
	getch();
	system("cls");
}

tm *NowTime() //获取系统时间
{
	time_t timep;
	time(&timep);
	tm *nowTime = NULL;
	nowTime = localtime(&timep);
	nowTime->tm_mon++; // tm_mon中月份从0开始
	return nowTime;
}

void PrintTime(tm *t) //打印时间
{
	printf("2022年%d月%d日", t->tm_mon, t->tm_mday);
	if (t->tm_hour < 10)
		printf("0");
	printf("%d:", t->tm_hour);
	if (t->tm_min < 10)
		printf("0");
	printf("%d", t->tm_min);
}

void ScanTime(tm *t) //输入时间
{
	printf("请依次输入月份，日期，小时，分钟>>>");
	scanf("%d%d%d%d", &t->tm_mon, &t->tm_mday, &t->tm_hour, &t->tm_min);
}

int CompareTime(tm *t1, tm *t2) //时间比较（t1>t2时返回1；否则返回0）
{
	if (t1->tm_mon > t2->tm_mon || (t1->tm_mon == t2->tm_mon && t1->tm_mday > t2->tm_mday) || (t1->tm_mon == t2->tm_mon && t1->tm_mday == t2->tm_mday && t1->tm_hour > t2->tm_hour) ||
		(t1->tm_mon == t2->tm_mon && t1->tm_mday == t2->tm_mday && t1->tm_hour == t2->tm_hour && t1->tm_min >= t2->tm_min))
		return 1;
	else
		return 0;
}

int SetPassword() //设置初始密码
{
	char password[MAXC] = {0}, _password[MAXC] = {0};
	while (1)
	{
		printf("请设置管理员密码（不少于6位）：");
		GetPassword(password);
		while (strlen(password) < 6)
		{
			printf("\n密码长度小于6位！请重新输入：");
			GetPassword(password);
		}
		printf("\n请再次输入密码以确认：");
		GetPassword(_password);
		if (strcmp(password, _password))
		{
			printf("\n两次输入密码不一致，请按任意键重新设置密码");
			getch();
			system("cls");
		}
		else
			return (fprintf(ACCOUNT, "%s", password)) ? 1 : 0;
	}
}

int GetPassword(char str[]) //从键盘读入密码
{
	int idx = 0;
	char ch = 0;
	while ((ch = getch()) != '\r')
	{
		if (ch == ' ' || ch == 8) //空格和退格不能作为密码
			continue;
		str[idx++] = ch;
		printf("*");
	}
	if (str[0] == 0)
		return 0;
	else
		return 1;
}

void SignIn() //管理员登录
{
	printf("请输入密码：");
	char password[MAXC] = {0};
	GetPassword(password);
	while (strcmp(systemPassword, password))
	{
		printf("\n密码有误！请重新输入：");
		memset(password, 0, MAXC);
		GetPassword(password);
	}
	system("cls");
}

void ReleaseRecord(record *head) //释放记录链表空间
{
	record *p0 = head, *p = NULL;
	while (p0 != NULL)
	{
		p = p0;
		p0 = p0->next;
		free(p);
	}
}

void ReleaseInfo(info *head) //释放信息链表空间
{
	info *p0 = head, *p = NULL;
	while (p0 != NULL)
	{
		p = p0;
		p0 = p0->next;
		free(p);
	}
}

int GetGoodsIdx(char name[]) //获取货物下标
{
	for (int i = 0; i < NUM; i++)
	{
		if (strcmp(name, stock[i].name) == 0)
			return i;
	}
	return -1;
}

int GetVarietyIdx(int n, char name[]) //获取品种下标
{
	for (int i = 0; i < stock[n].varietyNum; i++)
	{
		if (strcmp(name, stock[n].variety[i].name) == 0)
			return i;
	}
	return -1;
}

int GetSupplierIdx(char name[]) //获取供货商下标
{
	int idx[NUM] = {0}, k = 0;
	for (int i = 0; i < NUM; i++)
	{
		if (strcmp(name, supplier[i].name) == 0)
			idx[k++] = i;
	}
	if (k > 1)
	{
		printf("发现重名供货商。请通过联系方式选择您所要查找的供货商序号：\n");
		for (int i = 0; i < k; i++)
			printf("%d. %s  TEL: %s\n", i + 1, supplier[idx[i]].name, supplier[idx[i]].tel);
		printf(">>>");
		idx[0] = getch() - '0' - 1;
		printf("\n");
	}
	else if (k == 0)
		return -1;
	return idx[0];
}

info *GetVipNode(info *head) //获取会员节点
{
	printf("\n请选择识别会员的方式：");
	printf("\n1.按编号");
	printf("\n2.按姓名");
	printf("\n3.按电话");
	printf("\n>>>");
	info *p = head;
	if (p == NULL)
		printf("error\n");
	char op = 0;
	const char *str = 0;
	char inputInfo[MAXC] = {0}, savedInfo[MAXC] = {0};
	while (1)
	{
		op = getch();
		if (op > '3' || op < '1')
			printf("\n操作错误！请输入1-3范围内的数字>>>");
		else
			break;
	}
	switch (op - '0')
	{
	case 1:
		str = "编号";
		break;
	case 2:
		str = "姓名";
		break;
	case 3:
		str = "电话";
		break;
	}
	system("cls");
	printf("（返回上一层请直接按下回车）\n");
	while (1)
	{
		printf("\n请输入会员%s>>>\n", str);
		fgets(inputInfo, MAXC, stdin);
		if (inputInfo[0] == '\n')
			return NULL;
		inputInfo[strlen(inputInfo) - 1] = 0;
		while (p)
		{
			switch (op - '0')
			{
			case 1:
				strcpy(savedInfo, p->num);
				break;
			case 2:
				strcpy(savedInfo, p->name);
				break;
			case 3:
				strcpy(savedInfo, p->tel);
				break;
			}
			if (strcmp(savedInfo, inputInfo) == 0)
				break;
			p = p->next;
		}
		if (p == NULL)
			printf("未找到该会员！请确认后重新输入信息。");
		else
			break;
	}
	return p;
}

const char *GetSeason(int season) //获取季节名
{
	switch (season)
	{
	case 1:
		return "春季";
		break;
	case 2:
		return "夏季";
		break;
	case 3:
		return "秋季";
		break;
	case 4:
		return "冬季";
		break;
	default:
		return NULL;
	}
}

const char *GetVipLevel(int level) //获取会员等级名称
{
	switch (level)
	{
	case 1:
		return "普通会员";
		break;
	case 2:
		return "白金会员";
		break;
	case 3:
		return "钻石会员";
		break;
	default:
		return NULL;
	}
}

void PrintPurchaseRecord(record *p, int num)
{
	printf("\n%d.", num);
	printf("货物名称：%s\n", p->goods.name);
	printf("所属品种：%s\n", p->variety.name);
	printf("数量：%g\n", p->num);
	printf("供应商：%s\n", p->supplier.name);
	printf("采购时间：");
	PrintTime(p->time);
	printf("\n\n");
}

void PrintSellRecord(record *p)
{
	printf("\n货物名称：%s\n", p->goods.name);
	printf("所属品种：%s\n", p->variety.name);
	printf("数量：%g\n", p->num);
	printf("销售时间：");
	PrintTime(p->time);
	char str[MAXC] = {"零售"};
	if (p->isWholeSale)
		strcpy(str, "批发");
	printf("\n销售方式：%s\n", str);
}

int IsNumber(char str[]) //判断是否为全数字字符串
{
	for (int i = 0; i < strlen(str); i++)
		if (!('0' <= str[i] && str[i] <= '9'))
			return 0;
	return 1;
}

double Discount(info *vip, record *sale) //折扣
{
	double discount = 1;

	if (vip)
	{
		if (vip->level == 1)
			discount = cheapLevel1;
		if (vip->level == 2)
			discount = cheapLevel2;
		if (vip->level == 3)
			discount = cheapLevel3;
	}

	if (sale->num >= 5 && sale->num < 10 && cheapLevel1 < discount)
		discount = cheapLevel1;
	if (sale->num >= 10 && sale->num < 15 && cheapLevel2 < discount)
		discount = cheapLevel2;
	if (sale->num >= 15 && cheapLevel3 < discount)
		discount = cheapLevel3;

	if (IsOffSeason(sale->variety))
		discount *= offSeasonRate;
	return discount;
}

void SetDiscount(char method) //设置折扣
{
	printf("请输入新的第%c级折扣>>>", method);
	switch (method - '0')
	{
	case 1:
	{
		scanf("%lf", &cheapLevel1);
		break;
	}
	case 2:
	{
		scanf("%lf", &cheapLevel2);
		break;
	}
	case 3:
	{
		scanf("%lf", &cheapLevel3);
		break;
	}
	}
}

int IsOffSeason(variety commodity) //判断是否反季
{
	int nowSeason = NowTime()->tm_mon / 3;
	if (nowSeason == 0)
		nowSeason = 4;
	//春季(1)为3~5月，夏季(2)为6~8月，秋季(3)为9~11月，冬季(4)为12~2月
	if (nowSeason == commodity.season)
		return 0;
	else
		return 1;
}

int GetNextNum(char str[6]) //返回正确的成员编号的整型值
{
	int sum = 0, q = 1;
	int i, j;
	for (i = 0; i < 6; i++)
	{
		q = 1;
		for (j = 1; j < 6 - i; j++)
		{
			q *= 10;
		}
		sum += (str[i] - '0') * q;
	}
	return sum + 1;
}

char *TransformNumIntoStr(int num) //将数字转换为字符串
{
	int i;
	static char str[MAXC] = {0};
	for (i = 5; i >= 0; i--)
	{
		str[i] = num % 10 + '0';
		num /= 10;
	}
	return str;
}

void CheckStock(record *head) //检查库存
{
	if (head == NULL)
		return;
	record *p = head;
	while (p != NULL)
	{
		if (IsStale(p->time->tm_mon, p->time->tm_mday, NowTime()->tm_mon, NowTime()->tm_mday, p->variety.shelfLife))
		{
			int goodsIdx = GetGoodsIdx(p->goods.name);
			int varietyIdx = GetVarietyIdx(goodsIdx, p->variety.name);
			stock[goodsIdx].variety[varietyIdx].num -= p->num;
			if (stock[goodsIdx].variety[varietyIdx].num < 0)
				stock[goodsIdx].variety[varietyIdx].num = 0;
			printf("在");
			PrintTime(p->time);
			printf("购进的 %g 斤 %s（%s） 已过期，已在库存记录中扣除，请及时处理！\n", p->num, p->goods.name, p->variety.name);
		}
		p = p->next;
	}
	printf("按任意键继续>>>");
	getch();
	system("cls");
}

int IsStale(int purchaseMonth, int purchaseDay, int nowMonth, int nowDay, int shelfLife) //判断是否过期
{
	int month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	while (nowMonth > purchaseMonth && shelfLife > month[purchaseMonth] - purchaseDay)
	{
		shelfLife -= month[purchaseMonth] - purchaseDay;
		purchaseMonth++;
		purchaseDay = 1;
	}
	if (nowDay - purchaseDay >= shelfLife)
		return 1;
	return 0;
}
