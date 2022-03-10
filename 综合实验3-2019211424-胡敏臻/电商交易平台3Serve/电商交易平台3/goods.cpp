#include "goods.h"
#include"platform.h"

Goods::Goods(const std::string& name_, const std::string& descrip_ , const double& price_ , const int& amount_, const Good& goodType_ ) {
	name = name_;
	descrip = descrip_;
	price = price_;
	amount = amount_;
	goodType = goodType_;
}

Goods::Goods(const Goods& goods) {
	name = goods.name;
	descrip = goods.descrip;
	price = goods.price;
	amount = goods.amount;
	goodType = goods.goodType;
}

Goods::~Goods() {

}


