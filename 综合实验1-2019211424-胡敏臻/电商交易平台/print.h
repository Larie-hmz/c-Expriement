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
		//确保读入的类型正确且最后以\n收尾不存在多余的字符
		while (std::cin.get() != '\n' || std::cin.fail()) {
			std::cout << "请输入正确的输入：" << std::endl;
			std::cin.clear(); //清空错误码
			std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');//忽略最后多余的字符
			std::cin >> x;
		}
	}
};

