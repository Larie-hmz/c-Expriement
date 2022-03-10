#include "print.h"
#include<iostream>

//初始化时的程序选择
void print::printfi(){
	serp->in() << "***********************" << std::endl;
	serp->in() << "****用户注册请输入1****" << std::endl;
	serp->in() << "****用户登录请输入2****" << std::endl;
	serp->in() << "****商品展示请输入3****" << std::endl;
	serp->in() << "****商品筛选请输入4****" << std::endl;
	serp->in() << "****查看帮助请输入9****" << std::endl;
	serp->in() << "****程序退出请输入0****" << std::endl;
	serp->in() << "***********************" << std::endl;

}
//商家的程序选择
void print::printfm() {
	serp->in() << "***********************" << std::endl;
	serp->in() << "****修改密码请输入1****" << std::endl;
	serp->in() << "****余额管理请输入2****" << std::endl;
	serp->in() << "**商家商品展示请输入3**" << std::endl;
	serp->in() << "****商品筛选请输入4****" << std::endl;
	serp->in() << "****商品添加请输入5****" << std::endl;
	serp->in() << "****商品管理请输入6****" << std::endl;
	serp->in() << "****商品打折请输入7****" << std::endl;
	serp->in() << "**全部商品展示请输入8**" << std::endl;
	serp->in() << "****查看帮助请输入9****" << std::endl;
	serp->in() << "****账户退出请输入0****" << std::endl;
	serp->in() << "***********************" << std::endl;
}
//消费者的用户选择
void print::printfc() {
	serp->in() << "***********************" << std::endl;
	serp->in() << "****修改密码请输入1****" << std::endl;
	serp->in() << "****余额管理请输入2****" << std::endl;
	serp->in() << "****商品展示请输入3****" << std::endl;
	serp->in() << "****商品筛选请输入4****" << std::endl;
	serp->in() << "***购物车管理请输入5***" << std::endl;
	serp->in() << "****订单管理请输入6****" << std::endl;
	serp->in() << "****查看帮助请输入9****" << std::endl;
	serp->in() << "****账户退出请输入0****" << std::endl;
	serp->in() << "***********************" << std::endl;
}

//购物车的选择功能
void print::printfcart() {
	serp->in() << "***********************" << std::endl;
	serp->in() << "****添加商品请输入1****" << std::endl;
	serp->in() << "****删除商品请输入2****" << std::endl;
	serp->in() << "***修改购买量请输入3***" << std::endl;
	serp->in() << "***购物车查看请输入4***" << std::endl;
	serp->in() << "***********************" << std::endl;
}
//订单的选择功能
void print::printforder() {
	serp->in() << "***********************" << std::endl;
	serp->in() << "****生成订单请输入1****" << std::endl;
	serp->in() << "****取消订单请输入2****" << std::endl;
	serp->in() << "****支付订单请输入3****" << std::endl;
	serp->in() << "****查看订单请输入4****" << std::endl;
	serp->in() << "***********************" << std::endl;
}