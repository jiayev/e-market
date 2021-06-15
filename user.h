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
	void createUser();//创建新用户
	void login(user* liUser, int* loginF, int typeNum);//登陆
	void logout(user* loUser, int* loginF);//登出
	void changePwd(user* cpUser);//修改密码
	void addFund(user* afUser);//充值
	virtual int getUserType()=0;//提取用户类型
	void showUserInfo(user* uInfo, int* loginF);//显示用户信息
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

