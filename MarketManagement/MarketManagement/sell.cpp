#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

#include "struct.h"

void Sell(int method) //售货
{
	info* vip = NULL;
	if (!isWholesale)
	{
		printf("该顾客是否为会员？（是请按1，否请按除1外任意键）>>>");
		if ((getch()) == '1')
			vip = GetVipNode(vipInfo);
		if (vip != NULL)
			printf("\n欢迎%s %s！", GetVipLevel(vip->level), vip->name);
		printf("\n\n请按任意键进入售货页面>>>");
		getch();
	}

	record* start = NULL;
	if (sellRecord)
	{
		start = sellRecord;
		while (start->next != NULL)
			start = start->next;
	}
	record* rear = start, * pList = NULL;
	totalPrice = 0;
	int num = 0;
	char* recordNum = NULL;
	while (1)
	{
		system("cls");
		num = 0;
		if (start != NULL)
			pList = start->next;
		else if (sellRecord != NULL)
			pList = sellRecord;
		printf("***********************已选商品***********************\n");
		printf("序号\t名称（品种）\t\t数量\t单价\t总价\n\n");
		while (pList != NULL)
		{
			printf("%d\t%s(%s)\t\t", ++num, pList->goods.name, pList->variety.name);
			printf("%g\t%g\t%g\n", pList->num, pList->variety.price, pList->num * pList->variety.price);
			totalPrice += pList->num * pList->variety.price;
			pList = pList->next;
		}
		printf("\n\t\t\t\t\t共计：%g元\n", totalPrice);
		printf("\n******************************************************\n");
		printf("*直接按下回车即可结束商品录入*\n\n\n");
		recordNum = GetRecordNum(sellRecord);
		record* p = (record*)malloc(sizeof(record));
		if (method == 1) //读入商品条码
		{
			if (GetBarCode(p, recordNum) == 0)
				break;
		}
		if (method == 2) //直接读入信息
		{
			if (GetGoodsInfo(p, recordNum) == 0)
				break;
		}
		if (p != NULL)
		{
			p->price *= Discount(vip, p);
			if (sellRecord == NULL)
				sellRecord = p;
			else if (rear != NULL && p != NULL)
			{
				rear->next = p;
				p->next = NULL;
			}
			rear = p;
		}
	}
	if (num)
	{
		printf("\n\n******购物结算******\n\n");
		printf("您一共购买了 %d 种商品，共消费 %g 元。\n", num, totalPrice);
		if (vip)
		{
			AddBuyRecord(vip->buyRecord, recordNum);
			vip->points += (int)totalPrice; //会员积分取整计入
			printf("本次积分：%d，卡内积分余额：%d\n", (int)totalPrice, vip->points);
		}
		printf("请选择支付方式：1.现金  2.银联支付  3.扫码支付>>>");
		int payment = 0;
		while (1)
		{
			payment = getch() - '0';
			if (payment < 1 || payment > 3)
				printf("\n操作错误！请按下1~3范围内的数字>>>");
			else
				break;
		}
		if (payment == 1)
		{
			double payAmount = 0;
			printf("\n请输入实付金额>>>");
			scanf("%lf", &payAmount);
			printf("应找零 %g 元。\n按任意键继续>>>", payAmount - totalPrice);
			getch();
		}
		printf("\n支付成功!");
		if (totalPrice >= giveGiftLimit)
			GiveGift(giftRecord, start, num);
		saleIncome += totalPrice;
	}
	if (isAutoSave)
		DataSave();
}

int GetBarCode(record* p, char* recordNum) //读入商品条码
{
	//条码格式：前两位为果蔬序号，三四位为品种序号，五到八位为数量的整数部分，九到十位为数量的小数部分
	char barCode[MAXC] = { 0 };
	printf("请输入商品条码>>>\n");
	fgets(barCode, MAXC, stdin);
	if (barCode[0] == '\n')
	{
		//system("cls");
		return 0;
	}
	barCode[strlen(barCode) - 1] = 0;
	int goodsIdx = (barCode[0] - '0') * 10 + (barCode[1] - '0' - 1);
	int varietyIdx = (barCode[2] - '0') * 10 + (barCode[3] - '0' - 1);
	double num = 0;
	int i = 4, q = 1000;
	while (i < 10)
	{
		num += ((double)barCode[i++] - (double)'0') * q;
		q /= 10;
	}
	while (strlen(barCode) != 10 || !IsNumber(barCode) || goodsIdx >= NUM || varietyIdx > stock[goodsIdx].varietyNum || isWholesale && num < wholeSaleLimit)
	{
		printf("条码格式错误！请检查后重新输入>>>\n");
		fgets(barCode, MAXC, stdin);
		goodsIdx = (barCode[0] - '0') * 10 + (barCode[1] - '0');
		varietyIdx = (barCode[2] - '0') * 10 + (barCode[3] - '0');
	}
	p->time = NowTime();
	p->goods = stock[goodsIdx];
	p->variety = stock[goodsIdx].variety[varietyIdx];
	p->num = num;
	strcpy(p->recordNum, recordNum);
	p->isWholeSale = isWholesale;
	return 1;
}

int GetGoodsInfo(record* p, char* recordNum) //直接读入信息
{
	int goodsIdx = -1, varietyIdx = -1;
	char t = 0;
	while ((t = getchar()) != '\n' && t != EOF);
	printf("请输入商品名称>>>\n");
	fgets(p->goods.name, MAXC, stdin);
	if (p->goods.name[0] == '\n')
	{
		//system("cls");
		return 0;
	}
	p->goods.name[strlen(p->goods.name) - 1] = 0;
	while ((goodsIdx = GetGoodsIdx(p->goods.name)) == -1)
	{
		printf("库存中未找到名为 %s 的商品。\n", p->goods.name);
		printf("请检查后重新输入>>>\n");
		scanf("%s", p->goods.name);
	}
	printf("请输入品种名称>>>\n");
	scanf("%s", p->variety.name);
	while ((varietyIdx = GetVarietyIdx(goodsIdx, p->variety.name)) == -1)
	{
		printf("库存中未找到品种为 %s 的 %s。\n", p->variety.name, p->goods.name);
		printf("请检查后重新输入>>>\n");
		scanf("%s", p->variety.name);
	}
	printf("请输入数量>>>\n");
	scanf("%lf", &(p->num));
	while (isWholesale && p->num < wholeSaleLimit)
	{
		printf("数量少于批发数量的最小值，请确认后重新输入>>>\n");
		scanf("%lf", &(p->num));
	}
	while (p->num >= stock[goodsIdx].variety[varietyIdx].num)
	{
		printf("该商品库存中仅剩 %g 斤。", stock[goodsIdx].variety[varietyIdx].num);
		printf("请检查后重新输入>>>\n");
		scanf("%lf", &(p->num));
	}
	p->time = NowTime();
	p->goods = stock[goodsIdx];
	p->variety = stock[goodsIdx].variety[varietyIdx];
	strcpy(p->recordNum, recordNum);
	p->isWholeSale = isWholesale;
	return 1;
}

void InquireSellRecord(record* head, char op) //查询售货记录
{
	record* p = (record*)malloc(sizeof(record));
	switch (op - '0')
	{
	case 1: //按时间范围查询
	{
		tm* t1 = (tm*)malloc(sizeof(tm));
		tm* t2 = (tm*)malloc(sizeof(tm));
		while (1)
		{
			printf("请输入要查询的时间段起点:\n");
			ScanTime(t1);
			printf("请输入要查询的时间段终点:\n");
			ScanTime(t2);
			if (CompareTime(t1, t2))
				printf("输入错误！起点应早于终点，请重新输入。\n");
			else
				break;
		}
		p = head;
		int flag = 0;
		while (p != NULL)
		{
			if (CompareTime(t1, p->time) == 0 && CompareTime(t2, p->time) == 1)
			{
				PrintSellRecord(p);
				flag = 1;
			}
			p = p->next;
		}
		if (flag == 0)
			printf("未在该时间段内找到记录！");
		break;
	}
	case 2: //按名称查询
	{
		printf("请输入需要查询的货物及其品种的名称\n");
		char goodsName[MAXC] = { 0 }, varietyName[MAXC] = { 0 };
		scanf("%s %s", goodsName, varietyName);
		p = head;
		while (p != NULL)
		{
			if (strcmp(goodsName, p->goods.name) == 0 && strcmp(varietyName, p->variety.name) == 0)
				PrintSellRecord(p);
			p = p->next;
		}
		break;
	}
	}
}

void GiveGift(record* head, record* sale, int num) //给予赠品
{
	int i = NUM - 1;
	while (totalPrice / gifts[i].purchasePrice < giveGiftRate || gifts[i].num == 0)
	{
		i--;
		if (i == -1)
		{
			printf("\n抱歉，目前赠品库存不足，无法赠送，请您谅解。");
			return;
		}
	}
	printf("\n恭喜获得赠品：%s！", gifts[i].name);
	gifts[i].num--;

	record* p = NULL, * rear = NULL;
	p = (record*)malloc(sizeof(record));
	if (p != NULL)
	{
		p->gift = gifts[i];
		strcpy(p->sellRecordNum, sale->recordNum);
		p->next = NULL;
		if (head)
		{
			rear = head;
			while (rear->next != NULL)
				rear = rear->next;
			rear->next = p;
		}
		else
			head = p;
	}
	if (isAutoSave)
		DataSave();
}
