#pragma once
#include<iostream>
class print
{
public:
	void printfi() const;
	void printfm() const;
	void printfc() const;
	template<class T>
	void input(T& x) const {
		std::cin >> x;
		//ȷ�������������ȷ�������\n��β�����ڶ�����ַ�
		while (std::cin.get() != '\n' || std::cin.fail()) {
			std::cout << "��������ȷ�����룺" << std::endl;
			std::cin.clear(); //��մ�����
			std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');//������������ַ�
			std::cin >> x;
		}
	}
};

