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
	print pp(&ser);
	ser.in() << "������ԭ��������" << std::endl;
	ser.mySend();
	pp.input(beforewd);

	while (beforewd != passwd) {
		ser.in() << "�������ԭ��������������������" << std::endl;
		ser.mySend();
		pp.input(beforewd);
	}
	ser.in() << "������֤��ȷ��������Ҫ�޸ĵ�����" << std::endl;
	ser.mySend();
	pp.input( newwd);
	ser.in() << "�����޸ĳɹ�" << std::endl;
	
}

//������
void Account::manageBalance() {
	//serve ser;
	ser.in() << "***********************" << std::endl;
	ser.in() << "****����ѯ������1****" << std::endl;
	ser.in() << "****����ֵ������2****" << std::endl;
	ser.in() << "****��Ʒ����������3****" << std::endl;
	//ser.in() << "****�˳�����������0****" << std::endl;
	ser.in() << "***********************" << std::endl;

	int choice;
	print pp(&ser);
	ser.mySend();
	pp.input(choice);
	double tbalance = 0;
	switch (choice) {
	case 1:
		queryBalance();
		break;
	case 2:
		ser.in() << "��ʱ�˻������Ϊ" << balance << std::endl;
		ser.in() << "������Ҫ��ֵ������" << std::endl;
		ser.mySend();
		pp.input(tbalance);
		addBalance(tbalance);
		ser.in() << "��ʱ���Ϊ" << balance << std::endl;
		break;
	case 3:
		ser.in() << "��ʱ�˻������Ϊ" << balance << std::endl;
		ser.in() << "������Ҫ���ѵ�����" << std::endl;
		ser.mySend();
		pp.input(tbalance);
		consumeBalance(tbalance);
		break;
	default:
		ser.in() << "�������ѡ���д�" << std::endl;
		break;
	}
}

//��ѯ
void Account::queryBalance() const {
	//serve ser;
	ser.in() << "���˻������Ϊ" << balance << std::endl;
	
}

//��ֵ
void Account::addBalance(double tbalance) {
	//std::cout << "��ʱ�˻������Ϊ" << balance << std::endl;
	//std::cout << "������Ҫ��ֵ������" << std::endl;
	//double tbalance;
	print pp(&ser);
	//pp.input(tbalance);
	while (tbalance < 0) {
		ser.in() << "��ֵ��������Ҫ����0������������" << std::endl;
		ser.mySend();
		pp.input(tbalance);
	}

	balance += tbalance;
	//ser.in() << "��ʱ���Ϊ" << balance << std::endl;

}

//����
bool Account::consumeBalance(double tbalance) {
	//std::cout << "��ʱ�˻������Ϊ" << balance << std::endl;
	//std::cout << "������Ҫ���ѵ�����" << std::endl;
	//double tbalance;
	print pp(&ser);
	//pp.input(tbalance);
	if (tbalance < 0) {
		ser.in() << "���ѵ�������Ҫ����0" << std::endl;
		ser.mySend();
		pp.input(tbalance);
	}
	balance -= tbalance;
	if (balance<0) {
		ser.in() << "���Ѻ����С��0����ֹ����"  << std::endl;
		balance += tbalance;
		return false;
	}
	else {
		ser.in() << "���Ѻ����Ϊ" << balance << std::endl;

	}
	return true;
}