#include "print.h"
#include<iostream>

//初始化时的程序选择
void print::printfi() const{
	std::cout << "***********************" << std::endl;
	std::cout << "****用户注册请输入1****" << std::endl;
	std::cout << "****用户登录请输入2****" << std::endl;
	std::cout << "****商品展示请输入3****" << std::endl;
	std::cout << "****商品筛选请输入4****" << std::endl;
	std::cout << "****查看帮助请输入9****" << std::endl;
	std::cout << "****程序退出请输入0****" << std::endl;
	std::cout << "***********************" << std::endl;

}
//商家的程序选择
void print::printfm()const {
	std::cout << "***********************" << std::endl;
	std::cout << "****修改密码请输入1****" << std::endl;
	std::cout << "****余额管理请输入2****" << std::endl;
	std::cout << "**商家商品展示请输入3**" << std::endl;
	std::cout << "****商品筛选请输入4****" << std::endl;
	std::cout << "****商品添加请输入5****" << std::endl;
	std::cout << "****商品管理请输入6****" << std::endl;
	std::cout << "****商品打折请输入7****" << std::endl;
	std::cout << "**全部商品展示请输入8**" << std::endl;
	std::cout << "****查看帮助请输入9****" << std::endl;
	std::cout << "****账户退出请输入0****" << std::endl;
	std::cout << "***********************" << std::endl;
}
//消费者的用户选择
void print::printfc() const {
	std::cout << "***********************" << std::endl;
	std::cout << "****修改密码请输入1****" << std::endl;
	std::cout << "****余额管理请输入2****" << std::endl;
	std::cout << "****商品展示请输入3****" << std::endl;
	std::cout << "****商品筛选请输入4****" << std::endl;
	std::cout << "***购物车管理请输入5***" << std::endl;
	std::cout << "****订单管理请输入6****" << std::endl;
	std::cout << "****查看帮助请输入9****" << std::endl;
	std::cout << "****账户退出请输入0****" << std::endl;
	std::cout << "***********************" << std::endl;
}

//购物车的选择功能
void print::printfcart() const {
	std::cout << "***********************" << std::endl;
	std::cout << "****添加商品请输入1****" << std::endl;
	std::cout << "****删除商品请输入2****" << std::endl;
	std::cout << "***修改购买量请输入3***" << std::endl;
	std::cout << "***购物车查看请输入4***" << std::endl;
	std::cout << "***********************" << std::endl;
}
//订单的选择功能
void print::printforder() const {
	std::cout << "***********************" << std::endl;
	std::cout << "****生成订单请输入1****" << std::endl;
	std::cout << "****取消订单请输入2****" << std::endl;
	std::cout << "****支付订单请输入3****" << std::endl;
	std::cout << "****查看订单请输入4****" << std::endl;
	std::cout << "***********************" << std::endl;
}