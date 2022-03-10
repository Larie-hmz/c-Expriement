#include<iostream>
#include"platform.h"
#include"print.h"

int main() {
	Platform plat;
	if (!plat.initAccount()) {
		std::cout << "�û��ļ��������˳�����" << std::endl;

		return 0;
	}
	//std::cout << plat.allAccount.size();
	if (!plat.initGoods()) {
		std::cout << "��Ʒ�ļ��������˳�����" << std::endl;

		return 0;
	}

	print pp;
	pp.printfi();

	int choice;
	std::cout << "put choice" << std::endl;
	pp.input(choice);

	Account* curAccptr=nullptr;
	int iflogin = 0, ifmer=-1;//iflogin��־�Ƿ��¼,ifmer��־�Ƿ����̼�

	while (choice) {
		switch (choice)
		{
		case 1:
			plat.registerUser();
			break;
		case 2:
			if (plat.allAccount.size() == 0) {
				std::cout << "��ʱ����ע����û�" << std::endl;
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
			break;
		}
		if (iflogin != 1) {
			std::cout << "put choice" << std::endl;
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
					std::cout << "�����д�" << std::endl;
				}
			}
			
			if (choice && ifmer == 1) {
				pp.printfm();
				//curAccptr = (Merchant*)curAccptr;
				Merchant* cur = (Merchant*)curAccptr;
				std::cout << "put choice" << std::endl;
				pp.input(choice);
				while (ifmer == 1&& iflogin==1) {
					switch (choice)
					{
					case 0:
						iflogin = 0;
						std::cout << "�˳��˺ųɹ�" << std::endl;
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
						cur->addgoods(fileGoods,plat.allGoods);
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
						std::cout << "�������ѡ������" << std::endl;
						break;
					}
					std::cout << "put choice" << std::endl;
					pp.input(choice);
				}
			}
			else if (choice && ifmer == 0) {
				pp.printfc();
				//curAccptr = (Merchant*)curAccptr;
				Consumer* cur = (Consumer*)curAccptr;
				std::cout << "put choice" << std::endl;
				pp.input(choice);
				while (ifmer == 0 && iflogin==1) {
					switch (choice)
					{
					case 0:
						iflogin = 0;
						std::cout << "�˳��˺ųɹ�" << std::endl;
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
					case 9:
						pp.printfc();
						break;
					default:
						std::cout << "�������ѡ������" << std::endl;
						break;
					}
					std::cout << "put choice" << std::endl;
					pp.input(choice);
				}
			}
		}

	}
	

	//�˳�����ǰ�����˺ź��û���Ϣ
	plat.upgradeAccount();
	plat.upgradeGoods();

	std::cout << "�˳�����ɹ�" << std::endl;

	return 0;
}

