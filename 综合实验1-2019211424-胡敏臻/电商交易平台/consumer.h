#pragma once
#include "account.h"
class Consumer :
    public Account
{
public:
    Consumer(const int number_, const std::string& id_="", const std::string& passwd_="", const double& balance_=0, const User& userType_=CONSUMER);
    Consumer(const Consumer& acc);
    ~Consumer();
public:
    virtual User getUserType() override;
 
};

