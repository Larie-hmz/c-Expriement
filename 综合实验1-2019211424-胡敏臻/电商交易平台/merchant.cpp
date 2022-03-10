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
	std::cout << "������������Ʒ���֣�������Ϣ���۸�ʣ����������" << std::endl;
	std::string name_;
	std::string descrip_;
	double price_;
	int amount_;
	int goodType_;

	print pp;
	pp.input(name_); pp.input(descrip_); pp.input(price_); pp.input(amount_); pp.input(goodType_);
	auto it = std::find_if(merGoods.begin(), merGoods.end(), [&](Goods* A)-> bool {return A->getName() == name_; });
	while (it != merGoods.end()) {
		std::cout << "���������Ʒ�����Ѿ����ڣ�������������Ʒ����" << std::endl;
		pp.input(name_);
		it = std::find_if(merGoods.begin(), merGoods.end(), [&](Goods* A)-> bool {return A->getName() == name_; });
	}

	while (price_ < 0) {
		std::cout << "���������Ʒ�۸�С��0��������������Ʒ�۸�" << std::endl;
		pp.input(price_);
	}

	while (amount_ < 0) {
		std::cout << "���������Ʒʣ����С��0��������������Ʒʣ����" << std::endl;
		pp.input(amount_);
	}

	while (goodType_ != FOOD && goodType_ != BOOK && goodType_ != CLOTHES) {
		std::cout << "��Ʒ�ļ����������������������룡" << std::endl;
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

	//std::fstream fgoods;
	//fgoods.open(filename, std::ios::in | std::ios::app);
	//if (!fgoods.is_open()) {
	//	std::cout << "����Ʒ�ļ���������" << std::endl;
	//}
	//else {
	//	fgoods << name_ << " " << descrip_ << " " << price_ << " " << amount_ << "" << goodType_ <<std::endl ;
	//	std::cout << "�ɹ�����һ����Ʒ��Ϣ"<<std::endl;
	//}
	//fgoods.close();
}

//������Ʒ
void Merchant::manageGoods(std::vector<Goods*> & allGoods) {
	if (merGoods.size() == 0) {
		std::cout << "���̼�Ŀǰû�й������Ʒ" << std::endl;
		return;
	}
		
	std::cout << "�����Ҫ�������Ʒ����" << std::endl;
	std::string name_;
	std::cin >> name_;
	//�������û����Ƿ��и���Ʒ���ж��Ƿ����������lambda���ʽ
	auto it = std::find_if(merGoods.begin(), merGoods.end(), [&](Goods* A)-> bool {return A->getName() == name_; });
	if (it == merGoods.end()) {
		std::cout << "���������Ʒ���Ʋ����ڣ��˳�����" << std::endl;
		return;
		//std::cin >> name_;
		//it = std::find_if(merGoods.begin(), merGoods.end(), [&](Goods* A)-> bool {return A->getName() == name_; });
	}

	auto curptr = merGoods[std::distance(merGoods.begin(), it)];
	std::cout << "��ʱ��Ʒԭ��" << curptr->getPrice() << "    ��ʱ��Ʒʣ����" << curptr->getAmount() << std::endl;
	int choice;
	print pp;
	std::cout << "�޸ļ۸�����0���޸�ʣ��������1" << std::endl;
	pp.input(choice);
	switch (choice)
	{
	case 0:
		std::cout << "������Ҫ���ĵļ۸�" << std::endl;
		int tprice;
		pp.input(tprice);
		while (tprice < 0) {
			std::cout << "�۸���С��0������������" << std::endl;
			pp.input(tprice);
		}
		std::cout << "�۸��޸ĳɹ�" << std::endl;
		curptr->setPrice(tprice);
		break;
	case 1:
		std::cout << "������Ҫ���ĵ�ʣ����" << std::endl;
		int tamount;
		pp.input(tamount);
		while (tamount < 0) {
			std::cout << "ʣ��������С��0������������" << std::endl;
			pp.input(tamount);
		}
		std::cout << "ʣ�����޸ĳɹ�" << std::endl;
		curptr->setAmount(tamount);
		break;
	default:
		std::cout << "�������ѡ������,�˳�" << std::endl;
		break;
	}
}

//ͬ����Ʒ����
void Merchant::haveDiscount() {
	std::cout << "��������Ҫ���۵���Ʒ����\nʳ����ѡ��0���鱾��ѡ��1���·���ѡ��2" << std::endl;
	int type;
	print pp;
	pp.input(type);
	while (type != 0 && type != 1 && type != 2) {
		std::cout << "�������ѡ����������������" << std::endl;
		pp.input(type);
	}

	std::cout << "��������Ҫ���۵��ۿ�(������0-1֮�����)" << std::endl;
	double discount;
	pp.input(discount);
	while (!(0 < discount && discount < 1)) {
		std::cout << "������Ĵ��۵��ۿ�����(������0-1֮�����)������������" << std::endl;
		pp.input(discount);
	}
	
	merDiscount[type] = discount;    //�����������Ʒ�趨�ۿ�
}

