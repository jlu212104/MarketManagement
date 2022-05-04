#pragma once
#include "declare.h"

struct Variety //品种
{
	char name[MAXC];	  //名称
	double num;			  //库存数量
	double purchasePrice; //进价
	double price;		  //售价
	int shelfLife;		  //保质期
	int season;			  //成熟季节
	char origin[MAXC];	  //原产地
};

struct Goods //货物
{
	char name[MAXC];	  //名称
	int varietyNum;		  //品种数量
	struct Variety variety[NUM]; //品种
};

struct Merchant //商家
{
	char name[MAXC];  //名称
	char tel[MAXC];	  //联系电话
	struct Goods stock[NUM]; //库存
};

struct Gift //赠品
{
	char name[MAXC];	  //名称
	int num;			  //库存数量
	double purchasePrice; //进价
};

struct Record //记录（链表实现）
{
	tm *time;				  //时间
	char recordNum[MAXC];	  //编号
	struct Goods goods;			  //货物
	struct Variety variety;		  //品种
	struct Gift gift;				  //赠品
	double num;				  //数量
	double price;			  //售价
	struct Merchant supplier;		  //供货商
	int isWholeSale;		  //是否为批发
	char sellRecordNum[MAXC]; //销售记录编号
	struct Record *next;
};

struct Information //信息（链表实现）
{
	char num[MAXC];			  //编号
	char name[MAXC];		  //姓名
	int sex;				  //性别（男0女1）
	char tel[MAXC];			  //联系电话
	int points;				  //积分
	int level;				  //等级（1、2、3分别对应普通、白金、钻石会员）
	tm *time;				  //时间
	struct Record *buyRecord; //会员的购买记录
	struct Information *next;
};
