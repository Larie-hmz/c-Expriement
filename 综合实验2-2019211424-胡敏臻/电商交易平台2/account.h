#pragma once
#include"goods.h"
#include"book.h"
#include"clothes.h"
#include"food.h"
#include"print.h"
#include<string>
#include<vector>
#include<map>
#include<iomanip>
enum User{CONSUMER=0,MERCHANT};

class Account
{
protected:
	int number;         //记录用户的编号
	std::string id;     //记录用户的名称
	std::string passwd; //记录密码
	double balance;     //记录余额
public:
	User userType; 
public:

	Account(const std::string& id_="", const std::string& passwd_="",const double& balance_=0,const User & userType_= CONSUMER);
	Account(const Account& acc);
	~Account();

	int getNumber() const { return number; }
	void setNumber(const int& number_) { number = number_; }
	std::string getId() const { return id; }
	void setId(const std::string& i) { id = i;}
	std::string getPasswd() const { return passwd; }
	void setPasswd(const std::string& passw) { passwd = passw; }
	double getBalance() const { return balance; }
	void setBalance(const double& balanc) { balance = balanc; }
	virtual User getUserType()=0;
	//bool operator==(const std::string& id_);
	  
	void changePasswd();                       //修改用户密码
	void manageBalance();                      //管理用户
	void queryBalance()const;                  //查询余额
	void addBalance(double tbalance);          //充值
	bool consumeBalance(double tbalance);      //消费
};

