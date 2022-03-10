#pragma once
#include"print.h"
#include<string>
#include<iostream>
enum Good{FOOD=0,BOOK,CLOTHES};

class Goods
{
protected:
	int number;            //��ʾ��Ʒ�������̼ұ��
	std::string name;      //��Ʒ����
	std::string descrip;   //��Ʒ����
	double price;          //��Ʒ�۸�
	int amount;            //��Ʒʣ����
	Good goodType;         //��Ʒ����
public:
	Goods(const std::string& name_="", const std::string& descrip_ = "", const double& price_ = 0, const int& amount_ = 0, const Good& goodType_=FOOD);
	Goods(const Goods& goods);
	~Goods();

	//����Ϊ�ı�ͻ�ó�Ա�����ĺ���
	virtual double getPrice(double discount) { return price * discount; }
	int getNumber() const { return number; }
	void setNumber(const int& number) { this->number = number; }
	std::string getName() const { return name; }
	void setName(const std::string& name) { this->name = name; }
	std::string getDescrip() const { return descrip; }
	void setDescrip(const std::string& descri) { descrip = descri; }
	double getPrice() const { return price; }
	void setPrice(const double& pric) { price = pric; }
	int getAmount() const { return amount; }
	void setAmount(const int& amoun) { amount = amoun; }
	Good getgoodType() const { return goodType; }
	void setgoodType(const Good &goodTYp) { goodType = goodTYp; }



};
