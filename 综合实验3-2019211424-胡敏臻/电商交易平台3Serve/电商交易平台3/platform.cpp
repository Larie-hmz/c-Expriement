#include "platform.h"
#include<fstream>
#include<iostream>

//���캯��
Platform::Platform() {
	//allDiscount[0] = 1;
	//allDiscount[1] = 1;
	//allDiscount[2] = 1;
}

//�������� ɾ��ָ���������ָ��
Platform::~Platform() {
	for (int i = allAccount.size()-1; i >=0 ; i--) {
		delete allAccount[i];
	}
	for (int i = allGoods.size() - 1; i >= 0; i--) {
		delete allGoods[i];
	}
}

//չʾ�̼���Ʒ��Ϣ
void Platform::showGoodsInfo(const std::vector<Goods*> & merGoods) const {
	ser.in() << "�����̼ұ��\t" << "��Ʒ����\t" << "��Ʒ����\t" << "�۸�\t" << "ʣ����\t" << "��Ʒ����\t" << std::endl;
	ser.in() << setiosflags(std::ios::fixed) << std::setprecision(2);
	for (int i = 0; i < merGoods.size(); i++) {
		auto temptr = merGoods[i];
		//�ҵ���Ӧ��Ʒ�������̼�
		auto it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getNumber() == temptr->getNumber(); });
		Merchant* curptr = nullptr;
		if (it != allAccount.end()) {
			curptr = (Merchant*)allAccount[std::distance(allAccount.begin(), it)];
		}
		else {
			ser.in() << "�Ҳ�����Ӧ�̼�" << std::endl;
			return;
		}
		ser.in() << temptr->getNumber() << "\t\t"<<temptr->getName() << "\t" << temptr->getDescrip() << "\t" << temptr->getPrice(curptr->merDiscount[temptr->getgoodType()]) << "\t" <<
			temptr->getAmount() << "\t" << temptr->getgoodType() << "\t" <<std::endl;
	}
	ser.in() << std::endl;
}

//ɸѡ������Ʒ
void Platform::searchGoods() const {
	print pp(&ser);
	ser.in() << "�����Ҫɸѡ����Ʒ����" << std::endl;
	std::string name;
	ser.mySend();
	pp.input(name);
	ser.in() << setiosflags(std::ios::fixed) << std::setprecision(2);
	ser.in() << "�����̼ұ��\t" << "��Ʒ����\t" << "��Ʒ����\t" << "�۸�\t" << "ʣ����\t" << "��Ʒ����\t"  << std::endl;

	for (int i = 0; i < allGoods.size(); i++) {
		auto temptr = allGoods[i];
		if (auto it = temptr->getName().find(name) != std::string::npos) {
			auto it2 = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getNumber() == temptr->getNumber(); });
			Merchant* curptr = nullptr;
			if (it2 != allAccount.end()) {
				curptr = (Merchant*)allAccount[std::distance(allAccount.begin(), it2)];
			}
			else {
				ser.in() << "�Ҳ�����Ӧ�̼�" << std::endl;
				return;
			}
			ser.in() << temptr->getNumber() << "\t\t" << temptr->getName() << "\t" << temptr->getDescrip() << "\t" << temptr->getPrice(curptr->merDiscount[temptr->getgoodType()]) << "\t" <<
				temptr->getAmount() << "\t" << temptr->getgoodType() << "\t" << std::endl;
		}
	}
	//auto it = std::find_if(allGoods.begin(), allGoods.end(), [&](Goods* A)-> bool {return A->name.find(name); });
	//while (it != allGoods.end()) {
	//	ser.in() << (*it)->name <<" "<< (*it)->descrip <<" "<< (*it)->price <<" "<< (*it)->amount <<" "<< (*it)->goodType << std::endl;
	//	it = std::find_if(it, allGoods.end(), [&](Goods* A)-> bool {return A->name == name; });
	//}
	ser.in() << std::endl;
}

//ע���û�����
void Platform::registerUser() {
	int type;
	print pp(&ser);
	ser.in() << "��������Ҫע����û�����\n" << "ע���������˻�����0��ע���̼��˻�����1" << std::endl;
	ser.mySend();
	pp.input( type);
	while (type != 0 && type != 1) {
		ser.in() << "��������˻������������������룡" << std::endl;
		ser.mySend();
		pp.input( type);
	}
	ser.in() << "����ѡ��ɹ���������һ��" << std::endl;

	ser.in() << "������ע����û���" << std::endl;
	std::string tid;
	ser.mySend();
	pp.input(tid);
	auto it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getId() == tid; });
	while (it != allAccount.end()) {
		ser.in() << "��������û��Ѿ����ڣ�����������" << std::endl;
		ser.mySend();
		pp.input(tid);
		it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getId() == tid; });
	}
	ser.in() << "�û��������ɹ���������һ��" << std::endl;

	ser.in() << "����������" << std::endl;
	std::string tpasswd;
	ser.mySend();
	pp.input( tpasswd);
	
	if (type == CONSUMER)
	{
		Consumer* Conptr = new Consumer(number, tid, tpasswd, 0, User(type));
		allAccount.push_back(Conptr);
	}
	else if (type == MERCHANT) {
		Merchant* Merptr = new Merchant(number, tid, tpasswd, 0, User(type));
		allAccount.push_back(Merptr);
	}
	else {
		ser.in() << "ע���û�ʧ��" << std::endl;
		//ser.mySend();
		return;
	}
	ser.in() << "ע���û��ɹ�" << std::endl;
	//ser.mySend();
	//�����û��浽�ļ���
	std::fstream file;
	file.open(fileAccount, std::ios::out|std::ios::app);
	if (!file.is_open()) {
		ser.in() << "�����û��ļ�ʧ��" << std::endl;
	}
	else {
		file << number <<" " << tid << " " << tpasswd << " " << 0 << " " << type << std::endl;
	}

	number++; //�û���ż�1
	file.close();
}

//��¼����
Account* Platform::loginUser() {
	std::string tid;
	std::string tpasswd;
	std::string cpasswd;
	int tbalance;
	User tType;

	if (allAccount.size() == 0) {
		ser.in() << "��ʱ����ע����û�" << std::endl;
		//ser.mySend();
	}
	print pp(&ser);
	ser.in() << "�������û���" << std::endl;
	ser.mySend();
	pp.input(tid);
	auto it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getId() == tid; });
	while (it == allAccount.end()) {
		ser.in() << "��������û������ڣ�����������" << std::endl;
		ser.mySend();
		pp.input(tid);
		it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getId() == tid; });
	}

	auto curptr= allAccount[std::distance(allAccount.begin(), it)]; //�ҵ���ʱ���û�ָ��

	cpasswd = curptr->getPasswd();
	tType = curptr->userType;
	tbalance = curptr->getBalance();

	ser.in() << "����������" << std::endl;
	ser.mySend();
	pp.input(tpasswd);
	while (cpasswd != tpasswd) {
		ser.in() << "�������������������������" << std::endl;
		ser.mySend();
		pp.input(tpasswd);
	}
	ser.in() << "����������ȷ����¼�ɹ�" << std::endl;
	//ser.mySend();

	return curptr;

	//switch (tType)
	//{
	//case CONSUMER:
	//	Consumer* Conptr = new Consumer(tid, tpasswd, tbalance, User(tType));
	//	return Conptr;
	//	break;
	//case MERCHANT:
	//	Merchant* Merptr = new Merchant(tid, tpasswd, tbalance, User(tType));
	//	return Merptr;
	//	break;
	//default:
	//	ser.in() << "ע���û�ʧ��" << std::endl;
	//	return;
	//	break;
	//}

	//return &allAccount[std::distance(allAccount.begin(),it)];

}

//��ʼ�������˻�
void Platform::initAccount() {
	int number_;
	std::string id_;
	std::string passwd_;
	double balance_;
	int userType_;
	std::fstream file;
	file.open(fileAccount,std::ios::in);
	if (!file.is_open()) {
		ser.in() << "�û��ļ��򿪴���" << std::endl;
		ser.mySend();
		return;
	}
	else {
		while (file >> number_ >> id_ >> passwd_ >> balance_ >> userType_) {
			//file >> id_ >> passwd_ >> balance_ >> userType_;
			/*ser.in() << id_ <<" "<< passwd_ <<""<<
				balance_ << " " << userType_;*/
			if (userType_ == 0) {
				Consumer* Conptr = new Consumer(number_, id_, passwd_, balance_, User(userType_));
				allAccount.push_back(Conptr);
				number++;
			}
			else if(userType_ == 1) {
				Merchant* Merptr = new Merchant(number_, id_, passwd_, balance_, User(userType_));
				allAccount.push_back(Merptr);
				number++;
			}
			else {
				ser.in() << "�û��ļ������������飡" << std::endl;
				ser.mySend();
			}
			char ch;
			file.get(ch);
		}
	}
	file.close();
}

//��ʼ��������Ʒ
void Platform::initGoods() {
	int number_;
	std::string name_;
	std::string descrip_;
	double price_;
	int amount_;
	int goodType_;
	std::fstream file;
	file.open(fileGoods, std::ios::in);
	if (!file.is_open()) {
		ser.in() << "�û��ļ��򿪴���" << std::endl;
		ser.mySend();
	}
	else {
		while (file >> number_ >> name_ >> descrip_ >> price_ >> amount_ >> goodType_) {
			//file >> name_ >> descrip_ >> price_ >> amount_ >> goodType_;
			/*if (std::find_if
			(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->id == name_; }) != allAccount.end()) {
				break;
			}*/
			auto it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getNumber()==number_; });
			Merchant* curptr = nullptr;
			if (it != allAccount.end()) {
				curptr = (Merchant *)allAccount[std::distance(allAccount.begin(), it)];
			}
			else {
				ser.in() << "�Ҳ�����Ӧ�̼�" << std::endl;
				ser.mySend();
				return;
			}

			if (goodType_ == FOOD) {
				Food * foodptr = new Food(number_ ,name_ ,descrip_ , price_ , amount_ ,Good( goodType_));
				curptr->merGoods.push_back(foodptr);
				allGoods.push_back(foodptr);
				//ser.in() << "11 ";
			}
			else if (goodType_ == BOOK) {
				Book* bookptr = new Book(number_ ,name_, descrip_, price_, amount_, Good(goodType_));
				curptr->merGoods.push_back(bookptr);
				allGoods.push_back(bookptr);
				//ser.in() << "12 ";
			}
			else if (goodType_ == CLOTHES) {
				Clothes* clothptr = new Clothes(number_, name_, descrip_, price_, amount_, Good(goodType_));
				curptr->merGoods.push_back(clothptr);
				//ser.in() << "13 ";
				allGoods.push_back(clothptr);
			}
			else {
				ser.in() << "��Ʒ�ļ������������飡" << std::endl;
				ser.mySend();
			}
			char ch;
			file.get(ch);
			if (ch != '\n') {
				file.get(ch);
			}
		}
	}
	file.close();
}

//�����û���Ϣ
void Platform::upgradeAccount() const {
	std::fstream file;
	file.open(fileAccount,std::ios::out);
	if (!file.is_open()) {
		ser.in() << "���û��ļ�ʧ��" << std::endl;
		ser.mySend();
	}
	else {
		for (int i = 0; i < allAccount.size(); i++) {
			file << allAccount[i]->getNumber() <<" "<<allAccount[i]->getId() << " " << allAccount[i]->getPasswd() << " " << allAccount[i]->getBalance() << " " << allAccount[i]->userType << std::endl;
		}
	}
	file.close();
}

//������Ʒ��Ϣ
void Platform::upgradeGoods() const {
	std::fstream file;
	file.open(fileGoods, std::ios::out);
	if (!file.is_open()) {
		ser.in() << "���û��ļ�ʧ��" << std::endl;
		ser.mySend();
	}
	else {
		for (int i = 0; i < allGoods.size(); i++) {
			file << allGoods[i]->getNumber() << " "<< allGoods[i]->getName() << " " << allGoods[i]->getDescrip() << " " << allGoods[i]->getPrice() << " " << allGoods[i]->getAmount()<<" "<<allGoods[i]->getgoodType() <<std::endl;
		}
	}
	file.close();
}

//չʾ���ﳵ
void Platform::showShopcart(Consumer* & consumer) const {
	ser.in() << "�����ﳵ�ڵ���Ʒ��" << std::endl;
	ser.in() << "�����̼ұ��\t" << "��Ʒ����\t" << "��Ʒ����\t" << "�۸�\t" << "�����\t" <<"��Ʒ����\t"<< std::endl;
	ser.in() << setiosflags(std::ios::fixed) << std::setprecision(2);
	for (int i = 0; i < consumer->shopcart.size(); i++) {
		auto temptr = consumer->shopcart[i]->getGoodsCard();
		//�ҵ���Ӧ��Ʒ�������̼�
		auto it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getNumber() == temptr->getNumber(); });
		Merchant* curptr = nullptr;
		if (it != allAccount.end()) {
			curptr = (Merchant*)allAccount[std::distance(allAccount.begin(), it)];
		}
		else {
			ser.in() << "�Ҳ�����Ӧ�̼�" << std::endl;
			return;
		}
		ser.in() << temptr->getNumber() << "\t\t" << temptr->getName() << "\t" << temptr->getDescrip() << "\t" << temptr->getPrice(curptr->merDiscount[temptr->getgoodType()]) << "\t" <<
			consumer->shopcart[i]->getbuyNumber() << "\t" << temptr->getgoodType() << "\t" << std::endl;
	
	}
	ser.in() << std::endl;

}

//չʾ����
void Platform::showOrder(Consumer*& consumer) const {
	ser.in() << "�������ڵ���Ʒ��" << std::endl;
	ser.in() << "�����̼ұ��\t" << "��Ʒ����\t" << "��Ʒ����\t" << "�۸�\t" << "�����\t" << "��Ʒ����\t" << std::endl;
	ser.in() << setiosflags(std::ios::fixed) << std::setprecision(2);
	for (int i = 0; i < consumer->ordercart.size(); i++) {
		auto temptr = consumer->ordercart[i]->getGoodsCard();
		//�ҵ���Ӧ��Ʒ�������̼�
		auto it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getNumber() == temptr->getNumber(); });
		Merchant* curptr = nullptr;
		if (it != allAccount.end()) {
			curptr = (Merchant*)allAccount[std::distance(allAccount.begin(), it)];
		}
		else {
			ser.in() << "�Ҳ�����Ӧ�̼�" << std::endl;
			return;
		}
		ser.in() << temptr->getNumber() << "\t\t" << temptr->getName() << "\t" << temptr->getDescrip() << "\t" << temptr->getPrice(curptr->merDiscount[temptr->getgoodType()]) << "\t" <<
			consumer->ordercart[i]->getbuyNumber() << "\t" << temptr->getgoodType() << "\t" << std::endl;

	}
	ser.in() << std::endl;
	
}

//���㶩��
double Platform::calOrder(Consumer*& consumer) const {
	double sum = 0;
	for (int i = 0; i < consumer->ordercart.size(); i++) {
		auto temptr = consumer->ordercart[i]->getGoodsCard();
		//�ҵ���Ӧ��Ʒ�������̼�
		auto it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getNumber() == temptr->getNumber(); });
		Merchant* curptr = nullptr;
		if (it != allAccount.end()) {
			curptr = (Merchant*)allAccount[std::distance(allAccount.begin(), it)];
		}
		else {
			ser.in() << "�Ҳ�����Ӧ�̼�" << std::endl;
			ser.mySend();
			//return ;
		}
		sum+= temptr->getPrice(curptr->merDiscount[temptr->getgoodType()])*consumer->ordercart[i]->getbuyNumber() ;
	}
	return sum;
}

//֧������
void Platform::payloadOrder(Consumer*& consumer,double & sum) {
	if (consumer->ordercart.size() == 0) {
		ser.in() << "��ʱû�ж������޷�֧��" << std::endl;
		return;
	}

	if (! consumer->consumeBalance(sum)) {
		//����������Ʒ��������ָ�
		ser.in() << "��ǰ����ֱ��ȡ��" << std::endl;
		consumer->cancelOrder();
		return;
	}

	for (int i = 0; i < consumer->ordercart.size(); i++) {
		//curptr Ϊ�̼� temptrΪ��Ʒ
		auto temptr = consumer->ordercart[i]->getGoodsCard();
		//�ҵ���Ӧ��Ʒ�������̼�
		auto it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getNumber() == temptr->getNumber(); });
		Merchant* curptr = nullptr;
		if (it != allAccount.end()) {
			curptr = (Merchant*)allAccount[std::distance(allAccount.begin(), it)];
		}
		else {
			ser.in() << "�Ҳ�����Ӧ�̼�" << std::endl;
			return;
		}
		curptr->addBalance(temptr->getPrice(curptr->merDiscount[temptr->getgoodType()])* consumer->ordercart[i]->getbuyNumber());

	}
	ser.in() << "֧�������ɹ�" << std::endl;
	consumer->ordercart.clear();
}