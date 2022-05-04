#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

#include "struct.h"

void InquireCargo() //查询货物信息
{
	for (int i = 0; i < NUM; i++)
	{
		printf("%d. ", i + 1);
		printf("%s：", stock[i].name);
		for (int j = 0; j < stock[i].varietyNum; j++)
		{
			printf("%s", stock[i].variety[j].name);
			if (j != stock[i].varietyNum - 1)
				printf("、");
		}
		printf("\n");
	}
}

void InquireVariety() //查询品种信息
{
	for (int i = 0; i < NUM; i++)
	{
		printf("%d. ", i + 1);
		printf("%s：", stock[i].name);
		for (int j = 0; j < stock[i].varietyNum; j++)
		{
			printf("%s", stock[i].variety[j].name);
			if (j != stock[i].varietyNum - 1)
				printf("、");
		}
		printf("\n");
	}
	printf("\n\n");
	printf("请输入要查询详细信息的序号及其品种名。\n");
	printf("如查询“阿克苏”，请输入“7 阿克苏”\n");
	printf(">>>");
	int goodsIdx = 1, varietyIdx = 0;
	char variety_name[MAXC] = { 0 };
	scanf("%d %s", &goodsIdx, variety_name);
	system("cls");
	varietyIdx = GetVarietyIdx(goodsIdx - 1, variety_name);
	variety* p = &(stock[goodsIdx - 1].variety[varietyIdx]);
	//未查找到操作......
	printf("%s（%s）:\n\n进价：%g元\n售价：%g元\n保质期：%d天\n", stock[goodsIdx - 1].name, p->name, p->purchasePrice, p->price, p->shelfLife);
	printf("成熟季节：%s\n原产地：%s\n", GetSeason(p->season), p->origin);
}

void InquireMerchant() //查询商家信息
{
	printf("  供货商名称\t 联系电话\n");
	for (int i = 0; i < NUM; i++)
	{
		printf("%d. ", i + 1);
		printf("%s\t", supplier[i].name);
		printf("%s", supplier[i].tel);
		printf("\n");
	}
}

void InquireStock(char method) //库存查询
{
	switch (method - '0')
	{
	case 1: //按品种（给序号选择）
	{
		int goodsIdx = 0;
		InquireCargo();
		printf("\n\n\n请输入1到10的数字>>>");
		scanf("%d", &goodsIdx);
		while (!(1 <= goodsIdx && goodsIdx <= 10))
		{
			printf("\n抱歉，您输入错误，请输入0到9的数字>>>");
			scanf("%d", &goodsIdx);
		}
		system("cls");
		goods* p = &stock[goodsIdx - 1];
		printf("当前 %s 各品种剩余库存：\n", p->name);
		for (int i = 0; i < p->varietyNum; i++)
			printf("%s：%g\n", p->variety[i].name, p->variety[i].num);
		break;
	}
	case 2: //按名称（输入字符串）
	{
		int goodsIdx = -1;
		char goods_name[MAXC] = { 0 };
		printf("请输入要查询的商品名称>>>");
		scanf("%s", goods_name);
		while ((goodsIdx = GetGoodsIdx(goods_name)) == -1)
		{
			printf("库存中未找到该商品，请确认后重新输入>>>");
			scanf("%s", goods_name);
		}
		system("cls");
		printf("%s：", stock[goodsIdx].name);
		for (int i = 0; i < stock[goodsIdx].varietyNum; i++)
			printf("%s：%g斤 ", stock[goodsIdx].variety[i].name, stock[goodsIdx].variety[i].num);
		break;
	}
	case 3: //按供货商（输入字符串）
	{
		int supplierIdx = -1;
		char merchant_name[MAXC] = { 0 };
		while (1)
		{
			printf("请输入供货商名称>>>");
			scanf("%s", merchant_name);
			supplierIdx = GetSupplierIdx(merchant_name);
			if (supplierIdx == -1)
				printf("未找到供货商“%s”，请确认后重新输入。\n", merchant_name);
			else
				break;
		}
		for (int i = 0; i < NUM; i++)
		{
			int flag = 0;
			goods* p = &(supplier[supplierIdx].stock[i]);
			printf("%s：", p->name);
			for (int j = 0; j < p->varietyNum; j++)
				if (p->variety[j].num != 0)
				{
					printf("%s：%g斤  ", p->variety[j].name, p->variety[j].num);
					flag = 1;
				}
			if (!flag)
				printf("未提供该商品");
			printf("\n");
		}
		break;
	}
	}
}

void Purchase(record* head) //进货
{
	record* p = NULL, * rear = NULL;
	if (head)
	{
		rear = head;
		while (rear->next != NULL)
			rear = rear->next;
	}
	printf("*在输入名称时直接按下回车即可返回菜单*\n\n");
	int goodsIdx = -1, varietyIdx = -1, supplierIdx = -1;
	p = (record*)malloc(sizeof(record));
	if (p != NULL)
	{
		p->time = (tm*)malloc(sizeof(tm));
		if (p->time != NULL)
			p->time = NowTime();
		while (1)
		{
			printf("\n请输入货物的名称：\n");
			fgets(p->goods.name, MAXC, stdin);
			if (p->goods.name[0] == '\n')
			{
				system("cls");
				return;
			}
			p->goods.name[strlen(p->goods.name) - 1] = 0;
			if ((goodsIdx = GetGoodsIdx(p->goods.name)) == -1)
				printf("未找到名为“%s”的货物，请确认后重新输入。\n\n", p->goods.name);
			else
				break;
		}
		while (1)
		{
			printf("\n请输入%s的品种名：\n", p->goods.name);
			scanf("%s", p->variety.name);
			if ((varietyIdx = GetVarietyIdx(goodsIdx, p->variety.name)) == -1)
				printf("未找到名为“%s”的品种，请确认后重新输入。\n\n", p->variety.name);
			else
				break;
		}
		while (1)
		{
			printf("\n请输入进货数量（斤）：\n");
			scanf("%lf", &(p->num));
			if (p->num <= 0)
				printf("错误！请输入一个正数。\n\n");
			else
				break;
		}
		while (1)
		{
			printf("\n请输入此货物的供货商名称：\n");
			scanf("%s", p->supplier.name);
			if ((supplierIdx = GetSupplierIdx(p->supplier.name)) == -1)
				printf("未找到名为“%s”的供货商，请确认后重新输入。\n\n", p->supplier.name);
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
		printf("\n进货成功！");
	}
	if (isAutoSave)
		DataSave();
}

void InquirePurchaseRecord(record* head) //查询进货记录
{
	record* p = head;
	char c;
	printf("有以下三种查询方式：\n1.按时间查询\n2.按品种查询\n3.按供应商查询\n请您输入相应的序号来选择您的查询方式。\n");
	c = getch();
	switch (c - '0')
	{
	case 1: //按时间查询
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
			printf("未在该时间段内找到记录！");
		break;
	}
	case 2: //按品种查询
	{
		printf("请输入需要查询的货物及其品种的名称\n");
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
	case 3: //按供应商查询
	{
		printf("请输入需要查询的供应商的名称\n");
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
				printf("没有查询到相应的供应商,请重新输入\n");
			else
				break;
		}
		
		break;
	}
	}
}

void ModifyPurchaseRecord(record* head) //修改记录
{
	int del_num, i = 0, num;
	int goodsIdx = -1, varietyIdx = -1, supplierIdx = -1;
	record* p = head, * p0 = head;
	while (p->next != NULL)
	{
		i++;
		printf("%d.", i);
		printf("货物名称：%s;", p->goods.name);
		printf("所属品种：%s;", p->variety.name);
		printf("数量：%g;", p->num);
		printf("采购时间：");
		PrintTime(p->time);
		printf("\n");
		p = p->next;
	}
	printf("请输入想要删除的记录的序号及数量：");
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
	printf("删除成功！");
	if (isAutoSave)
		DataSave();
}
