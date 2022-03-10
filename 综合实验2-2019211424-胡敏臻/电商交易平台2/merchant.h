#pragma once
#include "account.h"
class Merchant :
    public Account
{ 
public:
    std::vector<Goods*> merGoods;         //存储该商家管理的商品
    std::map<int, double> merDiscount;    //存储该商家都不同类商品的打折情况
public:
    Merchant(const int number_,const std::string& id_ = "", const std::string& passwd_ = "", const double& balance_ = 0, const User& userType_ = MERCHANT);
    Merchant(Merchant& acc);
    ~Merchant();
public:
    virtual User getUserType() override;                                  //得到用户类型
    void addgoods(std::string filename, std::vector<Goods*>& allGoods);   //增加商品
    void manageGoods(std::vector<Goods*> & allGoods);                     //管理商品
    void haveDiscount() ;                                                 //对同类商品进行打折
};

