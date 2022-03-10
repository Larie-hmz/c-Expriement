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
	std::vector<Account*> allAccount;   //记录所有商家信息
	std::vector<Goods*> allGoods;       //记录所有商品信息
	//std::map<int, double> allDiscount;
private:
	int number = 0;
public:
	Platform();    //构造函数
	~Platform();   //析构函数

	void showGoodsInfo(const std::vector<Goods*>& merGoods) const;  //展示商家商品信息
	void searchGoods() const;                                       //筛选所有商品
	void registerUser();                                            //注册用户     
	Account* loginUser();                                           //登录用户

	void initAccount();                                             //初始化账户
	void initGoods();                                               //初始化商品
	void upgradeAccount() const;                                    //在文件中更新用户信息
	void upgradeGoods() const;                                      //在文件中更新商品信息     

	void showShopcart(Consumer* & consumer ) const;                 //展示购物车                                              
	void showOrder(Consumer* & consumer) const;                     //展示订单
	double calOrder(Consumer*& consumer) const;                     //计算订单
	void payloadOrder(Consumer*& consumer, double& sum);
};