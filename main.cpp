#include<iostream>
#include<string>
#include<fstream>
#include "user.h"
#include "stock.h"
using namespace std;
int main() {
	int actionNum = 0;
	int* loginF = new int;
	*loginF = 0;
	user* onlineUser = NULL;
	do
	{
		cout << "����������Ҫ�Ĳ���\n";
		if (*loginF == 0) cout << "1.�����û�\n2.��½\n";
		if (*loginF == 1 && onlineUser->getUserType() == 0) cout << "1.������Ʒ\n";
		if (*loginF == 1 && onlineUser->getUserType() == 1) cout << "1.�����Ʒ\n2.�޸���Ʒ\n";
		cout << "3.�˳�\n";
		if (*loginF == 1) cout << "4.�޸�����\n5.��ֵ\n6.�ǳ�\n7.��ʾ�û���Ϣ\n";
		cout << "8.��ʾ��Ʒ\n9.������Ʒ\n";
		cin >> actionNum;
		if (actionNum == 1 && *loginF == 0)
		{
			cout << "��������Ҫע����˻����ͣ�0.������ 1.�̼�\n";
			int typeNum;
			cin >> typeNum;
			if (typeNum == 0) 
			{
				consumer newUser;
				newUser.createUser();
			}
			else if (typeNum == 1)
			{
				seller newUser;
				newUser.createUser();
			}
		}
		else if (actionNum == 2 && *loginF == 0)
		{
			cout << "��������Ҫ��¼���˻����ͣ�0.������ 1.�̼�\n";
			int typeNum;
			cin >> typeNum;
			if (typeNum == 0)
			{
				onlineUser = new consumer;
				onlineUser->login(onlineUser, loginF, typeNum);
			}
			else if(typeNum == 1)
			{
				onlineUser = new seller;
				onlineUser->login(onlineUser, loginF, typeNum);
			}
		}
		else if (actionNum == 2 && *loginF == 1 && onlineUser->getUserType() == 1)
		{
			good modGood;
			modGood.modifyGood(dynamic_cast<seller*>(onlineUser));
		}
		else if (actionNum == 1 && *loginF == 1 && onlineUser->getUserType() == 1)
		{
			good newGood;
			newGood.addtoStock(dynamic_cast<seller*>(onlineUser));
		}
		else if (actionNum == 1 && *loginF == 1 && onlineUser->getUserType() == 0)
		{
			int buyAmount;
			string goodName;
			cout << "���������빺�����Ʒ���ƣ�";
			cin >> goodName;
			cout << "���������빺���������";
			cin >> buyAmount;
			if (dynamic_cast<consumer*>(onlineUser)->buyGood(dynamic_cast<consumer*>(onlineUser), goodName, buyAmount) == -1)
			{
				cout << "���㣬ȡ������\n";
			}
			else cout << "����ɹ���������Ϊ��" << onlineUser->balance << " Ԫ\n";
		}
		else if (actionNum == 4 && *loginF == 1) 
		{
			onlineUser->changePwd(onlineUser);
		}
		else if (actionNum == 5 && *loginF == 1)
		{
			onlineUser->addFund(onlineUser);
		}
		else if (actionNum == 6 && *loginF == 1)
		{
			onlineUser->logout(onlineUser , loginF);
		}
		else if (actionNum == 7 && *loginF == 1)
		{
			onlineUser->showUserInfo(onlineUser, loginF);
			if (onlineUser->getUserType() == 1)
			{
				cout << "����1�鿴�����Ʒ ����0���أ�";
				bool temp;
				cin >> temp;
				if (temp)
				{
					good showgood;
					showgood.showGoods(onlineUser->name, loginF, 2);
				}
			}
		}
		else if (actionNum == 8)
		{
			good showgood;
			showgood.showGoods("no",loginF,0);
		}
		else if (actionNum == 9)
		{
			good showgood;
			string search;
			int temp;
			cout << "����������Ҫ��������Ŀ��1.��Ʒ�� 2.�̼���\n";
			cin >> temp;
			switch (temp)
			{
			default:
				break;
			case 1:
				cout << "��������Ҫ��������Ʒ����";
				cin.get();
				getline(cin, search);
				showgood.showGoods(search, loginF, 1); 
				break;
			case 2: 
				cout << "��������Ҫ�������̼�����";
				cin.get();
				getline(cin, search);
				showgood.showGoods(search, loginF, 2); 
				break;
			}
			
		}
		else continue;
	} while (actionNum != 3);
	if (*loginF == 1) delete onlineUser;
	delete loginF;
	return 0;
}