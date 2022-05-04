#pragma once
#include "declare.h"

char systemPassword[MAXC];					//当前密码
FILE* ACCOUNT = fopen("account.txt", "a+"); //账户信息
FILE* SAVE = NULL;							//存档
int isAutoSave; //是否自动保存

double runFund = 500000;					//运行资金
double purchaseCost;						//进货花费
double saleIncome;							//售货收入

int isWholesale;							//是否为批发
double wholeSaleLimit;						//批发最小数量
double totalPrice;							//单次消费总额

double cheapLevel1 = 0.95; //折扣幅度
double cheapLevel2 = 0.9;
double cheapLevel3 = 0.8;
double offSeasonRate = 1.2; //反季售卖涨价幅度
double giveGiftLimit = 50;	//赠送赠品最小金额
double giveGiftRate = 15;	//所购商品总价与赠品进价倍数关系

record* purchaseRecord; //进货记录
record* sellRecord;		//销售记录
record* giftRecord;		//赠品记录
info* vipInfo;			//会员信息

goods stock[NUM];		//货物库存
merchant supplier[NUM]; //供货商
gift gifts[NUM];		//赠品库存