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
		//ȷ�������������ȷ�������\n��β�����ڶ�����ַ�
		while (serp->out().get() != '\n' || serp->out().fail()) {
			//���жϴ�ʱ�����Ƿ���
			if (!ser.iflegal()) {
				ser.close();
				throw std::runtime_error("����Ͽ�");
				return ;
			}
			serp->in() << "��������ȷ�����룺" << std::endl;
			ser.mySend();
			serp->out().clear(); //��մ�����
			serp->out().ignore(std::numeric_limits< std::streamsize >::max(), '\n');//������������ַ�
			serp->myReceive() >> x;
		}
	}
};

