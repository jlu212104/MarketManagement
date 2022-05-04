#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

#include "struct.h"

void Sell(int method) //�ۻ�
{
	info* vip = NULL;
	if (!isWholesale)
	{
		printf("�ù˿��Ƿ�Ϊ��Ա�������밴1�����밴��1���������>>>");
		if ((getch()) == '1')
			vip = GetVipNode(vipInfo);
		if (vip != NULL)
			printf("\n��ӭ%s %s��", GetVipLevel(vip->level), vip->name);
		printf("\n\n�밴����������ۻ�ҳ��>>>");
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
		printf("***********************��ѡ��Ʒ***********************\n");
		printf("���\t���ƣ�Ʒ�֣�\t\t����\t����\t�ܼ�\n\n");
		while (pList != NULL)
		{
			printf("%d\t%s(%s)\t\t", ++num, pList->goods.name, pList->variety.name);
			printf("%g\t%g\t%g\n", pList->num, pList->variety.price, pList->num * pList->variety.price);
			totalPrice += pList->num * pList->variety.price;
			pList = pList->next;
		}
		printf("\n\t\t\t\t\t���ƣ�%gԪ\n", totalPrice);
		printf("\n******************************************************\n");
		printf("*ֱ�Ӱ��»س����ɽ�����Ʒ¼��*\n\n\n");
		recordNum = GetRecordNum(sellRecord);
		record* p = (record*)malloc(sizeof(record));
		if (method == 1) //������Ʒ����
		{
			if (GetBarCode(p, recordNum) == 0)
				break;
		}
		if (method == 2) //ֱ�Ӷ�����Ϣ
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
		printf("\n\n******�������******\n\n");
		printf("��һ�������� %d ����Ʒ�������� %g Ԫ��\n", num, totalPrice);
		if (vip)
		{
			AddBuyRecord(vip->buyRecord, recordNum);
			vip->points += (int)totalPrice; //��Ա����ȡ������
			printf("���λ��֣�%d�����ڻ�����%d\n", (int)totalPrice, vip->points);
		}
		printf("��ѡ��֧����ʽ��1.�ֽ�  2.����֧��  3.ɨ��֧��>>>");
		int payment = 0;
		while (1)
		{
			payment = getch() - '0';
			if (payment < 1 || payment > 3)
				printf("\n���������밴��1~3��Χ�ڵ�����>>>");
			else
				break;
		}
		if (payment == 1)
		{
			double payAmount = 0;
			printf("\n������ʵ�����>>>");
			scanf("%lf", &payAmount);
			printf("Ӧ���� %g Ԫ��\n�����������>>>", payAmount - totalPrice);
			getch();
		}
		printf("\n֧���ɹ�!");
		if (totalPrice >= giveGiftLimit)
			GiveGift(giftRecord, start, num);
		saleIncome += totalPrice;
	}
	if (isAutoSave)
		DataSave();
}

int GetBarCode(record* p, char* recordNum) //������Ʒ����
{
	//�����ʽ��ǰ��λΪ������ţ�����λΪƷ����ţ��嵽��λΪ�������������֣��ŵ�ʮλΪ������С������
	char barCode[MAXC] = { 0 };
	printf("��������Ʒ����>>>\n");
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
		printf("�����ʽ�����������������>>>\n");
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

int GetGoodsInfo(record* p, char* recordNum) //ֱ�Ӷ�����Ϣ
{
	int goodsIdx = -1, varietyIdx = -1;
	char t = 0;
	while ((t = getchar()) != '\n' && t != EOF);
	printf("��������Ʒ����>>>\n");
	fgets(p->goods.name, MAXC, stdin);
	if (p->goods.name[0] == '\n')
	{
		//system("cls");
		return 0;
	}
	p->goods.name[strlen(p->goods.name) - 1] = 0;
	while ((goodsIdx = GetGoodsIdx(p->goods.name)) == -1)
	{
		printf("�����δ�ҵ���Ϊ %s ����Ʒ��\n", p->goods.name);
		printf("�������������>>>\n");
		scanf("%s", p->goods.name);
	}
	printf("������Ʒ������>>>\n");
	scanf("%s", p->variety.name);
	while ((varietyIdx = GetVarietyIdx(goodsIdx, p->variety.name)) == -1)
	{
		printf("�����δ�ҵ�Ʒ��Ϊ %s �� %s��\n", p->variety.name, p->goods.name);
		printf("�������������>>>\n");
		scanf("%s", p->variety.name);
	}
	printf("����������>>>\n");
	scanf("%lf", &(p->num));
	while (isWholesale && p->num < wholeSaleLimit)
	{
		printf("��������������������Сֵ����ȷ�Ϻ���������>>>\n");
		scanf("%lf", &(p->num));
	}
	while (p->num >= stock[goodsIdx].variety[varietyIdx].num)
	{
		printf("����Ʒ����н�ʣ %g �", stock[goodsIdx].variety[varietyIdx].num);
		printf("�������������>>>\n");
		scanf("%lf", &(p->num));
	}
	p->time = NowTime();
	p->goods = stock[goodsIdx];
	p->variety = stock[goodsIdx].variety[varietyIdx];
	strcpy(p->recordNum, recordNum);
	p->isWholeSale = isWholesale;
	return 1;
}

void InquireSellRecord(record* head, char op) //��ѯ�ۻ���¼
{
	record* p = (record*)malloc(sizeof(record));
	switch (op - '0')
	{
	case 1: //��ʱ�䷶Χ��ѯ
	{
		tm* t1 = (tm*)malloc(sizeof(tm));
		tm* t2 = (tm*)malloc(sizeof(tm));
		while (1)
		{
			printf("������Ҫ��ѯ��ʱ������:\n");
			ScanTime(t1);
			printf("������Ҫ��ѯ��ʱ����յ�:\n");
			ScanTime(t2);
			if (CompareTime(t1, t2))
				printf("����������Ӧ�����յ㣬���������롣\n");
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
			printf("δ�ڸ�ʱ������ҵ���¼��");
		break;
	}
	case 2: //�����Ʋ�ѯ
	{
		printf("��������Ҫ��ѯ�Ļ��Ｐ��Ʒ�ֵ�����\n");
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

void GiveGift(record* head, record* sale, int num) //������Ʒ
{
	int i = NUM - 1;
	while (totalPrice / gifts[i].purchasePrice < giveGiftRate || gifts[i].num == 0)
	{
		i--;
		if (i == -1)
		{
			printf("\n��Ǹ��Ŀǰ��Ʒ��治�㣬�޷����ͣ������½⡣");
			return;
		}
	}
	printf("\n��ϲ�����Ʒ��%s��", gifts[i].name);
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
