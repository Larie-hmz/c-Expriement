#pragma once
#include "goods.h"
class Book :
    public Goods
{
public:
	Book(const int number_,const std::string& name_, const std::string& descrip_ = "", const double& price_ = 0, const int& amount_ = 0, const Good& goodType_ = FOOD);
	Book(const Book& goods);
	~Book();
	virtual double getPrice(double discount = 1) override;
};

