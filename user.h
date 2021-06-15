#ifndef _user
#define _user
#include<iostream>
#include<string>
#include<fstream>
#include"stock.h"
#include"order.h"
using namespace std;
class good;
class cart;
class orderform;
class user
{
public:
	float balance;
	string name;
	void createUser();//�������û�
	static void login(user* liUser, int* loginF, int typeNum);//��½
	static void logout(user* loUser, int* loginF);//�ǳ�
	void changePwd(user* cpUser);//�޸�����
	void addFund(user* afUser);//��ֵ
	virtual int getUserType()=0;//��ȡ�û�����
	void showUserInfo(user* uInfo, int* loginF);//��ʾ�û���Ϣ
	static void userBalanceChange(user* bcUser, float change);
protected:
	string password;
private:
};


class consumer : public user 
{
public:
	int buyGood(consumer* buyer, string goodName, int amount);
	int getUserType();
	cart* startNode;
	orderform* startForm;
	//consumer();
private:

};

//consumer::consumer(void)
//{
//	startNode->next = NULL;
//}

class seller :public user
{
public:
	int getUserType();
private:
};
#endif

