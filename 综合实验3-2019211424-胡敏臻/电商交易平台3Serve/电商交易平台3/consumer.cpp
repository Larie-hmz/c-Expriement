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
	//释放指针
	for (int i = shopcart.size() - 1; i >= 0; i--) {
		delete shopcart[i];
	}
	for (int i = ordercart.size() - 1; i >= 0; i--) {
		delete ordercart[i];
	}
}

User Consumer::getUserType() {
	return userType;
}

//添加购物车
void Consumer::addShopcart(std::vector<Goods*>& allGoods) {
	if (allGoods.size() == 0) {
		ser.in() << "此时没有商品可以选择，不能添加购物车" << std::endl;
		return;
	}

	ser.in() << "请输入您要添加的商品名称" << std::endl;
	std::string name_;
	print pp(&ser);
	ser.mySend();
	pp.input(name_); 
	auto it = std::find_if(allGoods.begin(), allGoods.end(), [&](Goods* A)-> bool {return A->getName() == name_; });
	while (it == allGoods.end()) {
		ser.in() << "您输入的商品名称不存在，请重新输入商品名称" << std::endl;
		ser.mySend();
		pp.input(name_);
		it = std::find_if(allGoods.begin(), allGoods.end(), [&](Goods* A)-> bool {return A->getName() == name_; });
	}
	ser.in() << "成功选择商品，请输入您想添加的商品数量" << std::endl;
	Goods* curptr = allGoods[std::distance(allGoods.begin(), it)];
	if (curptr->getAmount() == 0) {
		ser.in() << "该商品的剩余量为0，不能添加商品" << std::endl;
		//ser.mySend();
		return;
	}
	ser.mySend();
	int buyNumber_;
	pp.input(buyNumber_);
	while (buyNumber_ > curptr->getAmount() || buyNumber_<1) {
		if (buyNumber_ > curptr->getAmount()) {
			ser.in() << "您添加的数量超过商品剩余量，请重新输入" << std::endl;
		}
		else {
			ser.in() << "您添加的数量小于1，请重新输入" << std::endl;
		}
		ser.mySend();
		pp.input(buyNumber_);
	}

	auto it2 = std::find_if(shopcart.begin(), shopcart.end(), [&](Shopcard* A)-> bool {return A->getGoodsCard()->getName() == name_; });
	if (it2 == shopcart.end()) {
		Shopcard* cardptr = new Shopcard(curptr, buyNumber_);
		shopcart.push_back(cardptr);
	}
	else {
		(*it2)->setbuyNumber((*it2)->getbuyNumber() + buyNumber_);
	}

	ser.in() << "您已经成功添加商品" << std::endl;

}

//修改购买数量
void Consumer::modifyShopcart( ) {
	ser.in() << "请输入您要修改的商品名称" << std::endl;
	ser.mySend();
	std::string name_;
	print pp(&ser);
	pp.input(name_);
	Shopcard* it=nullptr;
	auto itemp = shopcart.begin();
	for (int i = 0; i < shopcart.size(); i++) {
		if (shopcart[i]->getGoodsCard()->getName() == name_) {
			itemp++;
			it = shopcart[i];
			break;
		}
	}
	if (it == nullptr) {
		ser.in() << "购物车中无该商品，退出修改" << std::endl;
		return;
	}
	ser.in() << "成功选择商品，请输入您想修改的商品数量" << std::endl;
	ser.mySend();
	Goods* curptr = it->getGoodsCard();
	int buyNumber_;
	pp.input(buyNumber_);
	while (buyNumber_ > curptr->getAmount() || buyNumber_ < 0) {
		if (buyNumber_ > curptr->getAmount()) {
			ser.in() << "您修改的数量超过商品剩余量，请重新输入" << std::endl;
		}
		else {
			ser.in() << "您修改的数量小于0，请重新输入" << std::endl;
		}
		ser.mySend();
		pp.input(buyNumber_);
	}

	if (buyNumber_ == 0) {
		shopcart.erase(--itemp);
	}
	else {
		it->setbuyNumber(buyNumber_);
	}
	ser.in() << "您已经成功修改购物车" << std::endl;
}

//删除购物车中的商品
void Consumer::deleteShopcart() {
	ser.in() << "请输入您要删除的商品名称" << std::endl;
	ser.mySend();
	std::string name_;
	print pp(&ser);
	pp.input(name_);
	Shopcard* it = nullptr;
	auto itemp = shopcart.begin();
	for (int i = 0; i < shopcart.size(); i++) {
		itemp++;
		if (shopcart[i]->getGoodsCard()->getName() == name_) {
			it = shopcart[i];
			break;
		}
	}
	if (it == nullptr) {
		ser.in() << "购物车中无该商品，退出删除" << std::endl;
		return;
	}
	ser.in() << "成功选择商品，请输入您想删除的商品数量" << std::endl;
	ser.mySend();
	Goods* curptr = it->getGoodsCard();
	int buyNumber_;
	pp.input(buyNumber_);
	while (buyNumber_ > it->getbuyNumber() || buyNumber_ < 0) {
		if (buyNumber_ > it->getbuyNumber()) {
			ser.in() << "您删除的数量超过商品添加量，请重新输入" << std::endl;
		}
		else {
			ser.in() << "您删除的数量小于0，请重新输入" << std::endl;
		}
		ser.mySend();
		pp.input(buyNumber_);
	}

	if (it->getbuyNumber() - buyNumber_ == 0) {
		shopcart.erase(--itemp);
	}
	else {
		it->setbuyNumber(it->getbuyNumber() - buyNumber_);
	}
	ser.in() << "您已经成功删除商品" << std::endl;
}

//生成订单
void Consumer::generateOrder() {
	if (shopcart.size() == 0) {
		ser.in() << "购物车中没有商品，无法添加订单" << std::endl;
		return;
	}

	int choice = 1;
	while (choice) {
		ser.in() << "请输入您要添加的商品名称" << std::endl;
		ser.mySend();
		std::string name_;
		print pp(&ser);
		pp.input(name_);
		Shopcard* it = nullptr;
		auto itemp = shopcart.begin();
		for (int i = 0; i < shopcart.size(); i++) {
			itemp++;
			if (shopcart[i]->getGoodsCard()->getName() == name_) {
				it = shopcart[i];
				break;
			}
		}
		if (it == nullptr) {
			ser.in() << "购物车中无该商品" << std::endl;
		}
		else {
			//ser.in() << "成功选择商品" << std::endl;
			if (it->getGoodsCard()->getAmount() - it->getbuyNumber() < 0) {
				ser.in() << "该商品剩余量小于购买量，不符合条件，不能将此商品添加订单" << std::endl;
			}
			else {
				ser.in() << "成功选择商品" << std::endl;
				it->getGoodsCard()->setAmount(it->getGoodsCard()->getAmount() - it->getbuyNumber());
				ordercart.push_back(it);
				shopcart.erase(--itemp);
			}

		}
	
		ser.in() << "是否继续选择商品，继续输入1，退出输入0" << std::endl;
		ser.mySend();
		pp.input(choice);
	}


}

//取消订单
void Consumer::cancelOrder() {
	if (ordercart.size() == 0) {
		ser.in() << "此时无订单" << std::endl;
		return;
	}

	for (int i = 0; i < ordercart.size(); i++) {
		ordercart[i]->getGoodsCard()->setAmount(ordercart[i]->getGoodsCard()->getAmount() + ordercart[i]->getbuyNumber());
	}
	ordercart.clear();
	ser.in() << "已成功取消订单" << std::endl;

}