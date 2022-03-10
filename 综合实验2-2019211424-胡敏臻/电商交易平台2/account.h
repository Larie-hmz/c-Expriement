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
	int number;         //��¼�û��ı��
	std::string id;     //��¼�û�������
	std::string passwd; //��¼����
	double balance;     //��¼���
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
	  
	void changePasswd();                       //�޸��û�����
	void manageBalance();                      //�����û�
	void queryBalance()const;                  //��ѯ���
	void addBalance(double tbalance);          //��ֵ
	bool consumeBalance(double tbalance);      //����
};

