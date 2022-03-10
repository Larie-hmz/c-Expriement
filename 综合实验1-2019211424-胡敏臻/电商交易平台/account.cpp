#include "account.h"
#include<iostream>
using std::cout;
using std::endl;

Account::Account(const std::string& id_ , const std::string& passwd_ , const double& balance_, const User& userType_) {
	id = id_;
	passwd = passwd_;
	balance = balance_;
	userType = userType_;
}

Account::Account(const Account& acc) {
	id = acc.id;
	passwd = acc.passwd;
	balance = acc.balance;
	userType = acc.userType;
}

Account::~Account() {

}

//bool Account::operator==(const std::string& id_) {
//	return (this->id == id_);
//}

//�޸�����
void Account::changePasswd() {
	std::string beforewd,newwd;
	std::cout << "������ԭ��������" << std::endl;
	std::cin >> beforewd;
	while (beforewd != passwd) {
		std::cout << "�������ԭ��������������������" << std::endl;
		std::cin >> beforewd;
	}
	std::cout << "������֤��ȷ��������Ҫ�޸ĵ�����" << std::endl;
	std::cin >> newwd;
	passwd = newwd;
	std::cout << "�����޸ĳɹ�" << std::endl;

}

//������
void Account::manageBalance() {
	std::cout << "***********************" << std::endl;
	std::cout << "****����ѯ������1****" << std::endl;
	std::cout << "****����ֵ������2****" << std::endl;
	std::cout << "****��Ʒ����������3****" << std::endl;
	//std::cout << "****�˳�����������0****" << std::endl;
	std::cout << "***********************" << std::endl;

	int choice;
	print pp;
	pp.input(choice);
	switch (choice) {
	case 1:
		queryBalance();
		break;
	case 2:
		addBalance();
		break;
	case 3:
		consumeBalance();
		break;
	default:
		std::cout << "�������ѡ���д�" << std::endl;
		break;
	}
}

//��ѯ
void Account::queryBalance() const {
	std::cout << "���˻������Ϊ" << balance << std::endl;
}

//��ֵ
void Account::addBalance() {
	std::cout << "��ʱ�˻������Ϊ" << balance << std::endl;
	std::cout << "������Ҫ��ֵ������" << std::endl;
	double tbalance;
	print pp;
	pp.input(tbalance);
	while (tbalance < 0) {
		std::cout << "��ֵ��������Ҫ����0������������" << std::endl;
		pp.input(tbalance);
	}

	balance += tbalance;
	std::cout << "��ֵ�����Ϊ" << balance << std::endl;
}

//����
void Account::consumeBalance() {
	std::cout << "��ʱ�˻������Ϊ" << balance << std::endl;
	std::cout << "������Ҫ���ѵ�����" << std::endl;
	double tbalance;
	print pp;
	pp.input(tbalance);
	while (tbalance < 0) {
		std::cout << "���ѵ�������Ҫ����0������������" << std::endl;
		pp.input(tbalance);
	}
	balance -= tbalance;
	if (balance<0) {
		std::cout << "���Ѻ����С��0����ֹ����"  << std::endl;
		balance += tbalance;
	}
	else {
		std::cout << "���Ѻ����Ϊ" << balance << std::endl;
	}
	
}