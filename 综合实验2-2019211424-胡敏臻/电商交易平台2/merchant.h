#pragma once
#include "account.h"
class Merchant :
    public Account
{ 
public:
    std::vector<Goods*> merGoods;         //�洢���̼ҹ������Ʒ
    std::map<int, double> merDiscount;    //�洢���̼Ҷ���ͬ����Ʒ�Ĵ������
public:
    Merchant(const int number_,const std::string& id_ = "", const std::string& passwd_ = "", const double& balance_ = 0, const User& userType_ = MERCHANT);
    Merchant(Merchant& acc);
    ~Merchant();
public:
    virtual User getUserType() override;                                  //�õ��û�����
    void addgoods(std::string filename, std::vector<Goods*>& allGoods);   //������Ʒ
    void manageGoods(std::vector<Goods*> & allGoods);                     //������Ʒ
    void haveDiscount() ;                                                 //��ͬ����Ʒ���д���
};

