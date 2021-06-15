#ifndef _user
#define _user
#include<iostream>
#include<string>
#include<fstream>
#include"stock.h"

using namespace std;
class good;
class cart;
class user
{
public:
	float balance;
	string name;
	void createUser();//�������û�
	void login(user* liUser, int* loginF, int typeNum);//��½
	void logout(user* loUser, int* loginF);//�ǳ�
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
private:

};

class seller :public user
{
public:
	int getUserType();
private:
};
#endif

