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
	std::cout << "****查看帮助请输入9****" << std::endl;
	std::cout << "****账户退出请输入0****" << std::endl;
	std::cout << "***********************" << std::endl;
}

//template<class T>
//void print::input(T& x) const {
//	std::cin >> x;
//	//确保读入的类型正确且最后以\n收尾不存在多余的字符
//	while (std::cin.get() != '\n' || std::cin.fail()) {
//		std::cout << "请输入正确的输入：" << std::endl;
//		std::cin.clear(); //清空错误码
//		std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');//忽略最后多余的字符
//		std::cin >> x;
//	}
//}