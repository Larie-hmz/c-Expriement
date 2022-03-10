#include "merchant.h"
#include<iostream>
#include<fstream>

//构造函数
Merchant::Merchant(const int number_, const std::string& id_ , const std::string& passwd_, const double& balance_ , const User& userType_ ) {
	number = number_;
	id = id_;
	passwd = passwd_;
	balance = balance_;
	userType = userType_;

	merDiscount[0] = 1;
	merDiscount[1] = 1;
	merDiscount[2] = 1;
}

//拷贝构造函数
Merchant::Merchant(Merchant& acc) {
	number = acc.number;
	id = acc.id;
	passwd = acc.passwd;
	balance = acc.balance;
	userType = acc.userType;

	merDiscount[0] = acc.merDiscount[0];
	merDiscount[1] = acc.merDiscount[1];
	merDiscount[2] = acc.merDiscount[2];
}

//析构函数
Merchant::~Merchant() {
	for (int i = merGoods.size() - 1; i >= 0; i--) {
		delete merGoods[i];
	}
}

//得到用户类型
User Merchant::getUserType() {
	return userType;
}

//增加商品
void Merchant::addgoods(std::string filename, std::vector<Goods*>& allGoods) {
	ser.in() << "请依次输入商品名字，描述信息，价格，剩余量，类型" << std::endl;
	std::string name_;
	std::string descrip_;
	double price_;
	int amount_;
	int goodType_;

	print pp(&ser);
	ser.in() << "请输入商品名字" << std::endl;
	ser.mySend();
	pp.input(name_); 
	if (!ser.iflegal()) {
		ser.close();
		return;
	}
	auto it = std::find_if(allGoods.begin(), allGoods.end(), [&](Goods* A)-> bool {return A->getName() == name_; });
	while (it != allGoods.end()) {
		ser.in() << "您输入的商品名称已经存在，请重新输入商品名称" << std::endl;
		ser.mySend();
		pp.input(name_);
		it = std::find_if(allGoods.begin(), allGoods.end(), [&](Goods* A)-> bool {return A->getName() == name_; });
	}

	ser.in() << "请输入描述信息" << std::endl;
	ser.mySend();
	pp.input(descrip_); 

	ser.in() << "请输入价格" << std::endl;
	ser.mySend();
	pp.input(price_);
	while (price_ < 0) {
		ser.in() << "您输入的商品价格小于0，请重新输入商品价格" << std::endl;
		ser.mySend();
		pp.input(price_);
	}

	ser.in() << "请输入剩余量" << std::endl;
	ser.mySend();
	pp.input(amount_);
	while (amount_ < 0) {
		ser.in() << "您输入的商品剩余量小于0，请重新输入商品剩余量" << std::endl;
		ser.mySend();
		pp.input(amount_);
	}
	ser.in() << "请输入类型" << std::endl;
	ser.mySend();
	pp.input(goodType_);
	while (goodType_ != FOOD && goodType_ != BOOK && goodType_ != CLOTHES) {
		ser.in() << "商品文件输入类型有误，请重新输入！" << std::endl;
		ser.mySend();
		pp.input(goodType_);
	}

	//同时增加所有商品和该用户中的商品
	if (goodType_ == FOOD) {
		Food* foodptr = new Food(getNumber(),name_, descrip_, price_, amount_, Good(goodType_));
		merGoods.push_back(foodptr);
		allGoods.push_back(foodptr);
	}
	else if (goodType_ == BOOK) {
		Book* bookptr = new Book(getNumber(),name_, descrip_, price_, amount_, Good(goodType_));
		merGoods.push_back(bookptr);
		allGoods.push_back(bookptr);
	}
	else if (goodType_ == CLOTHES) {
		Clothes* clothptr = new Clothes(getNumber(),name_, descrip_, price_, amount_, Good(goodType_));
		merGoods.push_back(clothptr);
		allGoods.push_back(clothptr);
	}

	ser.in() << "您已成功添加商品" << std::endl;
	//std::fstream fgoods;
	//fgoods.open(filename, std::ios::in | std::ios::app);
	//if (!fgoods.is_open()) {
	//	ser.in() << "打开商品文件发生错误" << std::endl;
	//}
	//else {
	//	fgoods << name_ << " " << descrip_ << " " << price_ << " " << amount_ << "" << goodType_ <<std::endl ;
	//	ser.in() << "成功插入一条商品信息"<<std::endl;
	//}
	//fgoods.close();
}

//管理商品
void Merchant::manageGoods(std::vector<Goods*> & allGoods) {
	if (merGoods.size() == 0) {
		ser.in() << "该商家目前没有管理的商品" << std::endl;
		return;
	}
	print pp(&ser);
	ser.in() << "请输出要管理的商品名称" << std::endl;
	std::string name_;
	ser.mySend();
	pp.input(name_);
	//查找在用户中是否有该商品，判断是否相等运用了lambda表达式
	auto it = std::find_if(merGoods.begin(), merGoods.end(), [&](Goods* A)-> bool {return A->getName() == name_; });
	while (it == merGoods.end()) {
		ser.in() << "您输入的商品名称不存在，请重新输入" << std::endl;
		ser.mySend();
		pp.input(name_);
		it = std::find_if(merGoods.begin(), merGoods.end(), [&](Goods* A)-> bool {return A->getName() == name_; });
	}

	auto curptr = merGoods[std::distance(merGoods.begin(), it)];
	ser.in() << "此时商品原价" << curptr->getPrice() << "    此时商品剩余量" << curptr->getAmount() << std::endl;
	int choice;
	ser.in() << "修改价格输入0，修改剩余量输入1" << std::endl;
	ser.mySend();
	pp.input(choice);
	switch (choice)
	{
	case 0:
		ser.in() << "请输入要更改的价格" << std::endl;
		int tprice;
		ser.mySend();
		pp.input(tprice);
		while (tprice < 0) {
			ser.in() << "价格不能小于0，请重新输入" << std::endl;
			ser.mySend();
			pp.input(tprice);
		}
		ser.in() << "价格修改成功" << std::endl;
		curptr->setPrice(tprice);
		break;
	case 1:
		ser.in() << "请输入要更改的剩余量" << std::endl;
		int tamount;
		ser.mySend();
		pp.input(tamount);
		while (tamount < 0) {
			ser.in() << "剩余量不能小于0，请重新输入" << std::endl;
			ser.mySend();
			pp.input(tamount);
		}
		ser.in() << "剩余量修改成功" << std::endl;
		curptr->setAmount(tamount);
		break;
	default:
		ser.in() << "请输入的选择有误,退出" << std::endl;
		break;
	}
}

//同类商品打折
void Merchant::haveDiscount() {
	ser.in() << "请输入您要打折的商品类型\n食物类选择0，书本类选择1，衣服类选择2" << std::endl;
	int type;
	print pp(&ser);
	ser.mySend();
	pp.input(type);
	while (type != 0 && type != 1 && type != 2) {
		ser.in() << "您输入的选择有误，请重新输入" << std::endl;
		ser.mySend();
		pp.input(type);
	}

	ser.in() << "请输入你要打折的折扣(请输入0-1之间的数)" << std::endl;
	double discount;
	ser.mySend();
	pp.input(discount);
	while (!(0 < discount && discount < 1)) {
		ser.in() << "您输入的打折的折扣有误(请输入0-1之间的数)，请重新输入" << std::endl;
		ser.mySend();
		pp.input(discount);
	}
	
	merDiscount[type] = discount;
}

