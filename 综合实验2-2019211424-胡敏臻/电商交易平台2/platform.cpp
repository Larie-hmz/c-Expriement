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
	std::cout << "�����̼ұ��\t" << "��Ʒ����\t" << "��Ʒ����\t" << "�۸�\t" << "ʣ����\t" << "��Ʒ����\t" << std::endl;
	std::cout << setiosflags(std::ios::fixed) << std::setprecision(2);
	for (int i = 0; i < merGoods.size(); i++) {
		auto temptr = merGoods[i];
		//�ҵ���Ӧ��Ʒ�������̼�
		auto it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getNumber() == temptr->getNumber(); });
		Merchant* curptr = nullptr;
		if (it != allAccount.end()) {
			curptr = (Merchant*)allAccount[std::distance(allAccount.begin(), it)];
		}
		else {
			std::cout << "�Ҳ�����Ӧ�̼�" << std::endl;
			return;
		}
		std::cout << temptr->getNumber() << "\t\t"<<temptr->getName() << "\t" << temptr->getDescrip() << "\t" << temptr->getPrice(curptr->merDiscount[temptr->getgoodType()]) << "\t" <<
			temptr->getAmount() << "\t" << temptr->getgoodType() << "\t" <<std::endl;
	}
	std::cout << std::endl;
}

//ɸѡ������Ʒ
void Platform::searchGoods() const {
	std::cout << "�����Ҫɸѡ����Ʒ����" << std::endl;
	std::string name;
	std::cin >> name;
	std::cout << setiosflags(std::ios::fixed) << std::setprecision(2);
	std::cout << "�����̼ұ��\t" << "��Ʒ����\t" << "��Ʒ����\t" << "�۸�\t" << "ʣ����\t" << "��Ʒ����\t"  << std::endl;

	for (int i = 0; i < allGoods.size(); i++) {
		auto temptr = allGoods[i];
		if (auto it = temptr->getName().find(name) != std::string::npos) {
			auto it2 = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getNumber() == temptr->getNumber(); });
			Merchant* curptr = nullptr;
			if (it2 != allAccount.end()) {
				curptr = (Merchant*)allAccount[std::distance(allAccount.begin(), it2)];
			}
			else {
				std::cout << "�Ҳ�����Ӧ�̼�" << std::endl;
				return;
			}
			std::cout << temptr->getNumber() << "\t\t" << temptr->getName() << "\t" << temptr->getDescrip() << "\t" << temptr->getPrice(curptr->merDiscount[temptr->getgoodType()]) << "\t" <<
				temptr->getAmount() << "\t" << temptr->getgoodType() << "\t" << std::endl;
		}
	}
	//auto it = std::find_if(allGoods.begin(), allGoods.end(), [&](Goods* A)-> bool {return A->name.find(name); });
	//while (it != allGoods.end()) {
	//	std::cout << (*it)->name <<" "<< (*it)->descrip <<" "<< (*it)->price <<" "<< (*it)->amount <<" "<< (*it)->goodType << std::endl;
	//	it = std::find_if(it, allGoods.end(), [&](Goods* A)-> bool {return A->name == name; });
	//}
	std::cout << std::endl;
}

//ע���û�����
void Platform::registerUser() {
	int type;
	print pp;
	std::cout << "��������Ҫע����û�����\n" << "ע���������˻�����0��ע���̼��˻�����1" << std::endl;
	pp.input(type);
	while (type != 0 && type != 1) {
		std::cout << "��������˻������������������룡" << std::endl;
		pp.input(type);
	}
	std::cout << "����ѡ��ɹ���������һ��" << std::endl;

	std::cout << "������ע����û���" << std::endl;
	std::string tid;
	std::cin >> tid;
	auto it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getId() == tid; });
	while (it != allAccount.end()) {
		std::cout << "��������û��Ѿ����ڣ�����������" << std::endl;
		std::cin >> tid;
		it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getId() == tid; });
	}
	std::cout << "�û��������ɹ���������һ��" << std::endl;

	std::cout << "����������" << std::endl;
	std::string tpasswd;
	std::cin >> tpasswd;

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
		std::cout << "ע���û�ʧ��" << std::endl;
		return;
	}
	std::cout << "ע���û��ɹ�" << std::endl;

	//�����û��浽�ļ���
	std::fstream file;
	file.open(fileAccount, std::ios::out|std::ios::app);
	if (!file.is_open()) {
		std::cout << "�����û��ļ�ʧ��" << std::endl;
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
		std::cout << "��ʱ����ע����û�" << std::endl;
	}

	std::cout << "�������û���" << std::endl;
	std::cin >> tid;
	auto it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getId() == tid; });
	while (it == allAccount.end()) {
		std::cout << "��������û������ڣ�����������" << std::endl;
		std::cin >> tid;
		it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getId() == tid; });
	}

	auto curptr= allAccount[std::distance(allAccount.begin(), it)]; //�ҵ���ʱ���û�ָ��

	cpasswd = curptr->getPasswd();
	tType = curptr->userType;
	tbalance = curptr->getBalance();

	std::cout << "����������" << std::endl;
	std::cin >> tpasswd;
	while (cpasswd != tpasswd) {
		std::cout << "�������������������������" << std::endl;
		std::cin >> tpasswd;
	}
	std::cout << "����������ȷ����¼�ɹ�" << std::endl;

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
	//	std::cout << "ע���û�ʧ��" << std::endl;
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
		std::cout << "�û��ļ��򿪴���" << std::endl;
	}
	else {
		while (file >> number_ >> id_ >> passwd_ >> balance_ >> userType_) {
			//file >> id_ >> passwd_ >> balance_ >> userType_;
			/*std::cout << id_ <<" "<< passwd_ <<""<<
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
				std::cout << "�û��ļ������������飡" << std::endl;
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
		std::cout << "�û��ļ��򿪴���" << std::endl;
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
				std::cout << "�Ҳ�����Ӧ�̼�" << std::endl;
				return;
			}

			if (goodType_ == FOOD) {
				Food * foodptr = new Food(number_ ,name_ ,descrip_ , price_ , amount_ ,Good( goodType_));
				curptr->merGoods.push_back(foodptr);
				allGoods.push_back(foodptr);
				//std::cout << "11 ";
			}
			else if (goodType_ == BOOK) {
				Book* bookptr = new Book(number_ ,name_, descrip_, price_, amount_, Good(goodType_));
				curptr->merGoods.push_back(bookptr);
				allGoods.push_back(bookptr);
				//std::cout << "12 ";
			}
			else if (goodType_ == CLOTHES) {
				Clothes* clothptr = new Clothes(number_, name_, descrip_, price_, amount_, Good(goodType_));
				curptr->merGoods.push_back(clothptr);
				//std::cout << "13 ";
				allGoods.push_back(clothptr);
			}
			else {
				std::cout << "��Ʒ�ļ������������飡" << std::endl;
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
		std::cout << "���û��ļ�ʧ��" << std::endl;
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
		std::cout << "���û��ļ�ʧ��" << std::endl;
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
	std::cout << "�����ﳵ�ڵ���Ʒ��" << std::endl;
	std::cout << "�����̼ұ��\t" << "��Ʒ����\t" << "��Ʒ����\t" << "�۸�\t" << "�����\t" <<"��Ʒ����\t"<< std::endl;
	std::cout << setiosflags(std::ios::fixed) << std::setprecision(2);
	for (int i = 0; i < consumer->shopcart.size(); i++) {
		auto temptr = consumer->shopcart[i]->getGoodsCard();
		//�ҵ���Ӧ��Ʒ�������̼�
		auto it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getNumber() == temptr->getNumber(); });
		Merchant* curptr = nullptr;
		if (it != allAccount.end()) {
			curptr = (Merchant*)allAccount[std::distance(allAccount.begin(), it)];
		}
		else {
			std::cout << "�Ҳ�����Ӧ�̼�" << std::endl;
			return;
		}
		std::cout << temptr->getNumber() << "\t\t" << temptr->getName() << "\t" << temptr->getDescrip() << "\t" << temptr->getPrice(curptr->merDiscount[temptr->getgoodType()]) << "\t" <<
			consumer->shopcart[i]->getbuyNumber() << "\t" << temptr->getgoodType() << "\t" << std::endl;
	
	}
	std::cout << std::endl;
}

//չʾ����
void Platform::showOrder(Consumer*& consumer) const {
	std::cout << "�������ڵ���Ʒ��" << std::endl;
	std::cout << "�����̼ұ��\t" << "��Ʒ����\t" << "��Ʒ����\t" << "�۸�\t" << "�����\t" << "��Ʒ����\t" << std::endl;
	std::cout << setiosflags(std::ios::fixed) << std::setprecision(2);
	for (int i = 0; i < consumer->ordercart.size(); i++) {
		auto temptr = consumer->ordercart[i]->getGoodsCard();
		//�ҵ���Ӧ��Ʒ�������̼�
		auto it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getNumber() == temptr->getNumber(); });
		Merchant* curptr = nullptr;
		if (it != allAccount.end()) {
			curptr = (Merchant*)allAccount[std::distance(allAccount.begin(), it)];
		}
		else {
			std::cout << "�Ҳ�����Ӧ�̼�" << std::endl;
			return;
		}
		std::cout << temptr->getNumber() << "\t\t" << temptr->getName() << "\t" << temptr->getDescrip() << "\t" << temptr->getPrice(curptr->merDiscount[temptr->getgoodType()]) << "\t" <<
			consumer->ordercart[i]->getbuyNumber() << "\t" << temptr->getgoodType() << "\t" << std::endl;

	}
	std::cout << std::endl;

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
			std::cout << "�Ҳ�����Ӧ�̼�" << std::endl;
			//return ;
		}
		sum+= temptr->getPrice(curptr->merDiscount[temptr->getgoodType()])*consumer->ordercart[i]->getbuyNumber() ;
	}
	return sum;
}

//֧������
void Platform::payloadOrder(Consumer*& consumer,double & sum) {
	if (consumer->ordercart.size() == 0) {
		std::cout << "��ʱû�ж������޷�֧��" << std::endl;
		return;
	}

	if (! consumer->consumeBalance(sum)) {
		//����������Ʒ��������ָ�
		std::cout << "��ǰ����ֱ��ȡ��" << std::endl;
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
			std::cout << "�Ҳ�����Ӧ�̼�" << std::endl;
			return;
		}
		curptr->addBalance(temptr->getPrice(curptr->merDiscount[temptr->getgoodType()])* consumer->ordercart[i]->getbuyNumber());

	}
	consumer->ordercart.clear();
}