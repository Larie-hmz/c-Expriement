#pragma once
#include "goods.h"
class Food :
    public Goods
{
public:
	Food(const int number_ ,const std::string& name_, const std::string& descrip_ = "", const double& price_ = 0, const int& amount_ = 0, const Good& goodType_ = FOOD);
	Food(const Food& goods);
	~Food();
	virtual double getPrice(double discount = 1) override;
};

