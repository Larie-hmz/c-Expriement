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
	std::cout << "请输入原来的密码" << std::endl;
	std::cin >> beforewd;
	while (beforewd != passwd) {
		std::cout << "您输入的原来密码有误，请重新输入" << std::endl;
		std::cin >> beforewd;
	}
	std::cout << "密码验证正确，请输入要修改的密码" << std::endl;
	std::cin >> newwd;
	passwd = newwd;
	std::cout << "密码修改成功" << std::endl;

}

//余额管理
void Account::manageBalance() {
	std::cout << "***********************" << std::endl;
	std::cout << "****余额查询请输入1****" << std::endl;
	std::cout << "****余额充值请输入2****" << std::endl;
	std::cout << "****商品消费请输入3****" << std::endl;
	//std::cout << "****退出管理请输入0****" << std::endl;
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
		std::cout << "您输入的选择有错" << std::endl;
		break;
	}
}

//查询
void Account::queryBalance() const {
	std::cout << "您账户的余额为" << balance << std::endl;
}

//充值
void Account::addBalance() {
	std::cout << "此时账户的余额为" << balance << std::endl;
	std::cout << "请输入要充值的数量" << std::endl;
	double tbalance;
	print pp;
	pp.input(tbalance);
	while (tbalance < 0) {
		std::cout << "充值的数量需要大于0，请重新输入" << std::endl;
		pp.input(tbalance);
	}

	balance += tbalance;
	std::cout << "充值后余额为" << balance << std::endl;
}

//消费
void Account::consumeBalance() {
	std::cout << "此时账户的余额为" << balance << std::endl;
	std::cout << "请输入要消费的数量" << std::endl;
	double tbalance;
	print pp;
	pp.input(tbalance);
	while (tbalance < 0) {
		std::cout << "消费的数量需要大于0，请重新输入" << std::endl;
		pp.input(tbalance);
	}
	balance -= tbalance;
	if (balance<0) {
		std::cout << "消费后余额小于0，禁止消费"  << std::endl;
		balance += tbalance;
	}
	else {
		std::cout << "消费后余额为" << balance << std::endl;
	}
	
}