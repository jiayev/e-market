#ifndef _STOCK
#define _STOCK
#include<iostream>
#include<string>
#include"user.h"
class seller;
//Ҫ��amount�ĳɵ����ļ�
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
	void showGoods(string search, int* loginF, int method);//whileѭ����ʾһ�� ��ʱ����������
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