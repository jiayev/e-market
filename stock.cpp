#include<iostream>
#include<string>
#include<fstream>
#include"stock.h"
#define GTA 4

void good::addtoStock(seller* aSeller)
{
	string readName;
	string newName;
	string newInfo;
	float price;
	int amount;
	int readType= -1;
	fstream goodF;
	string readTmp;
	string fileName,fileName2;
	goodF.open("goodlist.txt", ios::in);
	cout << "请输入新货物的品名（没有空格）：";
	cin >> newName;
	while (!goodF.eof())
	{
		goodF >> readTmp >> readName >> readTmp >> readTmp;
		if (newName == readName)
		{
			goodF.close();
			goodF.open("goodlist.txt", ios::in);
			cout << "品名重复，请重新输入：";
			cin >> newName;
			continue;
		}
	}
	goodF.close();
	goodF.open("goodlist.txt", ios::app);
	
	while (readType != 0 && readType != 1 && readType != 2 && readType != 3)
	{
		cout << "请输入商品的类型，0为普通商品，1为食物，2为服装，3为图书\n";
		cin >> readType;
		if (readType != 0 && readType != 1 && readType != 2 && readType != 3) cout << "类型输入错误！\n";
	}
	cout << "请输入初始库存量：";
	cin >> amount;
	goodF << readType << " " << newName << " " << aSeller->name << endl;
	goodF.close();
	fileName = "goods\\" + to_string(readType) + "\\" + newName + ".txt";
	goodF.open(fileName, ios::out);
	cout << "请输入商品的基础价格：";
	cin >> price;
	cout << "请输入商品的信息：";
	cin.get();
	getline(cin,newInfo);
	goodF << price << " " << newInfo;
	fstream amountF;
	fileName2 = "goods\\" + to_string(readType) + "\\" + newName + "amount.txt";
	amountF.open(fileName2, ios::out);
	amountF << amount;
	amountF.close();
	goodF.close();
	cout << "商品创建成功！\n";
}

void good::modifyGood(seller* modder)
{
	string readName, modName, sellerName, readInfo, newInfo, readTmp, fileName, fileName2, readType;
	float readPrice, newPrice;
	int readAmount, newAmount;
	fstream goodF;
	cout << "请输入你要修改的商品名：";
	cin >> modName;
	goodF.open("goodlist.txt", ios::in);
	while (!goodF.eof())
	{
		goodF >> readType >> readName >> sellerName;
		if (modName == readName)
		{
			if (sellerName != modder->name)
			{
				cout << "此商品不属于你，返回\n";
				return;
			}
			goodF.close();
			fileName = "goods\\" + readType + "\\" + readName + ".txt";
			goodF.open(fileName, ios::in);
			goodF >> readPrice;
			goodF.get();
			fstream amountF;
			fileName2 = "goods\\" + readType + "\\" + readName + "amount.txt";
			amountF.open(fileName2, ios::in);
			amountF >> readAmount;
			amountF.close();
			getline(goodF,readInfo);
			newPrice = readPrice;
			newInfo = readInfo;
			newAmount = readAmount;
			int selectNum = 0;
			do
			{
				selectNum = 0;
				cout << "请输入你想要的操作：\n1.修改价格\n2.修改商品说明\n3.修改商品数量\n4.保存并返回\n5.撤销修改并返回\n";
				cin >> selectNum;
				if (selectNum == 1)
				{
					cout << "原基础价格为：" << readPrice << "元" << endl << "请输入新的基础价格：";
					cin >> newPrice;
				}
				if (selectNum == 2)
				{
					cout << "原说明为：" << readInfo << endl << "请输入新的说明：";
					cin.get();
					getline(cin, newInfo);
				}
				if (selectNum == 3)
				{
					cout << "原数量为：" << readAmount << endl << "请输入新的数量：";
					cin >> newAmount;
				}
				if (selectNum == 4)
				{
					goodF.close();
					goodF.open(fileName, ios::out);
					goodF.clear();
					goodF << newPrice << " " << newInfo;
					goodF.close();
					fstream amountF;
					fileName2 = "goods\\" + readType + "\\" + readName + "amount.txt";
					amountF.open(fileName2, ios::out);
					amountF << newAmount;
					amountF.close();
					return;
				}
			} while (selectNum != 5);
			return;
		}
	}
	cout << "你输入的商品不存在！\n";
}

void good::sellerGoodChange(string goodName)
{
	string readName, sellerName, readInfo, readTmp, fileName, fileName2, readType;
	float readPrice;
	int readAmount, newAmount;
	fstream goodF;
	goodF.open("goodlist.txt", ios::in);
	while (!goodF.eof())
	{
		goodF >> readType >> readName >> sellerName;
		if (goodName == readName)
		{
			goodF.close();
			fileName = "goods\\" + readType + "\\" + readName + ".txt";
			goodF.open(fileName, ios::in);
			goodF >> readPrice;
			goodF.get();
			fstream amountF;
			fileName2 = "goods\\" + readType + "\\" + readName + "amount.txt";
			amountF.open(fileName2, ios::in);
			amountF >> readAmount;
			newAmount = readAmount - 1;
			amountF.close();
			amountF.open(fileName2, ios::out);
			amountF.clear();
			amountF << newAmount;
			amountF.close();
			fstream userF1;
			string readPwd;
			float readBalance, addBalance, newBalance;
			string readTmp;
			string userFileName;
			userFileName = "user\\" + sellerName + ".txt";
			userF1.open(userFileName, ios::in);
			userF1 >> readPwd;
			userF1 >> readTmp >> readBalance;
			newBalance = readBalance + getPrice(goodName);
			userF1.close();
			userF1.open(userFileName, ios::out);
			userF1 << readPwd << " 1 " << newBalance;
			userF1.close();
			break;
		}
	}
}

float good::getPrice(string goodName)
{
	string readName, readTmp, fileName, readType;
	float readPrice;
	fstream goodF;
	goodF.open("goodlist.txt", ios::in);
	while (!goodF.eof())
	{
		goodF >> readType >> readName >> readTmp;
		if (goodName == readName)
		{
			goodF.close();
			fileName = "goods\\" + readType + "\\" + readName + ".txt";
			goodF.open(fileName, ios::in);
			goodF >> readPrice;
			goodF.close();
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
			return readPrice * goodP->getDiscount();
		}
	}
	return -1;
}

float good::getDiscount()
{
	float discount;
	fstream F1;
	F1.open("discount.txt", ios::in);
	F1 >> discount;
	F1.close();
	return discount;
}

void good::modDiscount()
{
	float discount[GTA];
	int i = 0, goodType;
	fstream F1;
	F1.open("discount.txt", ios::in);
	for (i = 0; i < GTA; i++)
	{
		F1 >> discount[i];
	}
	cout << "请输入你要打折的商品类型：0为普通商品，1为食物，2为服装，3为图书\n";
	cin >> goodType;
	cout << "请输入打折力度，1为原价，0为免费：";
	cin >> discount[goodType];
	F1.close();
	F1.open("discount.txt", ios::out);
	for (i = 0; i < GTA; i++)
	{
		F1 << discount[i];
	}
	F1.close();
}

int good::getgoodType(string goodName)
{
	fstream F1;
	string readName, readTemp;
	int readType;
	F1.open("goodlist.txt", ios::in);
	while (!F1.eof())
	{
		F1 >> readType >> readName >> readTemp;
		if (readName == goodName) return readType;
	}
	return 0;
}

void good::showGoods(string search, int* loginF, int method)//要写按情况判断输出项目
{
	fstream F1,F2;
	int readType, readAmount;
	string readName, readOwner, readInfo, fileName, fileName2, readTmp;
	F1.open("goodlist.txt", ios::in);
	while (!F1.eof())
	{
		F1 >> readType >> readName >> readOwner;
		fileName = "goods\\" + to_string(readType) + "\\" + readName + ".txt";
		F2.open(fileName, ios::in);
		F2 >> readTmp;
		F2.get();
		getline(F2, readInfo);
		F2.close();
		fstream amountF;
		fileName2 = "goods\\" + to_string(readType) + "\\" + readName + "amount.txt";
		amountF.open(fileName2, ios::in);
		amountF >> readAmount;
		amountF.close();
		if(!F1.eof()) 
			switch (method)
			{
			case 0:
				cout << readName << " " << getPrice(readName) << "元 库存：" << readAmount << " 个 商家：" << readOwner << " 商品描述：" << readInfo << endl;
				break;
			case 1:
				if (readName.find(search) != readName.npos) cout << readName << " " << getPrice(readName) << "元 库存：" << readAmount << " 个 商家：" << readOwner << " 商品描述：" << readInfo << endl;
				break;
			case 2:
				if (readOwner.find(search) != readOwner.npos) cout << readName << " " << getPrice(readName) << "元 库存：" << readAmount << " 个 商家：" << readOwner << " 商品描述：" << readInfo << endl;
				break;
			}
			
	}
}

bool good::isGoodExist(string goodName)
{
	fstream F1, F2;
	int readType, readAmount;
	string readName, readOwner;
	F1.open("goodlist.txt", ios::in);
	while (!F1.eof())
	{
		F1 >> readType >> readName >> readOwner;
		if (readName == goodName) 
		{ 
			F1.close();
			return true; 
		}
	}
	return false;
}

float foods::getDiscount()
{
	float discount;
	fstream F1;
	F1.open("discount.txt", ios::in);
	F1 >> discount >> discount;
	F1.close();
	return discount;
}

float clothes::getDiscount()
{
	float discount;
	fstream F1;
	F1.open("discount.txt", ios::in);
	F1 >> discount >> discount >> discount;
	F1.close();
	return discount;
}

float books::getDiscount()
{
	float discount;
	fstream F1;
	F1.open("discount.txt", ios::in);
	F1 >> discount >> discount >> discount >> discount;
	F1.close();
	return discount;
}