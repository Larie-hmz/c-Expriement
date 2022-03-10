#pragma once
#include<iostream>
#include"serve.h"
#include<limits>

class print
{
	serve* serp;
public:
	print(serve* ser) {
		serp = ser;
	}
	void printfi();
	void printfm();
	void printfc();
	void printfcart();
	void printforder();
	template<class T>
	void input(T& x) const {
		serp->myReceive() >> x;
		//确保读入的类型正确且最后以\n收尾不存在多余的字符
		while (serp->out().get() != '\n' || serp->out().fail()) {
			//先判断此时连接是否建立
			if (!ser.iflegal()) {
				ser.close();
				throw std::runtime_error("网络断开");
				return ;
			}
			serp->in() << "请输入正确的输入：" << std::endl;
			ser.mySend();
			serp->out().clear(); //清空错误码
			serp->out().ignore(std::numeric_limits< std::streamsize >::max(), '\n');//忽略最后多余的字符
			serp->myReceive() >> x;
		}
	}
};

