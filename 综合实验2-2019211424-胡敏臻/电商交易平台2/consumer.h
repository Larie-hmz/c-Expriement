#pragma once
#include "account.h"
#include "shopcard.h"

class Consumer :
    public Account
{
public:
    std::vector <Shopcard* > shopcart;
    std::vector <Shopcard* > ordercart;
    //std::vector <std::vector <Shopcard* > > orders;
public:
    Consumer(const int number_, const std::string& id_="", const std::string& passwd_="", const double& balance_=0, const User& userType_=CONSUMER);
    Consumer(const Consumer& acc);
    ~Consumer();
public:
    virtual User getUserType() override;

    //添加购物车
    void addShopcart(std::vector<Goods*>& allGoods);
    //修改购物车商品
    void modifyShopcart( );
    //删除购物车中的商品
    void deleteShopcart();
    //生成订单
    void generateOrder();
    //取消订单
    void cancelOrder();
};

