#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

#include "struct.h"

void InquireCargo() //��ѯ������Ϣ
{
	for (int i = 0; i < NUM; i++)
	{
		printf("%d. ", i + 1);
		printf("%s��", stock[i].name);
		for (int j = 0; j < stock[i].varietyNum; j++)
		{
			printf("%s", stock[i].variety[j].name);
			if (j != stock[i].varietyNum - 1)
				printf("��");
		}
		printf("\n");
	}
}

void InquireVariety() //��ѯƷ����Ϣ
{
	for (int i = 0; i < NUM; i++)
	{
		printf("%d. ", i + 1);
		printf("%s��", stock[i].name);
		for (int j = 0; j < stock[i].varietyNum; j++)
		{
			printf("%s", stock[i].variety[j].name);
			if (j != stock[i].varietyNum - 1)
				printf("��");
		}
		printf("\n");
	}
	printf("\n\n");
	printf("������Ҫ��ѯ��ϸ��Ϣ����ż���Ʒ������\n");
	printf("���ѯ�������ա��������롰7 �����ա�\n");
	printf(">>>");
	int goodsIdx = 1, varietyIdx = 0;
	char variety_name[MAXC] = { 0 };
	scanf("%d %s", &goodsIdx, variety_name);
	system("cls");
	varietyIdx = GetVarietyIdx(goodsIdx - 1, variety_name);
	variety* p = &(stock[goodsIdx - 1].variety[varietyIdx]);
	//δ���ҵ�����......
	printf("%s��%s��:\n\n���ۣ�%gԪ\n�ۼۣ�%gԪ\n�����ڣ�%d��\n", stock[goodsIdx - 1].name, p->name, p->purchasePrice, p->price, p->shelfLife);
	printf("���켾�ڣ�%s\nԭ���أ�%s\n", GetSeason(p->season), p->origin);
}

void InquireMerchant() //��ѯ�̼���Ϣ
{
	printf("  ����������\t ��ϵ�绰\n");
	for (int i = 0; i < NUM; i++)
	{
		printf("%d. ", i + 1);
		printf("%s\t", supplier[i].name);
		printf("%s", supplier[i].tel);
		printf("\n");
	}
}

void InquireStock(char method) //����ѯ
{
	switch (method - '0')
	{
	case 1: //��Ʒ�֣������ѡ��
	{
		int goodsIdx = 0;
		InquireCargo();
		printf("\n\n\n������1��10������>>>");
		scanf("%d", &goodsIdx);
		while (!(1 <= goodsIdx && goodsIdx <= 10))
		{
			printf("\n��Ǹ�����������������0��9������>>>");
			scanf("%d", &goodsIdx);
		}
		system("cls");
		goods* p = &stock[goodsIdx - 1];
		printf("��ǰ %s ��Ʒ��ʣ���棺\n", p->name);
		for (int i = 0; i < p->varietyNum; i++)
			printf("%s��%g\n", p->variety[i].name, p->variety[i].num);
		break;
	}
	case 2: //�����ƣ������ַ�����
	{
		int goodsIdx = -1;
		char goods_name[MAXC] = { 0 };
		printf("������Ҫ��ѯ����Ʒ����>>>");
		scanf("%s", goods_name);
		while ((goodsIdx = GetGoodsIdx(goods_name)) == -1)
		{
			printf("�����δ�ҵ�����Ʒ����ȷ�Ϻ���������>>>");
			scanf("%s", goods_name);
		}
		system("cls");
		printf("%s��", stock[goodsIdx].name);
		for (int i = 0; i < stock[goodsIdx].varietyNum; i++)
			printf("%s��%g�� ", stock[goodsIdx].variety[i].name, stock[goodsIdx].variety[i].num);
		break;
	}
	case 3: //�������̣������ַ�����
	{
		int supplierIdx = -1;
		char merchant_name[MAXC] = { 0 };
		while (1)
		{
			printf("�����빩��������>>>");
			scanf("%s", merchant_name);
			supplierIdx = GetSupplierIdx(merchant_name);
			if (supplierIdx == -1)
				printf("δ�ҵ������̡�%s������ȷ�Ϻ��������롣\n", merchant_name);
			else
				break;
		}
		for (int i = 0; i < NUM; i++)
		{
			int flag = 0;
			goods* p = &(supplier[supplierIdx].stock[i]);
			printf("%s��", p->name);
			for (int j = 0; j < p->varietyNum; j++)
				if (p->variety[j].num != 0)
				{
					printf("%s��%g��  ", p->variety[j].name, p->variety[j].num);
					flag = 1;
				}
			if (!flag)
				printf("δ�ṩ����Ʒ");
			printf("\n");
		}
		break;
	}
	}
}

void Purchase(record* head) //����
{
	record* p = NULL, * rear = NULL;
	if (head)
	{
		rear = head;
		while (rear->next != NULL)
			rear = rear->next;
	}
	printf("*����������ʱֱ�Ӱ��»س����ɷ��ز˵�*\n\n");
	int goodsIdx = -1, varietyIdx = -1, supplierIdx = -1;
	p = (record*)malloc(sizeof(record));
	if (p != NULL)
	{
		p->time = (tm*)malloc(sizeof(tm));
		if (p->time != NULL)
			p->time = NowTime();
		while (1)
		{
			printf("\n�������������ƣ�\n");
			fgets(p->goods.name, MAXC, stdin);
			if (p->goods.name[0] == '\n')
			{
				system("cls");
				return;
			}
			p->goods.name[strlen(p->goods.name) - 1] = 0;
			if ((goodsIdx = GetGoodsIdx(p->goods.name)) == -1)
				printf("δ�ҵ���Ϊ��%s���Ļ����ȷ�Ϻ��������롣\n\n", p->goods.name);
			else
				break;
		}
		while (1)
		{
			printf("\n������%s��Ʒ������\n", p->goods.name);
			scanf("%s", p->variety.name);
			if ((varietyIdx = GetVarietyIdx(goodsIdx, p->variety.name)) == -1)
				printf("δ�ҵ���Ϊ��%s����Ʒ�֣���ȷ�Ϻ��������롣\n\n", p->variety.name);
			else
				break;
		}
		while (1)
		{
			printf("\n������������������\n");
			scanf("%lf", &(p->num));
			if (p->num <= 0)
				printf("����������һ��������\n\n");
			else
				break;
		}
		while (1)
		{
			printf("\n������˻���Ĺ��������ƣ�\n");
			scanf("%s", p->supplier.name);
			if ((supplierIdx = GetSupplierIdx(p->supplier.name)) == -1)
				printf("δ�ҵ���Ϊ��%s���Ĺ����̣���ȷ�Ϻ��������롣\n\n", p->supplier.name);
			else
				break;
		}
		stock[goodsIdx].variety[varietyIdx].num += p->num;
		supplier[supplierIdx].stock[goodsIdx].variety[varietyIdx].num += p->num;
		purchaseCost += stock[goodsIdx].variety[varietyIdx].purchasePrice * p->num;
		if (head == NULL)
			head = p;
		else
			rear->next = p;
		p->next = NULL;
		rear = p;
		printf("\n�����ɹ���");
	}
	if (isAutoSave)
		DataSave();
}

void InquirePurchaseRecord(record* head) //��ѯ������¼
{
	record* p = head;
	char c;
	printf("���������ֲ�ѯ��ʽ��\n1.��ʱ���ѯ\n2.��Ʒ�ֲ�ѯ\n3.����Ӧ�̲�ѯ\n����������Ӧ�������ѡ�����Ĳ�ѯ��ʽ��\n");
	c = getch();
	switch (c - '0')
	{
	case 1: //��ʱ���ѯ
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
		int i = 0;
		int flag = 0;
		while (p != NULL)
		{
			if (CompareTime(t1, p->time) == 0 && CompareTime(t2, p->time) == 1)
			{
				i++;
				PrintPurchaseRecord(p, i);
				flag = 1;
			}
			p = p->next;
		}
		if (flag == 0)
			printf("δ�ڸ�ʱ������ҵ���¼��");
		break;
	}
	case 2: //��Ʒ�ֲ�ѯ
	{
		printf("��������Ҫ��ѯ�Ļ��Ｐ��Ʒ�ֵ�����\n");
		char goodsName[MAXC] = { 0 }, varietyName[MAXC] = { 0 };
		scanf("%s %s", goodsName, varietyName);
		p = head;
		int i = 0;
		while (p != NULL)
		{
			if (strcmp(goodsName, p->goods.name) == 0 && strcmp(varietyName, p->variety.name) == 0)
			{
				i++;
				PrintPurchaseRecord(p, i);
			}
			p = p->next;
		}
		break;
	}
	case 3: //����Ӧ�̲�ѯ
	{
		printf("��������Ҫ��ѯ�Ĺ�Ӧ�̵�����\n");
		while (1)
		{
			char supplierName[MAXC] = { 0 }, supplierTel[MAXC] = { 0 };
			scanf("%s %s", supplierName, supplierTel);
			int i = 0,flag=0;
			p = head;
			while (p != NULL)
			{
				if (strcmp(supplierName, supplier[i].name) == 0 && strcmp(supplierTel, supplier[i].tel) == 0)
				{
					i++;
					PrintPurchaseRecord(p, i);
					flag = 1;
				}
				p = p->next;
			}
			if (flag == 0)
				printf("û�в�ѯ����Ӧ�Ĺ�Ӧ��,����������\n");
			else
				break;
		}
		
		break;
	}
	}
}

void ModifyPurchaseRecord(record* head) //�޸ļ�¼
{
	int del_num, i = 0, num;
	int goodsIdx = -1, varietyIdx = -1, supplierIdx = -1;
	record* p = head, * p0 = head;
	while (p->next != NULL)
	{
		i++;
		printf("%d.", i);
		printf("�������ƣ�%s;", p->goods.name);
		printf("����Ʒ�֣�%s;", p->variety.name);
		printf("������%g;", p->num);
		printf("�ɹ�ʱ�䣺");
		PrintTime(p->time);
		printf("\n");
		p = p->next;
	}
	printf("��������Ҫɾ���ļ�¼����ż�������");
	scanf("%d %d", &num, &del_num);
	int j = num;
	while (--j)
	{
		p0 = p;
		p = p->next;
	}
	if (p != NULL)
	{
		goodsIdx = GetGoodsIdx(p->goods.name);
		varietyIdx = GetVarietyIdx(goodsIdx, p->variety.name);
		supplierIdx = GetSupplierIdx(p->supplier.name);
		if (goodsIdx < NUM && varietyIdx < stock[goodsIdx].varietyNum && supplierIdx < NUM)
		{
			stock[goodsIdx].variety[varietyIdx].num -= del_num;
			supplier[supplierIdx].stock[goodsIdx].variety[varietyIdx].num -= del_num;
			if (stock[goodsIdx].variety[varietyIdx].num < 0)
				stock[goodsIdx].variety[varietyIdx].num = 0;
			if (supplier[supplierIdx].stock[goodsIdx].variety[varietyIdx].num < 0)
				supplier[supplierIdx].stock[goodsIdx].variety[varietyIdx].num = 0;
		}
		if (del_num < p->num)
			p->num -= del_num;
		else
		{
			if (p == head)
				head = head->next;
			else
				p0->next = p->next;
			free(p);
		}
	}
	printf("ɾ���ɹ���");
	if (isAutoSave)
		DataSave();
}
