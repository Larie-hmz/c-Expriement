#include "merchant.h"
#include<iostream>
#include<fstream>

//���캯��
Merchant::Merchant(const int number_, const std::string& id_ , const std::string& passwd_, const double& balance_ , const User& userType_ ) {
	number = number_;
	id = id_;
	passwd = passwd_;
	balance = balance_;
	userType = userType_;

	merDiscount[0] = 1;
	merDiscount[1] = 1;
	merDiscount[2] = 1;
}

//�������캯��
Merchant::Merchant(Merchant& acc) {
	number = acc.number;
	id = acc.id;
	passwd = acc.passwd;
	balance = acc.balance;
	userType = acc.userType;

	merDiscount[0] = acc.merDiscount[0];
	merDiscount[1] = acc.merDiscount[1];
	merDiscount[2] = acc.merDiscount[2];
}

//��������
Merchant::~Merchant() {
	for (int i = merGoods.size() - 1; i >= 0; i--) {
		delete merGoods[i];
	}
}

//�õ��û�����
User Merchant::getUserType() {
	return userType;
}

//������Ʒ
void Merchant::addgoods(std::string filename, std::vector<Goods*>& allGoods) {
	ser.in() << "������������Ʒ���֣�������Ϣ���۸�ʣ����������" << std::endl;
	std::string name_;
	std::string descrip_;
	double price_;
	int amount_;
	int goodType_;

	print pp(&ser);
	ser.in() << "��������Ʒ����" << std::endl;
	ser.mySend();
	pp.input(name_); 
	if (!ser.iflegal()) {
		ser.close();
		return;
	}
	auto it = std::find_if(allGoods.begin(), allGoods.end(), [&](Goods* A)-> bool {return A->getName() == name_; });
	while (it != allGoods.end()) {
		ser.in() << "���������Ʒ�����Ѿ����ڣ�������������Ʒ����" << std::endl;
		ser.mySend();
		pp.input(name_);
		it = std::find_if(allGoods.begin(), allGoods.end(), [&](Goods* A)-> bool {return A->getName() == name_; });
	}

	ser.in() << "������������Ϣ" << std::endl;
	ser.mySend();
	pp.input(descrip_); 

	ser.in() << "������۸�" << std::endl;
	ser.mySend();
	pp.input(price_);
	while (price_ < 0) {
		ser.in() << "���������Ʒ�۸�С��0��������������Ʒ�۸�" << std::endl;
		ser.mySend();
		pp.input(price_);
	}

	ser.in() << "������ʣ����" << std::endl;
	ser.mySend();
	pp.input(amount_);
	while (amount_ < 0) {
		ser.in() << "���������Ʒʣ����С��0��������������Ʒʣ����" << std::endl;
		ser.mySend();
		pp.input(amount_);
	}
	ser.in() << "����������" << std::endl;
	ser.mySend();
	pp.input(goodType_);
	while (goodType_ != FOOD && goodType_ != BOOK && goodType_ != CLOTHES) {
		ser.in() << "��Ʒ�ļ����������������������룡" << std::endl;
		ser.mySend();
		pp.input(goodType_);
	}

	//ͬʱ����������Ʒ�͸��û��е���Ʒ
	if (goodType_ == FOOD) {
		Food* foodptr = new Food(getNumber(),name_, descrip_, price_, amount_, Good(goodType_));
		merGoods.push_back(foodptr);
		allGoods.push_back(foodptr);
	}
	else if (goodType_ == BOOK) {
		Book* bookptr = new Book(getNumber(),name_, descrip_, price_, amount_, Good(goodType_));
		merGoods.push_back(bookptr);
		allGoods.push_back(bookptr);
	}
	else if (goodType_ == CLOTHES) {
		Clothes* clothptr = new Clothes(getNumber(),name_, descrip_, price_, amount_, Good(goodType_));
		merGoods.push_back(clothptr);
		allGoods.push_back(clothptr);
	}

	ser.in() << "���ѳɹ������Ʒ" << std::endl;
	//std::fstream fgoods;
	//fgoods.open(filename, std::ios::in | std::ios::app);
	//if (!fgoods.is_open()) {
	//	ser.in() << "����Ʒ�ļ���������" << std::endl;
	//}
	//else {
	//	fgoods << name_ << " " << descrip_ << " " << price_ << " " << amount_ << "" << goodType_ <<std::endl ;
	//	ser.in() << "�ɹ�����һ����Ʒ��Ϣ"<<std::endl;
	//}
	//fgoods.close();
}

//������Ʒ
void Merchant::manageGoods(std::vector<Goods*> & allGoods) {
	if (merGoods.size() == 0) {
		ser.in() << "���̼�Ŀǰû�й������Ʒ" << std::endl;
		return;
	}
	print pp(&ser);
	ser.in() << "�����Ҫ�������Ʒ����" << std::endl;
	std::string name_;
	ser.mySend();
	pp.input(name_);
	//�������û����Ƿ��и���Ʒ���ж��Ƿ����������lambda���ʽ
	auto it = std::find_if(merGoods.begin(), merGoods.end(), [&](Goods* A)-> bool {return A->getName() == name_; });
	while (it == merGoods.end()) {
		ser.in() << "���������Ʒ���Ʋ����ڣ�����������" << std::endl;
		ser.mySend();
		pp.input(name_);
		it = std::find_if(merGoods.begin(), merGoods.end(), [&](Goods* A)-> bool {return A->getName() == name_; });
	}

	auto curptr = merGoods[std::distance(merGoods.begin(), it)];
	ser.in() << "��ʱ��Ʒԭ��" << curptr->getPrice() << "    ��ʱ��Ʒʣ����" << curptr->getAmount() << std::endl;
	int choice;
	ser.in() << "�޸ļ۸�����0���޸�ʣ��������1" << std::endl;
	ser.mySend();
	pp.input(choice);
	switch (choice)
	{
	case 0:
		ser.in() << "������Ҫ���ĵļ۸�" << std::endl;
		int tprice;
		ser.mySend();
		pp.input(tprice);
		while (tprice < 0) {
			ser.in() << "�۸���С��0������������" << std::endl;
			ser.mySend();
			pp.input(tprice);
		}
		ser.in() << "�۸��޸ĳɹ�" << std::endl;
		curptr->setPrice(tprice);
		break;
	case 1:
		ser.in() << "������Ҫ���ĵ�ʣ����" << std::endl;
		int tamount;
		ser.mySend();
		pp.input(tamount);
		while (tamount < 0) {
			ser.in() << "ʣ��������С��0������������" << std::endl;
			ser.mySend();
			pp.input(tamount);
		}
		ser.in() << "ʣ�����޸ĳɹ�" << std::endl;
		curptr->setAmount(tamount);
		break;
	default:
		ser.in() << "�������ѡ������,�˳�" << std::endl;
		break;
	}
}

//ͬ����Ʒ����
void Merchant::haveDiscount() {
	ser.in() << "��������Ҫ���۵���Ʒ����\nʳ����ѡ��0���鱾��ѡ��1���·���ѡ��2" << std::endl;
	int type;
	print pp(&ser);
	ser.mySend();
	pp.input(type);
	while (type != 0 && type != 1 && type != 2) {
		ser.in() << "�������ѡ����������������" << std::endl;
		ser.mySend();
		pp.input(type);
	}

	ser.in() << "��������Ҫ���۵��ۿ�(������0-1֮�����)" << std::endl;
	double discount;
	ser.mySend();
	pp.input(discount);
	while (!(0 < discount && discount < 1)) {
		ser.in() << "������Ĵ��۵��ۿ�����(������0-1֮�����)������������" << std::endl;
		ser.mySend();
		pp.input(discount);
	}
	
	merDiscount[type] = discount;
}

