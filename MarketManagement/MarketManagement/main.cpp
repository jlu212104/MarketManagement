#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

#include "struct.h"
#include "globalval.h"

int main()
{
	DataInit();
	printf("\n\n\n\t******欢迎使用果蔬超市管理系统******\n\n\n\n");

	if (fgetc(ACCOUNT) == EOF)
	{
		printf("初次使用本系统，需要设置管理员初始密码。\n");
		printf("按任意键进入密码设置界面>>>");
		getch();
		system("cls");
		if (SetPassword())
		{
			printf("\n密码设置成功！请按任意键进入系统>>>");
			getch();
			system("cls");
		}
		else
		{
			printf("\nERROR:PASSWORD SETTING FAILED");
			exit(0);
		}
	}
	rewind(ACCOUNT);
	if (fgets(systemPassword, MAXC, ACCOUNT))
		fclose(ACCOUNT);
	else
	{
		printf("\nERROR:FILE CANNOT BE LOADED");
		exit(0);
	}

	while (1)
	{
		printf("***请选择身份***\n\n");
		printf("1. 管理员\n2. 售货员");
		char op = 0;
		while (1)
		{
			op = getch();
			if (op < '1' || op > '2')
				printf("\n操作错误！请按下1~2范围内的数字>>>");
			else
				break;
		}
		if (op == '1') //管理员
		{
			system("cls");
			SignIn();
			while (1)
			{
				printf("**********管理员界面**********\n");
				printf("1.进货相关操作\n");
				printf("2.库存情况查询\n");
				printf("3.销售记录查询\n");
				printf("4.会员信息查询\n");
				printf("5.营业情况查询\n");
				printf("6.促销相关操作\n");
				printf("7.系统设置\n");
				printf("8.返回主菜单\n");
				printf("9.保存并退出系统\n");
				printf("*****************************\n\n");
				printf("请按下数字键进入相应菜单>>>");

				while (1)
				{
					op = getch();
					if (op < '1' || op > '9')
						printf("\n操作错误！请按下1~9范围内的数字>>>");
					else
						break;
				}
				system("cls");
				if (op == '8') //返回主菜单
					break;

				switch (op - '0')
				{
				case 1: //进货相关操作
				{
					while (1)
					{
						printf("**********进货相关操作**********\n");
						printf("1.查询货物信息\n");
						printf("2.查询品种信息\n");
						printf("3.查询商家信息\n");
						printf("4.增添货物\n");
						printf("5.删减货物\n");
						printf("6.查询进货记录\n");
						printf("7.返回上一级菜单\n");
						printf("*******************************\n");
						printf("请按下数字键进入相应菜单>>>");

						while (1)
						{
							op = getch();
							if (op < '1' || op > '7')
								printf("\n操作错误！请按下1~7范围内的数字>>>");
							else
								break;
						}
						system("cls");
						if (op == '7') //返回上一级菜单
							break;

						switch (op - '0')
						{
						case 1: //查询货物信息
							InquireCargo();
							Back();
							break;
						case 2: //查询品种信息
							InquireVariety();
							Back();
							break;
						case 3: //查询商家信息
							InquireMerchant();
							Back();
							break;
						case 4: //增添货物
							Purchase(purchaseRecord);
							Back();
							break;
						case 5: //删减货物
							ModifyPurchaseRecord(purchaseRecord);
							Back();
							break;
						case 6: //查询进货记录
							InquirePurchaseRecord(purchaseRecord);
							Back();
							break;
						}
					}
					break;
				}
				case 2: //库存情况查询
				{
					while (1)
					{
						printf("**********库存情况查询**********\n");
						printf("1.按序号查询\n");
						printf("2.按名称查询\n");
						printf("3.按供货商查询\n");
						printf("4.返回上一级菜单\n");
						printf("*****************************\n\n");
						printf("请按下数字键进入相应菜单>>>");

						while (1)
						{
							op = getch();
							if (op < '1' || op > '4')
								printf("\n操作错误！请按下1~4范围内的数字>>>");
							else
								break;
						}
						system("cls");
						if (op == '4') //返回主菜单
							break;

						InquireStock(op); //参数为查询方式
						Back();
					}
					break;
				}
				case 3: //销售记录查询
				{
					while (1)
					{
						printf("**********销售记录查询**********\n");
						printf("1.按时间范围查询\n");
						printf("2.按名称查询\n");
						printf("3.返回上一级菜单\n");
						printf("*****************************\n\n");
						printf("请按下数字键进入相应菜单>>>");

						while (1)
						{
							op = getch();
							if (op < '1' || op > '3')
								printf("\n操作错误！请按下1~3范围内的数字>>>");
							else
								break;
						}
						system("cls");
						if (op == '3') //返回主菜单
							break;

						InquireSellRecord(sellRecord, op);
						Back();
					}
					break;
				}
				case 4: //会员信息查询
				{
					while (1)
					{
						printf("**********会员信息查询**********\n");
						printf("1.查看会员资料\n");
						printf("2.查看购买记录\n");
						printf("3.返回主菜单\n");
						printf("*****************************\n\n");
						printf("请按下数字键进入相应菜单>>>");
						while (1)
						{
							op = getch();
							if (op < '1' || op > '3')
								printf("\n操作错误！请按下1~3范围内的数字>>>");
							else
								break;
						}
						system("cls");
						if (op == '3') //返回主菜单
							break;

						switch (op - '0')
						{
						case 1:
							InquireVipInfo();
							break;
						case 2:
							InquireBuyRecord();
							break;
						}
						Back();
					}
					break;
				}
				case 5: //营业情况查询
				{
					printf("**********营业情况**********\n");
					printf("当前运行资金：%g元\n其中：\n", runFund - purchaseCost + saleIncome);
					printf("\t进货共花费：%g元\n", purchaseCost);
					printf("\t售货共获得：%g元\n", saleIncome);
					printf("\t净利润为：%g元\n", saleIncome - purchaseCost);
					Back();
					break;
				}
				case 6: //促销策略设置
				{
					while (1)
					{
						printf("**********促销策略设置**********\n");
						printf("1.修改优惠策略第一级\n");
						printf("2.修改优惠策略第二级\n");
						printf("3.修改优惠策略第三级\n");
						printf("4.返回主菜单\n");
						printf("*****************************\n\n");
						printf("请按下数字键进入相应菜单>>>");
						while (1)
						{
							op = getch();
							if (op < '1' || op > '4')
								printf("\n操作错误！请按下1~4范围内的数字>>>");
							else
								break;
						}
						system("cls");
						if (op == '4') //返回主菜单
							break;

						SetDiscount(op);
						Back();
					}
					break;
				}
				case 7: //系统设置
				{
					while (1)
					{
						printf("**********系统设置**********\n");
						printf("1.密码修改\n");
						printf("2.自动保存\n");
						printf("3.清除记录\n");
						printf("4.返回上一级菜单\n");
						printf("***************************\n\n");
						printf("请按下数字键进入相应菜单>>>");
						while (1)
						{
							op = getch();
							if (op < '1' || op > '4')
								printf("\n操作错误！请按下1~4范围内的数字>>>");
							else
								break;
						}
						system("cls");
						if (op == '4')
							break;

						switch (op - '0')
						{
						case 1: //密码修改
						{
							while (1)
							{
								printf("如需返回上一级菜单请直接按下回车...\n");
								printf("请输入原密码：");
								char oldPassword[MAXC] = {0};
								if (!GetPassword(oldPassword))
								{
									system("cls");
									break;
								}
								if (strcmp(oldPassword, systemPassword))
								{
									printf("\n密码错误！按任意键重新输入>>>");
									getch();
									system("cls");
								}
								else
									break;
							}
							printf("\n");
							ACCOUNT = fopen("account.txt", "w+");
							if (SetPassword() && fclose(ACCOUNT) == 0)
								printf("\n密码修改成功！请按任意键返回菜单>>>");
							else
							{
								printf("ERROR:PASSWORD SETTING FAILED");
								exit(0);
							}
							getch();
							system("cls");
							break;
						}
						case 2: //自动保存
						{
							if (isAutoSave)
							{
								printf("目前自动保存功能已开启。\n");
								printf("是否关闭？关闭请按1，开启请按除1以外的任意键>>>");
								if (getch() == '1')
									isAutoSave = 0;
							}
							else
							{
								printf("目前自动保存功能已关闭。\n");
								printf("是否开启？开启请按1，关闭请按除1以外的任意键>>>");
								if (getch() == '1')
									isAutoSave = 1;
							}
							break;
						}
						case 3: //清除记录
						{
							printf("警告：此操作将清除系统中所有记录！\n");
							printf("是否继续？确认请按Y，取消请按除Y外的任意键>>>\n");
							if (getch() == 'Y')
							{
								ReleaseRecord(purchaseRecord);
								ReleaseRecord(sellRecord);
								ReleaseRecord(giftRecord);
								ReleaseInfo(vipInfo);
							}
							break;
						}
						}
					}
					break;
				}
				case 9: //保存并退出系统
				{
					DataSave();
					ReleaseRecord(purchaseRecord);
					ReleaseRecord(sellRecord);
					ReleaseRecord(giftRecord);
					ReleaseInfo(vipInfo);
					exit(0);
				}
				}
			}
		}
		else if (op == '2') //售货员
		{
			while (1)
			{
				system("cls");
				printf("**********售货员界面**********\n");
				printf("1.零售\n");
				printf("2.批发\n");
				printf("3.会员中心\n");
				printf("4.返回主菜单\n");
				printf("5.保存并退出系统\n");
				printf("*****************************\n\n");
				printf("请按下数字键进入相应菜单>>>");

				while (1)
				{
					op = getch();
					if (op < '1' || op > '5')
						printf("\n操作错误！请按下1~5范围内的数字>>>");
					else
						break;
				}
				system("cls");
				if (op == '4')
					break;
				isWholesale = 0;
				switch (op - '0')
				{
				case 2: //批发
					isWholesale = 1;
				case 1: //零售
				{
					while (1)
					{
						printf("**********售货**********\n");
						printf("1.读入商品条码\n");
						printf("2.直接读入信息\n");
						printf("3.返回上一级菜单\n");
						printf("************************\n\n");
						printf("请按下数字键进入相应菜单>>>");

						while (1)
						{
							op = getch();
							if (op < '1' || op > '3')
								printf("\n操作错误！请按下1~3范围内的数字>>>");
							else
								break;
						}
						system("cls");
						if (op == '3') //返回主菜单
							break;

						Sell(op - '0');
						Back();
					}
					break;
				}
				case 3: //会员中心
				{
					while (1)
					{
						printf("**********会员中心**********\n");
						printf("1.开通会员\n");
						printf("2.积分查询\n");
						printf("3.礼品兑换\n");
						printf("4.会员注销\n");
						printf("5.返回上一级菜单\n");
						printf("***************************\n\n");
						printf("请按下数字键进入相应菜单>>>");

						while (1)
						{
							op = getch();
							if (op < '1' || op > '5')
								printf("\n操作错误！请按下1~5范围内的数字>>>");
							else
								break;
						}
						system("cls");
						if (op == '5') //返回主菜单
							break;

						switch (op - '0')
						{
						case 1:
							AddVip(vipInfo);
							Back();
							break;
						case 2:
							InquireVipPoints(vipInfo);
							Back();
							break;
						case 3:
							ExchangeGift();
							Back();
							break;
						case 4:
							DelVip(vipInfo);
							Back();
							break;
						}
					}
					break;
				}
				case 5: //保存并退出系统
				{
					CheckStock(purchaseRecord);
					DataSave();
					ReleaseRecord(purchaseRecord);
					ReleaseRecord(sellRecord);
					ReleaseRecord(giftRecord);
					ReleaseInfo(vipInfo);
					exit(0);
				}
				}
			}
		}
	}
	return 0;
}
