#include"user.h"

void user::createUser()
{
	string newName;
	string newPwd;
	string readName;
	string readTmp;
	string userFileName;
	fstream userF1;
	userF1.open("userlist.txt",ios::in);
	cout << "正在创建用户 用户名和密码仅支持字母和数字" << endl << "请输入用户名：";
	cin >> newName;
	while (!userF1.eof())
	{
		userF1 >> readName;
		if (readName == newName) 
		{
			cout << "用户名重复！请重新输入：";
			cin >> newName;
			userF1.close();
			userF1.open("userlist.txt", ios::in);
		}
	}//判断是否已有同用户名存在
	userF1.close();
	userF1.open("userlist.txt", ios::app);
	userF1 << newName << endl;//写入新用户名
	userF1.close();
	userFileName = "user\\" + newName + ".txt";
	userF1.open(userFileName, ios::app);
	cout << "请输入密码：";
	cin >> newPwd;
	userF1 << newPwd << " ";
	userF1 << getUserType() << " 0";
	userF1.close();//单独文件写入用户信息
}

void user::login(user* liUser, int* loginF, int typeNum)//要改
{
	string enterName;
	string enterPwd;
	string readName;
	string readPwd;
	string readStr;
	string readTmp;
	int readType;
	float readBalance;
	fstream userF1;
	string userFileName;
	userF1.open("userlist.txt",ios::in);
	cout << "正在登录" << endl << "请输入用户名：";
	cin >> enterName;
	while (enterName != readName)
	{
		if (userF1.eof()) 
		{
			cout << "您输入的用户不存在！请重新输入：";
			cin >> enterName;
			userF1.close();
			userF1.open("userlist.txt", ios::in);
			continue;
		}
		userF1 >> readName;
		if (enterName == readName) break;
	}//检测用户是否存在
	userF1.close();
	userFileName = "user\\" + readName + ".txt";
	userF1.open(userFileName, ios::in);
	cout << "请输入密码：";
	cin >> enterPwd;
	userF1 >> readPwd;
	int countdown = 3;
	while (readPwd != enterPwd)
	{
		countdown -= 1;
		if (countdown == 0)
		{
			cout << "密码错误3次，退回主界面！\n";
			delete liUser;
			return;
		}
		cout << "密码错误！请重新输入：";
		cin >> enterPwd;
	}//输入密码并判断
	userF1 >> readType >> readBalance;//将用户信息读入内存
	if (typeNum != readType)
	{
		cout << "用户类型错误，返回主菜单！\n";
		delete liUser;
		return;
	}
	liUser->name = enterName;
	liUser->balance = readBalance;
	userF1.close();
	*loginF = 1;
	cout << "登录成功！您是：";
	if (readType == 0)cout << "消费者\n";
	else cout << "商家\n";
}

void user::logout(user* loUser, int* loginF)
{
	delete loUser;
	*loginF = 0;
}

void user::changePwd(user* cpUser)
{
	fstream userF1;
	string readName;
	string readPwd;
	string readTmp;
	string oldPwd;
	string newPwd;
	string userFileName;
	userF1.open("userlist.txt", ios::in);
	userF1 >> readName;
	while (readName != cpUser->name)
		userF1 >> readName;
	cout << "请输入原密码：";
	cin >> oldPwd;
	userFileName = "user\\" + readName + ".txt";
	userF1.close();
	userF1.open(userFileName, ios::in|ios::out);
	userF1 >> readPwd;//根据用户名读取原密码
	int countdown = 3;
	while (oldPwd != readPwd)
	{
		countdown -= 1;
		if (countdown == 0)
		{
			cout << "密码错误3次，退回主界面！\n";
			return;
		}
		cout << "原密码错误！请重新输入：";
		cin >> oldPwd;
	}
	cout << "请输入新密码：";
	cin >> cpUser->password;
	userF1.close();
	userF1.open(userFileName, ios::out);
	userF1 << cpUser->password << " " << cpUser->getUserType() << " " << cpUser->balance;//写入新的用户信息
	cout << "修改成功！" << endl;
	userF1.close();
}

void user::addFund(user* afUser)
{
	fstream userF1;
	string readPwd;
	float readBalance, addBalance, newBalance;
	string readTmp;
	string Pwd;
	string userFileName;
	userFileName = "user\\" + afUser->name + ".txt";
	userF1.open(userFileName, ios::in);
	userF1 >> readPwd;
	cout << "请输入密码：";
	cin >> Pwd;
	int countdown = 3;
	while (Pwd != readPwd)
	{
		countdown -= 1;
		if (countdown == 0)
		{
			cout << "密码错误3次，退回主界面！\n";
			return;
		}
		cout << "密码错误！请重新输入：";
		cin >> Pwd;
	}
	cout << "请输入充值数：";
	userF1 >> readTmp >> readBalance;
	cin >> addBalance;
	newBalance = readBalance + addBalance;
	userF1.close();
	userF1.open(userFileName, ios::out);
	userF1 << readPwd << " " << afUser->getUserType() << " " << newBalance;
	afUser->balance = newBalance;
	cout << "充值成功！" << endl;
	userF1.close();
}

/*int user::getUserType()
{
	return -1;
}*/

void user::showUserInfo(user* uInfo, int* loginF)
{
	if (*loginF == 0) 
	{
		cout << "您当前未登录！\n";
		return;
	}
	cout << "当前用户的用户名是：" << uInfo->name << "\n当前用户的余额是：" << uInfo->balance << " 元\n当前用户的用户类型是：";
	if (getUserType() == 0) cout << "消费者";
	else cout << "商家";
	cout << endl;
}

void user::userBalanceChange(user* bcUser, float change)
{
	fstream userF1;
	string readPwd;
	float readBalance, addBalance, newBalance;
	string readTmp;
	string userFileName;
	userFileName = "user\\" + bcUser->name + ".txt";
	userF1.open(userFileName, ios::in);
	userF1 >> readPwd;
	userF1 >> readTmp >> readBalance;
	newBalance = readBalance + change;
	userF1.close();
	userF1.open(userFileName, ios::out);
	userF1 << readPwd << " " << bcUser->getUserType() << " " << newBalance;
	userF1.close();
	bcUser->balance = newBalance;
}

int consumer::buyGood(consumer* buyer, string goodName, int amount)
{
	good* goodP = new good;
	switch (good::getgoodType(goodName))
	{
	case 0:
		delete goodP;
		goodP = new good;
		break;
	case 1:
		delete goodP;
		goodP = new foods;
		break;
	case 2:
		delete goodP;
		goodP = new clothes;
		break;
	case 3:
		delete goodP;
		goodP = new books;
		break;
	}
	if (goodP->getPrice(goodName) * amount <= buyer->balance)
	{
		userBalanceChange(buyer, -(goodP->getPrice(goodName) * amount));
		for (int i = 0; i < amount; i++)
		{
			good::sellerGoodChange(goodName);
		}
		return 0;
	}
	else return -1;
}

int consumer::getUserType()
{
	return 0;
}

int seller::getUserType()
{
	return 1;
}
