#include "consumer.h"

Consumer::Consumer(const int number_,const std::string& id_ , const std::string& passwd_ , const double& balance_ , const User& userType_ ) {
	number = number_;
	id = id_;
	passwd = passwd_;
	balance = balance_;
	userType = userType_;
}
Consumer::Consumer(const Consumer& acc) {
	number = acc.number;
	id = acc.id;
	passwd = acc.passwd;
	balance = acc.balance;
	userType = acc.userType;
}
Consumer::~Consumer() {

}

User Consumer::getUserType() {
	return userType;
}