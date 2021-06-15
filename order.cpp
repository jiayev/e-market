#include"order.h"

void cart::addtoCart(string goodName, consumer* consumer, int amount)
{
	bool isItemExist = 0;
	cart* nodeS = consumer->startNode->next;
	cart* lastnode = consumer->startNode;
	while (isItemExist == 0 && nodeS != NULL)
	{
		if(goodName == nodeS->Order.goodName)
		{
			isItemExist = 1;
			break;
		}
		
		else
		{
			lastnode = nodeS;
			nodeS = nodeS->next;
		}
	}
	cart* newCart = new cart;
	if (isItemExist == 1)
	{
		nodeS->Order.amount += amount;
	}
	else
	{
		newCart->Order.goodName = goodName;
		newCart->Order.consumerName = consumer->name;
		newCart->Order.amount = amount;
		lastnode->next = newCart;
	}
}

int cart::removeItem(string goodName, consumer* consumer, int amount)
{
	bool isItemExist = 0;
	cart* nodeS = consumer->startNode->next;
	cart* lastnode = consumer->startNode;
	while (isItemExist == 0 && nodeS != NULL)
	{
		if (goodName == nodeS->Order.goodName)
		{
			isItemExist = 1;
			break;
		}

		else
		{
			lastnode = nodeS;
			nodeS = nodeS->next;
		}
	}
	if (isItemExist == 1)
	{
		if(amount>=nodeS->Order.amount)
		{
			lastnode->next = nodeS->next;
			return 1;
		}
		else
			nodeS->Order.amount -= amount;
	}
	else
		return -1;
	return 0;
}

void cart::showCart(cart* startNode)
{
	string readName;
	cart* nodeS;
	nodeS = startNode;
	while (nodeS != NULL)
	{
		cout << nodeS->Order.goodName << " 共 " << nodeS->Order.amount << " 个 总价为 " << nodeS->Order.amount * good::getPrice(nodeS->Order.goodName) << " 元\n";
		nodeS = nodeS->next;
	}
}

void orderform::createForm(consumer* consumer)
{
	orderform* formNode,* newForm;
	formNode = consumer->startForm;
	while (consumer->startForm->next != NULL)
	{
		formNode = formNode->next;
	}
	newForm = new orderform;
	formNode->next = newForm;
	newForm->formID = formNode->formID + 1;
	newForm->consumerName = consumer->name;
	newForm->comCart = consumer->startNode->next;
	consumer->startNode->next = NULL;
}

float orderform::calFormPrice()
{
	float price = 0;
	cart* Node;
	Node = comCart;
	do
	{
		price += Node->Order.amount * good::getPrice(Node->Order.goodName);
		Node = Node->next;
	}while (Node->next != NULL);
	return price;
}

void orderform::showForms(consumer* consumer)
{
	orderform* readForm;
	readForm = consumer->startForm;
	while (readForm->next != NULL)
	{
		readForm = readForm->next;
		cout << readForm->formID << "号订单\n";
		cart::showCart(readForm->comCart);
		cout << "共 " << readForm->calFormPrice() << " 元\n";
	}
}

int orderform::getFormAmounts(consumer* consumer)
{
	orderform* readForm;
	int amounts = 0;
	readForm = consumer->startForm;
	while (readForm->next != NULL)
	{
		readForm = readForm->next;
		amounts = readForm->formID;
	}
	return amounts;
}
