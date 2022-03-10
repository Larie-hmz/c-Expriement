#include "clothes.h"

Clothes::Clothes(const int number_,const std::string& name_, const std::string& descrip_ , const double& price_ , const int& amount_ , const Good& goodType_ ) {
	number = number_;
	name = name_;
	descrip = descrip_;
	price = price_;
	amount = amount_;
	goodType = goodType_;
}
Clothes::Clothes(const Clothes& goods) {
	number = goods.number;
	name = goods.name;
	descrip = goods.descrip;
	price = goods.price;
	amount = goods.amount;
	goodType = goods.goodType;
}
Clothes::~Clothes() {

}

double Clothes::getPrice(double discount ) {
	return this->price * discount;
}