#ifndef _ORDER
#define _ORDER
#include<iostream>
#include<string>
using namespace std;
#include"user.h"
#include"stock.h"
class consumer;
class lockgood;
class order
{
public:
	string goodName;
	string consumerName;
	int amount;
};

class cart
{
public:
	order Order;
	cart* next;
	static void addtoCart(string goodName, consumer* consumer, int amount);
	static int removeItem(string goodName, consumer* consumer, int amount);
	static void showCart(cart* startNode);
private:
};

class orderform
{
public:
	orderform* next;
	cart* comCart;
	static void createForm(consumer* consumer, lockgood* lockStart);
	static void payForm(int payID, consumer* consumer, lockgood* lockStart);
	static void cancelForm(int formID, consumer* consumer, lockgood* lockStart);
	float calFormPrice();
	static void showForms(consumer* consumer);
	static int getFormAmounts(consumer* consumer);
	static bool isFormExist(int formID, consumer* consumer);
	int formID;
private:
	string consumerName;
};

#endif