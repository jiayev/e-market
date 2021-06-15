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
	do
	{
		cout << "请输入你想要的操作\n";
		if (*loginF == 0) cout << "1.创建用户\n2.登陆\n";
		if (*loginF == 1 && onlineUser->getUserType() == 0) cout << "1.购买商品\n2.进入购物车\n";
		if (*loginF == 1 && onlineUser->getUserType() == 1) cout << "1.添加商品\n2.修改商品\n";
		cout << "3.退出\n";
		if (*loginF == 1) cout << "4.修改密码\n5.充值\n6.登出\n7.显示用户信息\n";
		cout << "8.显示商品\n9.搜索商品\n";
		cin >> actionNum;
		if (actionNum == 1 && *loginF == 0)
		{
			cout << "请输入你要注册的账户类型：0.消费者 1.商家\n";
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
			cout << "请输入你要登录的账户类型：0.消费者 1.商家\n";
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
			cout << "请输入你想购买的商品名称：";
			do
			{
				cin >> goodName;
				if (!good::isGoodExist(goodName))
					cout << "商品不存在，请重新输入！\n";
			} while (!good::isGoodExist(goodName));
			cout << "请输入你想购买的数量：";
			cin >> buyAmount;
			if (dynamic_cast<consumer*>(onlineUser)->buyGood(dynamic_cast<consumer*>(onlineUser), goodName, buyAmount) == -1)
			{
				cout << "余额不足，取消购买！\n";
			}
			else cout << "购买成功！你的余额为：" << onlineUser->balance << " 元\n";
		}
		else if (actionNum == 2 && *loginF == 1 && onlineUser->getUserType() == 0)
		{
			int actionNum2;
			do
			{
				cout << "1.添加商品\n2.删除商品\n3.显示购物列表\n4.退出\n5.创建订单（将会清空购物车）\n6.显示订单\n7.支付订单\n8.取消订单\n你的订单数量：" << orderform::getFormAmounts(dynamic_cast<consumer*>(onlineUser)) << endl;
				cin >> actionNum2;
				if (actionNum2 == 1)
				{
					string goodName;
					int goodAmount;
					cout << "请输入你要加入购物车的商品名称：";
					do
					{
						cin >> goodName;
						if (!good::isGoodExist(goodName))
							cout << "商品不存在，请重新输入！\n";
					} while (!good::isGoodExist(goodName));
					cout << "请输入你要添加的数量：";
					cin >> goodAmount;
					cart::addtoCart(goodName, dynamic_cast<consumer*>(onlineUser), goodAmount);
				}
				else if (actionNum2 == 2)
				{
					string goodName;
					int goodAmount, dF;
					cout << "请输入你要移出购物车的商品名称：";
					do
					{
						cin >> goodName;
						if (!good::isGoodExist(goodName))
							cout << "商品不存在，请重新输入！\n";
					} while (!good::isGoodExist(goodName));
					cout << "请输入你要减少的数量：";
					cin >> goodAmount;
					dF = cart::removeItem(goodName, dynamic_cast<consumer*>(onlineUser), goodAmount);
					if (dF == -1) cout << "购物车中没有此商品！\n";
				}
				else if (actionNum2 == 3)
				{
					cart::showCart(dynamic_cast<consumer*>(onlineUser)->startNode->next);
				}
				else if (actionNum2 == 5)
				{
					orderform::createForm(dynamic_cast<consumer*>(onlineUser));
				}
				else if (actionNum2 == 6)
				{
					orderform::showForms(dynamic_cast<consumer*>(onlineUser));
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
				cout << "输入1查看库存商品 输入0返回：";
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
			cout << "请输入你想要搜索的项目：1.商品名 2.商家名\n";
			cin >> temp;
			switch (temp)
			{
			default:
				break;
			case 1:
				cout << "请输入你要搜索的商品名：";
				cin.get();
				getline(cin, search);
				showgood.showGoods(search, loginF, 1); 
				break;
			case 2: 
				cout << "请输入你要搜索的商家名：";
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