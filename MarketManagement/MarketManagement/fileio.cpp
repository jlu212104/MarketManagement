#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

#include "struct.h"

void DataInit() //数据初始化
{
	while (1)
	{
		char fileName[MAXC] = "default.txt";
		char ch = 0;
		printf("请输入要读入的数据库文件名，如读取默认文件可直接按下回车>>>");
		if ((ch = getchar()) != '\n')
		{
			memset(fileName, 0, MAXC);
			fileName[0] = ch;
			int idx = 1;
			while ((fileName[idx] = getchar()) != '\n')
				idx++;
			fileName[idx] = 0;
		}
		if ((SAVE = fopen(fileName, "r+")) == NULL)
		{
			memset(fileName, 0, MAXC);
			printf("文件打开失败！按任意键返回>>>");
			getch();
			system("cls");
		}
		else
			break;
	}
	rewind(SAVE);
	int i = 0, j = 0, k = 0;
	for (i = 0; i < NUM; i++)
	{
		fscanf(SAVE, "%s", stock[i].name);
		fscanf(SAVE, "%d", &(stock[i].varietyNum));
		for (j = 0; j < stock[i].varietyNum; j++) //读取库存信息
		{
			variety* p = &(stock[i].variety[j]);
			fscanf(SAVE, "%s", p->name);
			fscanf(SAVE, "%lf%lf%lf%d%d", &(p->num), &(p->purchasePrice), &(p->price), &(p->shelfLife), &(p->season));
			fscanf(SAVE, "%s", p->origin);
		}
	}
	for (i = 0; i < NUM; i++) //读取供货商信息
	{
		fscanf(SAVE, "%s%s", supplier[i].name, supplier[i].tel);
		for (j = 0; j < NUM; j++)
		{
			strcpy(supplier[i].stock[j].name, stock[j].name);
			supplier[i].stock[j].varietyNum = stock[j].varietyNum;
			for (k = 0; k < stock[j].varietyNum; k++)
				strcpy(supplier[i].stock[j].variety[k].name, stock[j].variety[k].name);
		}
	}
	for (i = 0; i < NUM; i++) //读取赠品信息
	{
		fscanf(SAVE, "%s%d%lf", gifts[i].name, &(gifts[i].num), &(gifts[i].purchasePrice));
		purchaseCost += gifts[i].purchasePrice * gifts[i].num;
	}
	ReadRecord(PURCHASERECORD);
	ReadRecord(SELLRECORD);
	ReadRecord(GIFTRECORD);
	ReadInfo(vipInfo);
	if (fclose(SAVE) == 0)
		printf("数据读入成功！请按任意键进入系统>>>");
	getch();
	system("cls");
}

void DataSave() //保存数据
{
	while (1)
	{
		char fileName[MAXC] = "default.txt";
		char ch = 0;
		int idx = 1;
		printf("请输入要存入的数据库文件名（txt文件），如存入默认文件可直接按下回车>>>");
		if ((ch = getchar()) != '\n')
		{
			memset(fileName, 0, MAXC);
			fileName[0] = ch;
			while ((fileName[idx] = getchar()) != '\n')
				idx++;
			fileName[idx] = 0;
		}
		char strTemp[MAXC] = { 0 };
		strncpy(strTemp, fileName + idx - 4, 4);
		strTemp[4] = 0;
		if (strcmp(strTemp, ".txt") && strcmp(fileName, "default.txt"))
		{
			printf("请输入以“.txt”为后缀的文件名！按任意键返回>>>");
			getch();
			system("cls");
		}
		else
		{
			SAVE = fopen(fileName, "w+");
			break;
		}
	}
	rewind(SAVE);
	int i = 0, j = 0;
	for (i = 0; i < NUM; i++)
	{
		fprintf(SAVE, "%s ", stock[i].name);
		fprintf(SAVE, "%d\n", stock[i].varietyNum);
		for (j = 0; j < stock[i].varietyNum; j++) //写入库存信息
		{
			variety* p = &stock[i].variety[j];
			fprintf(SAVE, "%s ", p->name);
			fprintf(SAVE, "%g %g %g %d %d ", p->num, p->purchasePrice, p->price, p->shelfLife, p->season);
			fprintf(SAVE, "%s\n", p->origin);
		}
	}
	fprintf(SAVE, "\n");
	for (i = 0; i < NUM; i++) //写入供货商信息
		fprintf(SAVE, "%s %s\n", supplier[i].name, supplier[i].tel);
	fprintf(SAVE, "\n");
	for (i = 0; i < NUM; i++) //写入赠品信息
		fprintf(SAVE, "%s %d %g\n", gifts[i].name, gifts[i].num, gifts[i].purchasePrice);
	fprintf(SAVE, "\n");
	WriteRecord(purchaseRecord);
	WriteRecord(sellRecord);
	WriteRecord(giftRecord);
	WriteInfo(vipInfo);
	if (fclose(SAVE) == 0)
		printf("数据存储成功！请按任意键继续>>>");
	getch();
}

void ReadRecord(const int RECORD) //从文件中读取记录链表
{
	record* head = NULL, * p = NULL, * rear = NULL;
	while (1)
	{
		p = (record*)malloc(sizeof(record));
		if (p != NULL)
		{
			if (RECORD == GIFTRECORD)
			{
				fscanf(SAVE, "%s", p->gift.name);
				if (*(p->gift.name) == '#')
					break;
				fscanf(SAVE, "%s", (char*)p->sellRecordNum);
			}
			else
			{
				fscanf(SAVE, "%s", p->goods.name);
				if (*(p->goods.name) == '#')
					break;
				fscanf(SAVE, "%s", p->variety.name);
				int goodsIdx = GetGoodsIdx(p->goods.name);
				int varietyIdx = GetVarietyIdx(goodsIdx, p->variety.name);
				p->goods = stock[goodsIdx];
				p->variety = stock[goodsIdx].variety[varietyIdx];
				fscanf(SAVE, "%lf", &(p->num));
				if (RECORD == PURCHASERECORD)
				{
					purchaseCost += p->variety.purchasePrice * p->num;
					fscanf(SAVE, "%s", p->supplier.name);
					int supplierIdx = GetSupplierIdx(p->supplier.name);
					p->supplier = supplier[supplierIdx];
					supplier[supplierIdx].stock[goodsIdx].variety[varietyIdx].num += p->num;
				}
				p->time = (tm*)malloc(sizeof(tm));
				if (p->time != NULL)
					fscanf(SAVE, "%d%d%d%d", &(p->time->tm_mon), &(p->time->tm_mday), &(p->time->tm_hour), &(p->time->tm_min));
				if (RECORD == SELLRECORD)
				{
					fscanf(SAVE, "%d%s", &(p->isWholeSale), p->recordNum);
					saleIncome += p->variety.price * p->num;
				}
			}
			if (head == NULL)
			{
				head = p;
				switch (RECORD)
				{
				case PURCHASERECORD:
					purchaseRecord = head;
					break;
				case SELLRECORD:
					sellRecord = head;
					break;
				case GIFTRECORD:
					giftRecord = head;
					break;
				}
			}
			else if (rear != NULL)
				rear->next = p;
			p->next = NULL;
			rear = p;
		}
	}
}

void ReadInfo(info* head) //从文件中读取信息链表
{
	info* p = NULL, * rear = NULL;
	while (1)
	{
		p = (info*)malloc(sizeof(info));
		if (p != NULL)
		{
			fscanf(SAVE, "%s", p->num);
			if (*(p->num) == '#')
				break;
			fscanf(SAVE, "%s%s", p->name, p->tel);
			fscanf(SAVE, "%d", &(p->sex));
			fscanf(SAVE, "%d", &(p->points));
			fscanf(SAVE, "%d", &(p->level));
			p->time = (tm*)malloc(sizeof(tm));
			if (p->time != NULL)
				fscanf(SAVE, "%d%d%d%d", &(p->time->tm_mon), &(p->time->tm_mday), &(p->time->tm_hour), &(p->time->tm_min));
			p->buyRecord = NULL;
			record* qrear = NULL;
			while (1)
			{
				record* q = (record*)malloc(sizeof(record));
				if (q != NULL)
				{
					fscanf(SAVE, "%s", q->sellRecordNum);
					if (*(q->sellRecordNum) == '#')
						break;
					if (p->buyRecord == NULL)
						p->buyRecord = q;
					else if (qrear != NULL)
						qrear->next = q;
					q->next = NULL;
					qrear = q;
				}
			}

			if (vipInfo == NULL)
				vipInfo = p;
			else if (rear != NULL)
				rear->next = p;
			p->next = NULL;
			rear = p;
		}
	}
}

void WriteRecord(record* head) //将记录链表存储至文件
{
	record* p = head;
	while (p)
	{
		if (head == giftRecord)
			fprintf(SAVE, "%s %s", p->gift.name, p->sellRecordNum);
		else
		{
			fprintf(SAVE, "%s %s ", p->goods.name, p->variety.name);
			fprintf(SAVE, "%g ", p->num);
			if (head == purchaseRecord)
				fprintf(SAVE, "%s ", p->supplier.name);
			fprintf(SAVE, "%d %d %d %d", p->time->tm_mon, p->time->tm_mday, p->time->tm_hour, p->time->tm_min);
			if (head == sellRecord)
				fprintf(SAVE, " %d %s", p->isWholeSale, p->recordNum);
		}
		fprintf(SAVE, "\n");
		p = p->next;
	}
	fprintf(SAVE, "#\n");
}

void WriteInfo(info* head) //将信息链表存储至文件
{
	info* p = head;
	while (p)
	{
		fprintf(SAVE, "%s %s %s ", p->num, p->name, p->tel);
		fprintf(SAVE, "%d %d %d ", p->sex, p->points, p->level);
		fprintf(SAVE, "%d %d %d %d\n", p->time->tm_mon, p->time->tm_mday, p->time->tm_hour, p->time->tm_min);
		record* q = p->buyRecord;
		while (q != NULL)
		{
			fprintf(SAVE, "%s\n", q->sellRecordNum);
			q = q->next;
		}
		fprintf(SAVE, "#\n");
		p = p->next;
	}
	fprintf(SAVE, "#\n");
}