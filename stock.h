#ifndef _STOCK
#define _STOCK
#include<iostream>
#include<string>
#include"user.h"
class seller;
//要把amount改成单独文件
using namespace std;
class good 
{
public:
	void addtoStock(seller* aSeller);
	void modifyGood(seller* modder);
	static void sellerGoodChange(string goodName);
	static float getPrice(string goodName);
	virtual float getDiscount();
	void modDiscount();
	static int getgoodType(string goodName);
	void showGoods(string search, int* loginF, int method);//while循环显示一下 暂时不做排序了
	static bool isGoodExist(string goodName);
protected:
	string name;
	int amount;
	int basicprice;
	string info;
	string ownerName;
	int type;
	float discount;
};

class foods :public good
{
public:
	float getDiscount();
};
class clothes :public good
{
public:
	float getDiscount();
};
class books :public good
{
public:
	float getDiscount();
};
#endif // !_STOCK