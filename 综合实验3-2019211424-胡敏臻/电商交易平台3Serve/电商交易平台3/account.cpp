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

//修改密码
void Account::changePasswd() {
	std::string beforewd,newwd;
	print pp(&ser);
	ser.in() << "请输入原来的密码" << std::endl;
	ser.mySend();
	pp.input(beforewd);

	while (beforewd != passwd) {
		ser.in() << "您输入的原来密码有误，请重新输入" << std::endl;
		ser.mySend();
		pp.input(beforewd);
	}
	ser.in() << "密码验证正确，请输入要修改的密码" << std::endl;
	ser.mySend();
	pp.input( newwd);
	ser.in() << "密码修改成功" << std::endl;
	
}

//余额管理
void Account::manageBalance() {
	//serve ser;
	ser.in() << "***********************" << std::endl;
	ser.in() << "****余额查询请输入1****" << std::endl;
	ser.in() << "****余额充值请输入2****" << std::endl;
	ser.in() << "****商品消费请输入3****" << std::endl;
	//ser.in() << "****退出管理请输入0****" << std::endl;
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
		ser.in() << "此时账户的余额为" << balance << std::endl;
		ser.in() << "请输入要充值的数量" << std::endl;
		ser.mySend();
		pp.input(tbalance);
		addBalance(tbalance);
		ser.in() << "此时余额为" << balance << std::endl;
		break;
	case 3:
		ser.in() << "此时账户的余额为" << balance << std::endl;
		ser.in() << "请输入要消费的数量" << std::endl;
		ser.mySend();
		pp.input(tbalance);
		consumeBalance(tbalance);
		break;
	default:
		ser.in() << "您输入的选择有错" << std::endl;
		break;
	}
}

//查询
void Account::queryBalance() const {
	//serve ser;
	ser.in() << "您账户的余额为" << balance << std::endl;
	
}

//充值
void Account::addBalance(double tbalance) {
	//std::cout << "此时账户的余额为" << balance << std::endl;
	//std::cout << "请输入要充值的数量" << std::endl;
	//double tbalance;
	print pp(&ser);
	//pp.input(tbalance);
	while (tbalance < 0) {
		ser.in() << "充值的数量需要大于0，请重新输入" << std::endl;
		ser.mySend();
		pp.input(tbalance);
	}

	balance += tbalance;
	//ser.in() << "此时余额为" << balance << std::endl;

}

//消费
bool Account::consumeBalance(double tbalance) {
	//std::cout << "此时账户的余额为" << balance << std::endl;
	//std::cout << "请输入要消费的数量" << std::endl;
	//double tbalance;
	print pp(&ser);
	//pp.input(tbalance);
	if (tbalance < 0) {
		ser.in() << "消费的数量需要大于0" << std::endl;
		ser.mySend();
		pp.input(tbalance);
	}
	balance -= tbalance;
	if (balance<0) {
		ser.in() << "消费后余额小于0，禁止消费"  << std::endl;
		balance += tbalance;
		return false;
	}
	else {
		ser.in() << "消费后余额为" << balance << std::endl;

	}
	return true;
}