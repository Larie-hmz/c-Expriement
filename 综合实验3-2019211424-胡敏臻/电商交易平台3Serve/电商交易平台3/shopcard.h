#pragma once
#include "goods.h"
class Shopcard
{
    Goods* goodsCard;
    int buyNumber=0;
public:
    Shopcard(Goods* & good_,const int & buyNumber_);
    Shopcard(const Shopcard & shop_);
    ~Shopcard();
  
    int getbuyNumber() const { return buyNumber; }
    void setbuyNumber(const int& number) { this->buyNumber = number; }
    
    Goods* getGoodsCard() const { return goodsCard; }
    void setGoodsCard(Goods*& goodsCar) {  goodsCard = goodsCar; }
    
};

