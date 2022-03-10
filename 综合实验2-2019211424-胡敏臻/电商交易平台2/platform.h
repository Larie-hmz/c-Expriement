#pragma once
#include"account.h"
#include"merchant.h"
#include"consumer.h"
#include"goods.h"
#include"book.h"
#include"clothes.h"
#include"food.h"
#include<vector>
#include<iterator>
#include<set>
#include<algorithm>
#include <iomanip>



#define fileAccount "allAccount.txt"
#define fileGoods "allGoods.txt"

class Platform
{
public:
	std::vector<Account*> allAccount;   //��¼�����̼���Ϣ
	std::vector<Goods*> allGoods;       //��¼������Ʒ��Ϣ
	//std::map<int, double> allDiscount;
private:
	int number = 0;
public:
	Platform();    //���캯��
	~Platform();   //��������

	void showGoodsInfo(const std::vector<Goods*>& merGoods) const;  //չʾ�̼���Ʒ��Ϣ
	void searchGoods() const;                                       //ɸѡ������Ʒ
	void registerUser();                                            //ע���û�     
	Account* loginUser();                                           //��¼�û�

	void initAccount();                                             //��ʼ���˻�
	void initGoods();                                               //��ʼ����Ʒ
	void upgradeAccount() const;                                    //���ļ��и����û���Ϣ
	void upgradeGoods() const;                                      //���ļ��и�����Ʒ��Ϣ     

	void showShopcart(Consumer* & consumer ) const;                 //չʾ���ﳵ                                              
	void showOrder(Consumer* & consumer) const;                     //չʾ����
	double calOrder(Consumer*& consumer) const;                     //���㶩��
	void payloadOrder(Consumer*& consumer, double& sum);
};