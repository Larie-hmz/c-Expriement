#include<iostream>
#include"platform.h"
#include"print.h"
#include"serve.h"
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")


int main() {
	try {

		//创建连接
		//serve ser;
		ser.setup();

		Platform plat;
		plat.initAccount();
		//std::cout << plat.allAccount.size();
		plat.initGoods();

		print pp(&ser);
		pp.printfi();

		int choice;
		ser.in() << "put choice" << std::endl;
		ser.mySend();
		pp.input(choice);


		Account* curAccptr = nullptr;
		int iflogin = 0, ifmer = -1;//iflogin标志是否登录,ifmer标志是否是商家
		if (!ser.iflegal()) {
			return 0;
		}
		while (choice) {
			if (!ser.iflegal()) {
				return 0;
			}
			switch (choice)
			{
			case 1:
				plat.registerUser();
				break;
			case 2:
				if (plat.allAccount.size() == 0) {
					ser.in() << "此时无已注册的用户" << std::endl;
					ser.mySend();
					break;
				}
				curAccptr = plat.loginUser();
				iflogin = 1;
				break;
			case 3:
				plat.showGoodsInfo(plat.allGoods);
				break;
			case 4:
				plat.searchGoods();
				break;
			case 9:
				pp.printfi();
				break;
			default:
				ser.in() << "您输入的选择有误" << std::endl;
				break;
			}
			if (iflogin != 1) {
				ser.in() << "put choice" << std::endl;
				ser.mySend();
				pp.input(choice);
			}
			else {
				if (curAccptr != nullptr) {
					if (curAccptr->userType == MERCHANT) {
						ifmer = 1;
					}
					else if (curAccptr->userType == CONSUMER) {
						ifmer = 0;
					}
					else {
						ser.in() << "类型有错" << std::endl;
					}
				}

				if (choice && ifmer == 1) {
					pp.printfm();
					//curAccptr = (Merchant*)curAccptr;
					Merchant* cur = (Merchant*)curAccptr;
					ser.in() << "put choice" << std::endl;
					ser.mySend();
					pp.input(choice);
					while (ifmer == 1 && iflogin == 1) {
						if (!ser.iflegal()) {
							return 0;
						}
						switch (choice)
						{
						case 0:
							iflogin = 0;
							ser.in() << "退出账号成功" << std::endl;
							break;
						case 1:
							curAccptr->changePasswd();
							break;
						case 2:
							curAccptr->manageBalance();
							break;
						case 3:
							plat.showGoodsInfo(cur->merGoods);
							break;
						case 4:
							plat.searchGoods();
							break;
						case 5:
							cur->addgoods(fileGoods, plat.allGoods);
							break;
						case 6:
							cur->manageGoods(plat.allGoods);
							break;
						case 7:
							cur->haveDiscount();
							break;
						case 8:
							plat.showGoodsInfo(plat.allGoods);
							break;
						case 9:
							pp.printfm();
							break;
						default:
							ser.in() << "您输入的选择有误" << std::endl;
							break;
						}
						ser.in() << "put choice" << std::endl;
						ser.mySend();
						pp.input(choice);
					}
				}
				else if (choice && ifmer == 0) {
					pp.printfc();
					//curAccptr = (Merchant*)curAccptr;
					Consumer* cur = (Consumer*)curAccptr;
					ser.in() << "put choice" << std::endl;
					ser.mySend();
					pp.input(choice);
					while (ifmer == 0 && iflogin == 1) {
						if (!ser.iflegal()) {
							return 0;
						}
						double orderSum = 0;
						switch (choice)
						{
						case 0:
							iflogin = 0;
							if (cur->ordercart.size() > 0) {
								ser.in() << "您还有为支付的账单，退出账户将取消订单" << std::endl;
								cur->cancelOrder();
							}
							ser.in() << "退出账号成功" << std::endl;
							break;
						case 1:
							curAccptr->changePasswd();
							break;
						case 2:
							curAccptr->manageBalance();
							break;
						case 3:
							plat.showGoodsInfo(plat.allGoods);
							break;
						case 4:
							plat.searchGoods();
							break;
						case 5:
							pp.printfcart();
							int choice2;
							ser.mySend();
							pp.input(choice2);
							switch (choice2)
							{
							case 1:
								plat.showGoodsInfo(plat.allGoods);
								cur->addShopcart(plat.allGoods);
								break;
							case 2:
								plat.showShopcart(cur);
								cur->deleteShopcart();
								break;
							case 3:
								plat.showShopcart(cur);
								cur->modifyShopcart();
								break;
							case 4:
								plat.showShopcart(cur);
								break;
							default:
								ser.in() << "您输入的选择有误" << std::endl;
								break;
							}
							break;
						case 6:
							pp.printforder();
							ser.mySend();
							pp.input(choice2);
							switch (choice2)
							{
							case 1:
								ser.in() << "请从购物车中添加商品 " << std::endl;
								plat.showShopcart(cur);
								cur->generateOrder();
								orderSum = plat.calOrder(cur);
								if (cur->ordercart.size() != 0) {
									ser.in() << "该订单的价格为" << setiosflags(std::ios::fixed) << std::setprecision(2) << orderSum << "元" << std::endl;

								}
								break;
							case 2:
								cur->cancelOrder();
								break;
							case 3:
								orderSum = plat.calOrder(cur);
								plat.payloadOrder(cur, orderSum);
								break;
							case 4:
								plat.showOrder(cur);
								break;
							default:
								break;
							}
							break;
						case 9:
							pp.printfc();
							break;
						default:
							ser.in() << "您输入的选择有误" << std::endl;
							break;
						}
						ser.in() << "put choice" << std::endl;
						ser.mySend();
						pp.input(choice);
					}
				}
			}

		}


		//退出程序前更新账号和用户信息
		plat.upgradeAccount();
		plat.upgradeGoods();

		ser.in() << "退出程序成功" << std::endl;
		ser.mySend();
	}
	catch (std::runtime_error& e) {
		std::cout << e.what();
	}
	//关闭连接
	ser.close();
	//ser.mySend();

	return 0;
}

