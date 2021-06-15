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
	cout << "�������»����Ʒ����û�пո񣩣�";
	cin >> newName;
	while (!goodF.eof())
	{
		goodF >> readTmp >> readName >> readTmp >> readTmp;
		if (newName == readName)
		{
			goodF.close();
			goodF.open("goodlist.txt", ios::in);
			cout << "Ʒ���ظ������������룺";
			cin >> newName;
			continue;
		}
	}
	goodF.close();
	goodF.open("goodlist.txt", ios::app);
	
	while (readType != 0 && readType != 1 && readType != 2 && readType != 3)
	{
		cout << "��������Ʒ�����ͣ�0Ϊ��ͨ��Ʒ��1Ϊʳ�2Ϊ��װ��3Ϊͼ��\n";
		cin >> readType;
		if (readType != 0 && readType != 1 && readType != 2 && readType != 3) cout << "�����������\n";
	}
	cout << "�������ʼ�������";
	cin >> amount;
	goodF << readType << " " << newName << " " << aSeller->name << endl;
	goodF.close();
	fileName = "goods\\" + to_string(readType) + "\\" + newName + ".txt";
	goodF.open(fileName, ios::out);
	cout << "��������Ʒ�Ļ����۸�";
	cin >> price;
	cout << "��������Ʒ����Ϣ��";
	cin.get();
	getline(cin,newInfo);
	goodF << price << " " << newInfo;
	fstream amountF;
	fileName2 = "goods\\" + to_string(readType) + "\\" + newName + "amount.txt";
	amountF.open(fileName2, ios::out);
	amountF << amount;
	amountF.close();
	goodF.close();
	cout << "��Ʒ�����ɹ���\n";
}

void good::modifyGood(seller* modder)
{
	string readName, modName, sellerName, readInfo, newInfo, readTmp, fileName, fileName2, readType;
	float readPrice, newPrice;
	int readAmount, newAmount;
	fstream goodF;
	cout << "��������Ҫ�޸ĵ���Ʒ����";
	cin >> modName;
	goodF.open("goodlist.txt", ios::in);
	while (!goodF.eof())
	{
		goodF >> readType >> readName >> sellerName;
		if (modName == readName)
		{
			if (sellerName != modder->name)
			{
				cout << "����Ʒ�������㣬����\n";
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
				cout << "����������Ҫ�Ĳ�����\n1.�޸ļ۸�\n2.�޸���Ʒ˵��\n3.�޸���Ʒ����\n4.���沢����\n5.�����޸Ĳ�����\n";
				cin >> selectNum;
				if (selectNum == 1)
				{
					cout << "ԭ�����۸�Ϊ��" << readPrice << "Ԫ" << endl << "�������µĻ����۸�";
					cin >> newPrice;
				}
				if (selectNum == 2)
				{
					cout << "ԭ˵��Ϊ��" << readInfo << endl << "�������µ�˵����";
					cin.get();
					getline(cin, newInfo);
				}
				if (selectNum == 3)
				{
					cout << "ԭ����Ϊ��" << readAmount << endl << "�������µ�������";
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
	cout << "���������Ʒ�����ڣ�\n";
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
	cout << "��������Ҫ���۵���Ʒ���ͣ�0Ϊ��ͨ��Ʒ��1Ϊʳ�2Ϊ��װ��3Ϊͼ��\n";
	cin >> goodType;
	cout << "������������ȣ�1Ϊԭ�ۣ�0Ϊ��ѣ�";
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

void good::showGoods(string search, int* loginF, int method)//Ҫд������ж������Ŀ
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
				cout << readName << " " << getPrice(readName) << "Ԫ ��棺" << readAmount << " �� �̼ң�" << readOwner << " ��Ʒ������" << readInfo << endl;
				break;
			case 1:
				if (readName.find(search) != readName.npos) cout << readName << " " << getPrice(readName) << "Ԫ ��棺" << readAmount << " �� �̼ң�" << readOwner << " ��Ʒ������" << readInfo << endl;
				break;
			case 2:
				if (readOwner.find(search) != readOwner.npos) cout << readName << " " << getPrice(readName) << "Ԫ ��棺" << readAmount << " �� �̼ң�" << readOwner << " ��Ʒ������" << readInfo << endl;
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