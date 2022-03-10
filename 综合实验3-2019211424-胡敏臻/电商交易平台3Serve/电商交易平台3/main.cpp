#include<iostream>
#include"platform.h"
#include"print.h"
#include"serve.h"
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")


int main() {
	try {

		//��������
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
		int iflogin = 0, ifmer = -1;//iflogin��־�Ƿ��¼,ifmer��־�Ƿ����̼�
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
					ser.in() << "��ʱ����ע����û�" << std::endl;
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
				ser.in() << "�������ѡ������" << std::endl;
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
						ser.in() << "�����д�" << std::endl;
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
							ser.in() << "�˳��˺ųɹ�" << std::endl;
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
							ser.in() << "�������ѡ������" << std::endl;
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
								ser.in() << "������Ϊ֧�����˵����˳��˻���ȡ������" << std::endl;
								cur->cancelOrder();
							}
							ser.in() << "�˳��˺ųɹ�" << std::endl;
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
								ser.in() << "�������ѡ������" << std::endl;
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
								ser.in() << "��ӹ��ﳵ�������Ʒ " << std::endl;
								plat.showShopcart(cur);
								cur->generateOrder();
								orderSum = plat.calOrder(cur);
								if (cur->ordercart.size() != 0) {
									ser.in() << "�ö����ļ۸�Ϊ" << setiosflags(std::ios::fixed) << std::setprecision(2) << orderSum << "Ԫ" << std::endl;

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
							ser.in() << "�������ѡ������" << std::endl;
							break;
						}
						ser.in() << "put choice" << std::endl;
						ser.mySend();
						pp.input(choice);
					}
				}
			}

		}


		//�˳�����ǰ�����˺ź��û���Ϣ
		plat.upgradeAccount();
		plat.upgradeGoods();

		ser.in() << "�˳�����ɹ�" << std::endl;
		ser.mySend();
	}
	catch (std::runtime_error& e) {
		std::cout << e.what();
	}
	//�ر�����
	ser.close();
	//ser.mySend();

	return 0;
}

