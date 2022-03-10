#pragma once
#include "goods.h"
class Clothes :
    public Goods
{
public:
	Clothes(const int number_,const std::string& name_, const std::string& descrip_ = "", const double& price_ = 0, const int& amount_ = 0, const Good& goodType_ = FOOD);
	Clothes(const Clothes& goods);
	~Clothes();
	virtual double getPrice(double discount = 1) override;
};

