#include "book.h"

Book::Book(const int number_,const std::string& name_, const std::string& descrip_ , const double& price_ , const int& amount_ , const Good& goodType_ ) {
	number = number_;
	name = name_;
	descrip = descrip_;
	price = price_;
	amount = amount_;
	goodType = goodType_;
}
Book::Book(const Book& goods) {
	number = goods.number;
	name = goods.name;
	descrip = goods.descrip;
	price = goods.price;
	amount = goods.amount;
	goodType = goods.goodType;
}
Book::~Book() {

}

double Book::getPrice(double discount ) {
	return this->price * discount;
}