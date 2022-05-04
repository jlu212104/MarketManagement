#pragma once

#define MAXN 65536 // int数组大小
#define MAXC 256   // char数组大小
#define NUM 10	   //果蔬种类及供货商数量

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

typedef struct Merchant merchant;
typedef struct Variety variety;
typedef struct Goods goods;
typedef struct Gift gift;
typedef struct Record record;
typedef struct Information info;

extern FILE *ACCOUNT;
extern FILE* SAVE;
extern char systemPassword[];
extern int isAutoSave;

extern double runFund;
extern double purchaseCost;
extern double saleIncome;
extern double totalPrice;

extern int isWholesale;
extern double wholeSaleLimit;
extern double cheapLevel1;
extern double cheapLevel2;
extern double cheapLevel3;
extern double offSeasonRate;
extern double giveGiftLimit;
extern double giveGiftRate;

extern record *purchaseRecord;
extern record *sellRecord;
extern record *giftRecord;
extern info *vipInfo;
enum RECORD
{
	PURCHASERECORD = 0,
	SELLRECORD,
	GIFTRECORD
};

extern goods stock[];
extern merchant supplier[];
extern gift gifts[];

void Back();

tm *NowTime();
void PrintTime(tm *);
void ScanTime(tm *);
int CompareTime(tm *, tm *);

int SetPassword();
int GetPassword(char *);
void SignIn();

void DataInit();
void DataSave();
void ReadRecord(const int);
void ReadInfo(info *);
void WriteRecord(record *);
void WriteInfo(info *);
void ReleaseRecord(record *);
void ReleaseInfo(info *);

int GetGoodsIdx(char *);
int GetVarietyIdx(int, char *);
int GetSupplierIdx(char *);
info *GetVipNode(info *);
const char* GetSeason(int);
const char* GetVipLevel(int);

void InquireCargo();
void InquireVariety();
void InquireMerchant();
void InquirePurchaseRecord(record *);
void InquireStock(char);
void InquireSellRecord(record *, char);
void InquireVipInfo();
void InquireBuyRecord();

void PrintPurchaseRecord(record *, int);
void PrintSellRecord(record *);

void Purchase(record *);
void ModifyPurchaseRecord(record *);

void SetDiscount(char);
int IsOffSeason(variety);

void Sell(int);
int IsNumber(char *);
int GetBarCode(record *, char *);
int GetGoodsInfo(record *, char *);
char *GetRecordNum(record *);
void AddBuyRecord(record *, char *);
double Discount(info *, record *);
void GiveGift(record *, record *, int);

void AddVip(info *);
void DelVip(info *);
char *GetVipNum(info *);
char *TransformNumIntoStr(int);
int GetNextNum(char *);
void InquireVipPoints(info *);
void ExchangeGift();

void CheckStock(record *);
int IsStale(int, int, int, int, int);