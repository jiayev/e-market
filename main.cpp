#include<iostream>
#include<string>
#include<fstream>
#include "user.h"
#include "stock.h"
#include "order.h"
using namespace std;
int main() {
	int actionNum = 0;
	int* loginF = new int;
	*loginF = 0;
	user* onlineUser = NULL;
	lockgood* startLock = new lockgood;
	startLock->Next = NULL;
	do
	{
		cout << "����������Ҫ�Ĳ���\n";
		if (*loginF == 0) cout << "1.�����û�\n2.��½\n";
		if (*loginF == 1 && onlineUser->getUserType() == 0) cout << "1.������Ʒ\n2.���빺�ﳵ\n";
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
				dynamic_cast<consumer*>(onlineUser)->startNode = new cart;
				dynamic_cast<consumer*>(onlineUser)->startNode->next = NULL;
				dynamic_cast<consumer*>(onlineUser)->startForm = new orderform;
				dynamic_cast<consumer*>(onlineUser)->startForm->next = NULL;
				dynamic_cast<consumer*>(onlineUser)->startForm->formID = 0;
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
			do
			{
				cin >> goodName;
				if (!good::isGoodExist(goodName))
					cout << "��Ʒ�����ڣ����������룡\n";
			} while (!good::isGoodExist(goodName));
			cout << "���������빺���������";
			cin >> buyAmount;
			if (dynamic_cast<consumer*>(onlineUser)->buyGood(dynamic_cast<consumer*>(onlineUser), goodName, buyAmount) == -1)
			{
				cout << "���㣬ȡ������\n";
			}
			else cout << "����ɹ���������Ϊ��" << onlineUser->balance << " Ԫ\n";
		}
		else if (actionNum == 2 && *loginF == 1 && onlineUser->getUserType() == 0)
		{
			int actionNum2;
			do
			{
				cout << "1.�����Ʒ\n2.ɾ����Ʒ\n3.��ʾ�����б�\n4.�˳�\n5.����������������չ��ﳵ��\n6.��ʾ����\n7.֧������\n8.ȡ������\n��Ķ���������" << orderform::getFormAmounts(dynamic_cast<consumer*>(onlineUser)) << endl;
				cin >> actionNum2;
				if (actionNum2 == 1)
				{
					string goodName;
					int goodAmount;
					cout << "��������Ҫ���빺�ﳵ����Ʒ���ƣ�";
					do
					{
						cin >> goodName;
						if (!good::isGoodExist(goodName))
							cout << "��Ʒ�����ڣ����������룡\n";
					} while (!good::isGoodExist(goodName));
					cout << "��������Ҫ��ӵ�������";
					cin >> goodAmount;
					if (!lockgood::isGoodLocked(goodName, startLock)) cart::addtoCart(goodName, dynamic_cast<consumer*>(onlineUser), goodAmount);
					else cout << "����Ʒ�Ѵ��ڶ����У�\n";
				}
				else if (actionNum2 == 2)
				{
					string goodName;
					int goodAmount, dF;
					cout << "��������Ҫ�Ƴ����ﳵ����Ʒ���ƣ�";
					do
					{
						cin >> goodName;
						if (!good::isGoodExist(goodName))
							cout << "��Ʒ�����ڣ����������룡\n";
					} while (!good::isGoodExist(goodName));
					cout << "��������Ҫ���ٵ�������";
					cin >> goodAmount;
					dF = cart::removeItem(goodName, dynamic_cast<consumer*>(onlineUser), goodAmount);
					if (dF == -1) cout << "���ﳵ��û�д���Ʒ��\n";
				}
				else if (actionNum2 == 3)
				{
					cart::showCart(dynamic_cast<consumer*>(onlineUser)->startNode->next);
				}
				else if (actionNum2 == 5)
				{
					orderform::createForm(dynamic_cast<consumer*>(onlineUser), startLock);
				}
				else if (actionNum2 == 6)
				{
					orderform::showForms(dynamic_cast<consumer*>(onlineUser));
				}
				else if (actionNum2 == 7)
				{
					int formID;
					cout << "��������Ҫ֧���Ķ����ţ�";
					cin >> formID;
					if (orderform::isFormExist(formID, dynamic_cast<consumer*>(onlineUser))) orderform::payForm(formID, dynamic_cast<consumer*>(onlineUser), startLock);
					else cout << "���������ڣ�\n";
				}
				else if (actionNum2 == 8)
				{
					int formID;
					cout << "��������Ҫȡ���Ķ����ţ�";
					cin >> formID;
					if (orderform::isFormExist(formID, dynamic_cast<consumer*>(onlineUser))) orderform::cancelForm(formID, dynamic_cast<consumer*>(onlineUser), startLock);
					else cout << "���������ڣ�\n";
				}
			} while (actionNum2 != 4);
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
			user::logout(onlineUser , loginF);
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