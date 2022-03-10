#include "consumer.h"

Consumer::Consumer(const int number_,const std::string& id_ , const std::string& passwd_ , const double& balance_ , const User& userType_ ) {
	number = number_;
	id = id_;
	passwd = passwd_;
	balance = balance_;
	userType = userType_;
}
Consumer::Consumer(const Consumer& acc) {
	number = acc.number;
	id = acc.id;
	passwd = acc.passwd;
	balance = acc.balance;
	userType = acc.userType;
}
Consumer::~Consumer() {
	//�ͷ�ָ��
	for (int i = shopcart.size() - 1; i >= 0; i--) {
		delete shopcart[i];
	}
	for (int i = ordercart.size() - 1; i >= 0; i--) {
		delete ordercart[i];
	}
}

User Consumer::getUserType() {
	return userType;
}

//��ӹ��ﳵ
void Consumer::addShopcart(std::vector<Goods*>& allGoods) {
	if (allGoods.size() == 0) {
		ser.in() << "��ʱû����Ʒ����ѡ�񣬲�����ӹ��ﳵ" << std::endl;
		return;
	}

	ser.in() << "��������Ҫ��ӵ���Ʒ����" << std::endl;
	std::string name_;
	print pp(&ser);
	ser.mySend();
	pp.input(name_); 
	auto it = std::find_if(allGoods.begin(), allGoods.end(), [&](Goods* A)-> bool {return A->getName() == name_; });
	while (it == allGoods.end()) {
		ser.in() << "���������Ʒ���Ʋ����ڣ�������������Ʒ����" << std::endl;
		ser.mySend();
		pp.input(name_);
		it = std::find_if(allGoods.begin(), allGoods.end(), [&](Goods* A)-> bool {return A->getName() == name_; });
	}
	ser.in() << "�ɹ�ѡ����Ʒ��������������ӵ���Ʒ����" << std::endl;
	Goods* curptr = allGoods[std::distance(allGoods.begin(), it)];
	if (curptr->getAmount() == 0) {
		ser.in() << "����Ʒ��ʣ����Ϊ0�����������Ʒ" << std::endl;
		//ser.mySend();
		return;
	}
	ser.mySend();
	int buyNumber_;
	pp.input(buyNumber_);
	while (buyNumber_ > curptr->getAmount() || buyNumber_<1) {
		if (buyNumber_ > curptr->getAmount()) {
			ser.in() << "����ӵ�����������Ʒʣ����������������" << std::endl;
		}
		else {
			ser.in() << "����ӵ�����С��1������������" << std::endl;
		}
		ser.mySend();
		pp.input(buyNumber_);
	}

	auto it2 = std::find_if(shopcart.begin(), shopcart.end(), [&](Shopcard* A)-> bool {return A->getGoodsCard()->getName() == name_; });
	if (it2 == shopcart.end()) {
		Shopcard* cardptr = new Shopcard(curptr, buyNumber_);
		shopcart.push_back(cardptr);
	}
	else {
		(*it2)->setbuyNumber((*it2)->getbuyNumber() + buyNumber_);
	}

	ser.in() << "���Ѿ��ɹ������Ʒ" << std::endl;

}

//�޸Ĺ�������
void Consumer::modifyShopcart( ) {
	ser.in() << "��������Ҫ�޸ĵ���Ʒ����" << std::endl;
	ser.mySend();
	std::string name_;
	print pp(&ser);
	pp.input(name_);
	Shopcard* it=nullptr;
	auto itemp = shopcart.begin();
	for (int i = 0; i < shopcart.size(); i++) {
		if (shopcart[i]->getGoodsCard()->getName() == name_) {
			itemp++;
			it = shopcart[i];
			break;
		}
	}
	if (it == nullptr) {
		ser.in() << "���ﳵ���޸���Ʒ���˳��޸�" << std::endl;
		return;
	}
	ser.in() << "�ɹ�ѡ����Ʒ�������������޸ĵ���Ʒ����" << std::endl;
	ser.mySend();
	Goods* curptr = it->getGoodsCard();
	int buyNumber_;
	pp.input(buyNumber_);
	while (buyNumber_ > curptr->getAmount() || buyNumber_ < 0) {
		if (buyNumber_ > curptr->getAmount()) {
			ser.in() << "���޸ĵ�����������Ʒʣ����������������" << std::endl;
		}
		else {
			ser.in() << "���޸ĵ�����С��0������������" << std::endl;
		}
		ser.mySend();
		pp.input(buyNumber_);
	}

	if (buyNumber_ == 0) {
		shopcart.erase(--itemp);
	}
	else {
		it->setbuyNumber(buyNumber_);
	}
	ser.in() << "���Ѿ��ɹ��޸Ĺ��ﳵ" << std::endl;
}

//ɾ�����ﳵ�е���Ʒ
void Consumer::deleteShopcart() {
	ser.in() << "��������Ҫɾ������Ʒ����" << std::endl;
	ser.mySend();
	std::string name_;
	print pp(&ser);
	pp.input(name_);
	Shopcard* it = nullptr;
	auto itemp = shopcart.begin();
	for (int i = 0; i < shopcart.size(); i++) {
		itemp++;
		if (shopcart[i]->getGoodsCard()->getName() == name_) {
			it = shopcart[i];
			break;
		}
	}
	if (it == nullptr) {
		ser.in() << "���ﳵ���޸���Ʒ���˳�ɾ��" << std::endl;
		return;
	}
	ser.in() << "�ɹ�ѡ����Ʒ������������ɾ������Ʒ����" << std::endl;
	ser.mySend();
	Goods* curptr = it->getGoodsCard();
	int buyNumber_;
	pp.input(buyNumber_);
	while (buyNumber_ > it->getbuyNumber() || buyNumber_ < 0) {
		if (buyNumber_ > it->getbuyNumber()) {
			ser.in() << "��ɾ��������������Ʒ�����������������" << std::endl;
		}
		else {
			ser.in() << "��ɾ��������С��0������������" << std::endl;
		}
		ser.mySend();
		pp.input(buyNumber_);
	}

	if (it->getbuyNumber() - buyNumber_ == 0) {
		shopcart.erase(--itemp);
	}
	else {
		it->setbuyNumber(it->getbuyNumber() - buyNumber_);
	}
	ser.in() << "���Ѿ��ɹ�ɾ����Ʒ" << std::endl;
}

//���ɶ���
void Consumer::generateOrder() {
	if (shopcart.size() == 0) {
		ser.in() << "���ﳵ��û����Ʒ���޷���Ӷ���" << std::endl;
		return;
	}

	int choice = 1;
	while (choice) {
		ser.in() << "��������Ҫ��ӵ���Ʒ����" << std::endl;
		ser.mySend();
		std::string name_;
		print pp(&ser);
		pp.input(name_);
		Shopcard* it = nullptr;
		auto itemp = shopcart.begin();
		for (int i = 0; i < shopcart.size(); i++) {
			itemp++;
			if (shopcart[i]->getGoodsCard()->getName() == name_) {
				it = shopcart[i];
				break;
			}
		}
		if (it == nullptr) {
			ser.in() << "���ﳵ���޸���Ʒ" << std::endl;
		}
		else {
			//ser.in() << "�ɹ�ѡ����Ʒ" << std::endl;
			if (it->getGoodsCard()->getAmount() - it->getbuyNumber() < 0) {
				ser.in() << "����Ʒʣ����С�ڹ����������������������ܽ�����Ʒ��Ӷ���" << std::endl;
			}
			else {
				ser.in() << "�ɹ�ѡ����Ʒ" << std::endl;
				it->getGoodsCard()->setAmount(it->getGoodsCard()->getAmount() - it->getbuyNumber());
				ordercart.push_back(it);
				shopcart.erase(--itemp);
			}

		}
	
		ser.in() << "�Ƿ����ѡ����Ʒ����������1���˳�����0" << std::endl;
		ser.mySend();
		pp.input(choice);
	}


}

//ȡ������
void Consumer::cancelOrder() {
	if (ordercart.size() == 0) {
		ser.in() << "��ʱ�޶���" << std::endl;
		return;
	}

	for (int i = 0; i < ordercart.size(); i++) {
		ordercart[i]->getGoodsCard()->setAmount(ordercart[i]->getGoodsCard()->getAmount() + ordercart[i]->getbuyNumber());
	}
	ordercart.clear();
	ser.in() << "�ѳɹ�ȡ������" << std::endl;

}