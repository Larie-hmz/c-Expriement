#include "platform.h"
#include<fstream>
#include<iostream>

//构造函数
Platform::Platform() {
	//allDiscount[0] = 1;
	//allDiscount[1] = 1;
	//allDiscount[2] = 1;
}

//析构函数 删除指针数组里的指针
Platform::~Platform() {
	for (int i = allAccount.size()-1; i >=0 ; i--) {
		delete allAccount[i];
	}
	for (int i = allGoods.size() - 1; i >= 0; i--) {
		delete allGoods[i];
	}
}

//展示商家商品信息
void Platform::showGoodsInfo(const std::vector<Goods*> & merGoods) const {
	std::cout << "所属商家编号\t" << "商品名称\t" << "商品描述\t" << "价格\t" << "剩余量\t" << "商品类型\t" << std::endl;
	std::cout << setiosflags(std::ios::fixed) << std::setprecision(2);
	for (int i = 0; i < merGoods.size(); i++) {
		auto temptr = merGoods[i];
		//找到对应商品所属的商家
		auto it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getNumber() == temptr->getNumber(); });
		Merchant* curptr = nullptr;
		if (it != allAccount.end()) {
			curptr = (Merchant*)allAccount[std::distance(allAccount.begin(), it)];
		}
		else {
			std::cout << "找不到对应商家" << std::endl;
			return;
		}
		std::cout << temptr->getNumber() << "\t\t"<<temptr->getName() << "\t" << temptr->getDescrip() << "\t" << temptr->getPrice(curptr->merDiscount[temptr->getgoodType()]) << "\t" <<
			temptr->getAmount() << "\t" << temptr->getgoodType() << "\t" <<std::endl;
	}
	std::cout << std::endl;
}

//筛选所有商品
void Platform::searchGoods() const {
	std::cout << "请输出要筛选的商品名称" << std::endl;
	std::string name;
	std::cin >> name;
	std::cout << setiosflags(std::ios::fixed) << std::setprecision(2);
	std::cout << "所属商家编号\t" << "商品名称\t" << "商品描述\t" << "价格\t" << "剩余量\t" << "商品类型\t"  << std::endl;

	for (int i = 0; i < allGoods.size(); i++) {
		auto temptr = allGoods[i];
		if (auto it = temptr->getName().find(name) != std::string::npos) {
			auto it2 = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getNumber() == temptr->getNumber(); });
			Merchant* curptr = nullptr;
			if (it2 != allAccount.end()) {
				curptr = (Merchant*)allAccount[std::distance(allAccount.begin(), it2)];
			}
			else {
				std::cout << "找不到对应商家" << std::endl;
				return;
			}
			std::cout << temptr->getNumber() << "\t\t" << temptr->getName() << "\t" << temptr->getDescrip() << "\t" << temptr->getPrice(curptr->merDiscount[temptr->getgoodType()]) << "\t" <<
				temptr->getAmount() << "\t" << temptr->getgoodType() << "\t" << std::endl;
		}
	}
	//auto it = std::find_if(allGoods.begin(), allGoods.end(), [&](Goods* A)-> bool {return A->name.find(name); });
	//while (it != allGoods.end()) {
	//	std::cout << (*it)->name <<" "<< (*it)->descrip <<" "<< (*it)->price <<" "<< (*it)->amount <<" "<< (*it)->goodType << std::endl;
	//	it = std::find_if(it, allGoods.end(), [&](Goods* A)-> bool {return A->name == name; });
	//}
	std::cout << std::endl;
}

//注册用户功能
void Platform::registerUser() {
	int type;
	print pp;
	std::cout << "请输入您要注册的用户类型\n" << "注册消费者账户输入0；注册商家账户输入1" << std::endl;
	pp.input(type);
	while (type != 0 && type != 1) {
		std::cout << "您输入的账户类型有误，请重新输入！" << std::endl;
		pp.input(type);
	}
	std::cout << "类型选择成功，进入下一步" << std::endl;

	std::cout << "请输入注册的用户名" << std::endl;
	std::string tid;
	std::cin >> tid;
	auto it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getId() == tid; });
	while (it != allAccount.end()) {
		std::cout << "您输入的用户已经存在，请重新输入" << std::endl;
		std::cin >> tid;
		it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getId() == tid; });
	}
	std::cout << "用户名创建成功，进入下一步" << std::endl;

	std::cout << "请输入密码" << std::endl;
	std::string tpasswd;
	std::cin >> tpasswd;

	if (type == CONSUMER)
	{
		Consumer* Conptr = new Consumer(number, tid, tpasswd, 0, User(type));
		allAccount.push_back(Conptr);
	}
	else if (type == MERCHANT) {
		Merchant* Merptr = new Merchant(number, tid, tpasswd, 0, User(type));
		allAccount.push_back(Merptr);
	}
	else {
		std::cout << "注册用户失败" << std::endl;
		return;
	}
	std::cout << "注册用户成功" << std::endl;

	//将新用户存到文件中
	std::fstream file;
	file.open(fileAccount, std::ios::out|std::ios::app);
	if (!file.is_open()) {
		std::cout << "存入用户文件失败" << std::endl;
	}
	else {
		file << number <<" " << tid << " " << tpasswd << " " << 0 << " " << type << std::endl;
	}

	number++; //用户编号加1
	file.close();
}

//登录功能
Account* Platform::loginUser() {
	std::string tid;
	std::string tpasswd;
	std::string cpasswd;
	int tbalance;
	User tType;

	if (allAccount.size() == 0) {
		std::cout << "此时无已注册的用户" << std::endl;
	}

	std::cout << "请输入用户名" << std::endl;
	std::cin >> tid;
	auto it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getId() == tid; });
	while (it == allAccount.end()) {
		std::cout << "您输入的用户不存在，请重新输入" << std::endl;
		std::cin >> tid;
		it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getId() == tid; });
	}

	auto curptr= allAccount[std::distance(allAccount.begin(), it)]; //找到此时的用户指针

	cpasswd = curptr->getPasswd();
	tType = curptr->userType;
	tbalance = curptr->getBalance();

	std::cout << "请输入密码" << std::endl;
	std::cin >> tpasswd;
	while (cpasswd != tpasswd) {
		std::cout << "您输入的密码有误，请重新输入" << std::endl;
		std::cin >> tpasswd;
	}
	std::cout << "输入密码正确，登录成功" << std::endl;

	return curptr;

	//switch (tType)
	//{
	//case CONSUMER:
	//	Consumer* Conptr = new Consumer(tid, tpasswd, tbalance, User(tType));
	//	return Conptr;
	//	break;
	//case MERCHANT:
	//	Merchant* Merptr = new Merchant(tid, tpasswd, tbalance, User(tType));
	//	return Merptr;
	//	break;
	//default:
	//	std::cout << "注册用户失败" << std::endl;
	//	return;
	//	break;
	//}

	//return &allAccount[std::distance(allAccount.begin(),it)];

}

//初始化所有账户
void Platform::initAccount() {
	int number_;
	std::string id_;
	std::string passwd_;
	double balance_;
	int userType_;
	std::fstream file;
	file.open(fileAccount,std::ios::in);
	if (!file.is_open()) {
		std::cout << "用户文件打开错误" << std::endl;
	}
	else {
		while (file >> number_ >> id_ >> passwd_ >> balance_ >> userType_) {
			//file >> id_ >> passwd_ >> balance_ >> userType_;
			/*std::cout << id_ <<" "<< passwd_ <<""<<
				balance_ << " " << userType_;*/
			if (userType_ == 0) {
				Consumer* Conptr = new Consumer(number_, id_, passwd_, balance_, User(userType_));
				allAccount.push_back(Conptr);
				number++;
			}
			else if(userType_ == 1) {
				Merchant* Merptr = new Merchant(number_, id_, passwd_, balance_, User(userType_));
				allAccount.push_back(Merptr);
				number++;
			}
			else {
				std::cout << "用户文件内容有误，请检查！" << std::endl;
			}
			char ch;
			file.get(ch);
		}
	}
	file.close();
}

//初始化所有商品
void Platform::initGoods() {
	int number_;
	std::string name_;
	std::string descrip_;
	double price_;
	int amount_;
	int goodType_;
	std::fstream file;
	file.open(fileGoods, std::ios::in);
	if (!file.is_open()) {
		std::cout << "用户文件打开错误" << std::endl;
	}
	else {
		while (file >> number_ >> name_ >> descrip_ >> price_ >> amount_ >> goodType_) {
			//file >> name_ >> descrip_ >> price_ >> amount_ >> goodType_;
			/*if (std::find_if
			(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->id == name_; }) != allAccount.end()) {
				break;
			}*/
			auto it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getNumber()==number_; });
			Merchant* curptr = nullptr;
			if (it != allAccount.end()) {
				curptr = (Merchant *)allAccount[std::distance(allAccount.begin(), it)];
			}
			else {
				std::cout << "找不到对应商家" << std::endl;
				return;
			}

			if (goodType_ == FOOD) {
				Food * foodptr = new Food(number_ ,name_ ,descrip_ , price_ , amount_ ,Good( goodType_));
				curptr->merGoods.push_back(foodptr);
				allGoods.push_back(foodptr);
				//std::cout << "11 ";
			}
			else if (goodType_ == BOOK) {
				Book* bookptr = new Book(number_ ,name_, descrip_, price_, amount_, Good(goodType_));
				curptr->merGoods.push_back(bookptr);
				allGoods.push_back(bookptr);
				//std::cout << "12 ";
			}
			else if (goodType_ == CLOTHES) {
				Clothes* clothptr = new Clothes(number_, name_, descrip_, price_, amount_, Good(goodType_));
				curptr->merGoods.push_back(clothptr);
				//std::cout << "13 ";
				allGoods.push_back(clothptr);
			}
			else {
				std::cout << "商品文件内容有误，请检查！" << std::endl;
			}
			char ch;
			file.get(ch);
			if (ch != '\n') {
				file.get(ch);
			}
		}
	}
	file.close();
}

//更新用户信息
void Platform::upgradeAccount() const {
	std::fstream file;
	file.open(fileAccount,std::ios::out);
	if (!file.is_open()) {
		std::cout << "打开用户文件失败" << std::endl;
	}
	else {
		for (int i = 0; i < allAccount.size(); i++) {
			file << allAccount[i]->getNumber() <<" "<<allAccount[i]->getId() << " " << allAccount[i]->getPasswd() << " " << allAccount[i]->getBalance() << " " << allAccount[i]->userType << std::endl;
		}
	}
	file.close();
}

//更新商品信息
void Platform::upgradeGoods() const {
	std::fstream file;
	file.open(fileGoods, std::ios::out);
	if (!file.is_open()) {
		std::cout << "打开用户文件失败" << std::endl;
	}
	else {
		for (int i = 0; i < allGoods.size(); i++) {
			file << allGoods[i]->getNumber() << " "<< allGoods[i]->getName() << " " << allGoods[i]->getDescrip() << " " << allGoods[i]->getPrice() << " " << allGoods[i]->getAmount()<<" "<<allGoods[i]->getgoodType() <<std::endl;
		}
	}
	file.close();
}

//展示购物车
void Platform::showShopcart(Consumer* & consumer) const {
	std::cout << "您购物车内的商品有" << std::endl;
	std::cout << "所属商家编号\t" << "商品名称\t" << "商品描述\t" << "价格\t" << "添加量\t" <<"商品类型\t"<< std::endl;
	std::cout << setiosflags(std::ios::fixed) << std::setprecision(2);
	for (int i = 0; i < consumer->shopcart.size(); i++) {
		auto temptr = consumer->shopcart[i]->getGoodsCard();
		//找到对应商品所属的商家
		auto it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getNumber() == temptr->getNumber(); });
		Merchant* curptr = nullptr;
		if (it != allAccount.end()) {
			curptr = (Merchant*)allAccount[std::distance(allAccount.begin(), it)];
		}
		else {
			std::cout << "找不到对应商家" << std::endl;
			return;
		}
		std::cout << temptr->getNumber() << "\t\t" << temptr->getName() << "\t" << temptr->getDescrip() << "\t" << temptr->getPrice(curptr->merDiscount[temptr->getgoodType()]) << "\t" <<
			consumer->shopcart[i]->getbuyNumber() << "\t" << temptr->getgoodType() << "\t" << std::endl;
	
	}
	std::cout << std::endl;
}

//展示订单
void Platform::showOrder(Consumer*& consumer) const {
	std::cout << "您订单内的商品有" << std::endl;
	std::cout << "所属商家编号\t" << "商品名称\t" << "商品描述\t" << "价格\t" << "添加量\t" << "商品类型\t" << std::endl;
	std::cout << setiosflags(std::ios::fixed) << std::setprecision(2);
	for (int i = 0; i < consumer->ordercart.size(); i++) {
		auto temptr = consumer->ordercart[i]->getGoodsCard();
		//找到对应商品所属的商家
		auto it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getNumber() == temptr->getNumber(); });
		Merchant* curptr = nullptr;
		if (it != allAccount.end()) {
			curptr = (Merchant*)allAccount[std::distance(allAccount.begin(), it)];
		}
		else {
			std::cout << "找不到对应商家" << std::endl;
			return;
		}
		std::cout << temptr->getNumber() << "\t\t" << temptr->getName() << "\t" << temptr->getDescrip() << "\t" << temptr->getPrice(curptr->merDiscount[temptr->getgoodType()]) << "\t" <<
			consumer->ordercart[i]->getbuyNumber() << "\t" << temptr->getgoodType() << "\t" << std::endl;

	}
	std::cout << std::endl;

}

//计算订单
double Platform::calOrder(Consumer*& consumer) const {
	double sum = 0;
	for (int i = 0; i < consumer->ordercart.size(); i++) {
		auto temptr = consumer->ordercart[i]->getGoodsCard();
		//找到对应商品所属的商家
		auto it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getNumber() == temptr->getNumber(); });
		Merchant* curptr = nullptr;
		if (it != allAccount.end()) {
			curptr = (Merchant*)allAccount[std::distance(allAccount.begin(), it)];
		}
		else {
			std::cout << "找不到对应商家" << std::endl;
			//return ;
		}
		sum+= temptr->getPrice(curptr->merDiscount[temptr->getgoodType()])*consumer->ordercart[i]->getbuyNumber() ;
	}
	return sum;
}

//支付订单
void Platform::payloadOrder(Consumer*& consumer,double & sum) {
	if (consumer->ordercart.size() == 0) {
		std::cout << "此时没有订单，无法支付" << std::endl;
		return;
	}

	if (! consumer->consumeBalance(sum)) {
		//将订单中商品的添加量恢复
		std::cout << "当前订单直接取消" << std::endl;
		consumer->cancelOrder();
		return;
	}

	for (int i = 0; i < consumer->ordercart.size(); i++) {
		//curptr 为商家 temptr为商品
		auto temptr = consumer->ordercart[i]->getGoodsCard();
		//找到对应商品所属的商家
		auto it = std::find_if(allAccount.begin(), allAccount.end(), [&](Account* A)-> bool {return A->getNumber() == temptr->getNumber(); });
		Merchant* curptr = nullptr;
		if (it != allAccount.end()) {
			curptr = (Merchant*)allAccount[std::distance(allAccount.begin(), it)];
		}
		else {
			std::cout << "找不到对应商家" << std::endl;
			return;
		}
		curptr->addBalance(temptr->getPrice(curptr->merDiscount[temptr->getgoodType()])* consumer->ordercart[i]->getbuyNumber());

	}
	consumer->ordercart.clear();
}