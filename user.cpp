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
	cout << "���ڴ����û� �û����������֧����ĸ������" << endl << "�������û�����";
	cin >> newName;
	while (!userF1.eof())
	{
		userF1 >> readName;
		if (readName == newName) 
		{
			cout << "�û����ظ������������룺";
			cin >> newName;
			userF1.close();
			userF1.open("userlist.txt", ios::in);
		}
	}//�ж��Ƿ�����ͬ�û�������
	userF1.close();
	userF1.open("userlist.txt", ios::app);
	userF1 << newName << endl;//д�����û���
	userF1.close();
	userFileName = "user\\" + newName + ".txt";
	userF1.open(userFileName, ios::app);
	cout << "���������룺";
	cin >> newPwd;
	userF1 << newPwd << " ";
	userF1 << getUserType() << " 0";
	userF1.close();//�����ļ�д���û���Ϣ
}

void user::login(user* liUser, int* loginF, int typeNum)//Ҫ��
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
	cout << "���ڵ�¼" << endl << "�������û�����";
	cin >> enterName;
	while (enterName != readName)
	{
		if (userF1.eof()) 
		{
			cout << "��������û������ڣ����������룺";
			cin >> enterName;
			userF1.close();
			userF1.open("userlist.txt", ios::in);
			continue;
		}
		userF1 >> readName;
		if (enterName == readName) break;
	}//����û��Ƿ����
	userF1.close();
	userFileName = "user\\" + readName + ".txt";
	userF1.open(userFileName, ios::in);
	cout << "���������룺";
	cin >> enterPwd;
	userF1 >> readPwd;
	int countdown = 3;
	while (readPwd != enterPwd)
	{
		countdown -= 1;
		if (countdown == 0)
		{
			cout << "�������3�Σ��˻������棡\n";
			delete liUser;
			return;
		}
		cout << "����������������룺";
		cin >> enterPwd;
	}//�������벢�ж�
	userF1 >> readType >> readBalance;//���û���Ϣ�����ڴ�
	if (typeNum != readType)
	{
		cout << "�û����ʹ��󣬷������˵���\n";
		delete liUser;
		return;
	}
	liUser->name = enterName;
	liUser->balance = readBalance;
	userF1.close();
	*loginF = 1;
	cout << "��¼�ɹ������ǣ�";
	if (readType == 0)cout << "������\n";
	else cout << "�̼�\n";
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
	cout << "������ԭ���룺";
	cin >> oldPwd;
	userFileName = "user\\" + readName + ".txt";
	userF1.close();
	userF1.open(userFileName, ios::in|ios::out);
	userF1 >> readPwd;//�����û�����ȡԭ����
	int countdown = 3;
	while (oldPwd != readPwd)
	{
		countdown -= 1;
		if (countdown == 0)
		{
			cout << "�������3�Σ��˻������棡\n";
			return;
		}
		cout << "ԭ����������������룺";
		cin >> oldPwd;
	}
	cout << "�����������룺";
	cin >> cpUser->password;
	userF1.close();
	userF1.open(userFileName, ios::out);
	userF1 << cpUser->password << " " << cpUser->getUserType() << " " << cpUser->balance;//д���µ��û���Ϣ
	cout << "�޸ĳɹ���" << endl;
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
	cout << "���������룺";
	cin >> Pwd;
	int countdown = 3;
	while (Pwd != readPwd)
	{
		countdown -= 1;
		if (countdown == 0)
		{
			cout << "�������3�Σ��˻������棡\n";
			return;
		}
		cout << "����������������룺";
		cin >> Pwd;
	}
	cout << "�������ֵ����";
	userF1 >> readTmp >> readBalance;
	cin >> addBalance;
	newBalance = readBalance + addBalance;
	userF1.close();
	userF1.open(userFileName, ios::out);
	userF1 << readPwd << " " << afUser->getUserType() << " " << newBalance;
	afUser->balance = newBalance;
	cout << "��ֵ�ɹ���" << endl;
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
		cout << "����ǰδ��¼��\n";
		return;
	}
	cout << "��ǰ�û����û����ǣ�" << uInfo->name << "\n��ǰ�û�������ǣ�" << uInfo->balance << " Ԫ\n��ǰ�û����û������ǣ�";
	if (getUserType() == 0) cout << "������";
	else cout << "�̼�";
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
