#pragma once
#ifndef _ORDER
#define _ORDER
#include<iostream>
#include<string>
using namespace std;
#include"user.h"
#include"stock.h"
class consumer;
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
	static void addtoCart(string goodName, consumer* consumer, int amount, cart* start);
	static void removeItem(string goodName, consumer* consumer, int amount, cart* start);
	static void payCart(consumer* consumer);
private:
};



#endif