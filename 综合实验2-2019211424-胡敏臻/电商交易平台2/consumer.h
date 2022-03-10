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

    //��ӹ��ﳵ
    void addShopcart(std::vector<Goods*>& allGoods);
    //�޸Ĺ��ﳵ��Ʒ
    void modifyShopcart( );
    //ɾ�����ﳵ�е���Ʒ
    void deleteShopcart();
    //���ɶ���
    void generateOrder();
    //ȡ������
    void cancelOrder();
};

