#include "print.h"
#include<iostream>

//��ʼ��ʱ�ĳ���ѡ��
void print::printfi() const{
	std::cout << "***********************" << std::endl;
	std::cout << "****�û�ע��������1****" << std::endl;
	std::cout << "****�û���¼������2****" << std::endl;
	std::cout << "****��Ʒչʾ������3****" << std::endl;
	std::cout << "****��Ʒɸѡ������4****" << std::endl;
	std::cout << "****�鿴����������9****" << std::endl;
	std::cout << "****�����˳�������0****" << std::endl;
	std::cout << "***********************" << std::endl;

}
//�̼ҵĳ���ѡ��
void print::printfm()const {
	std::cout << "***********************" << std::endl;
	std::cout << "****�޸�����������1****" << std::endl;
	std::cout << "****������������2****" << std::endl;
	std::cout << "**�̼���Ʒչʾ������3**" << std::endl;
	std::cout << "****��Ʒɸѡ������4****" << std::endl;
	std::cout << "****��Ʒ���������5****" << std::endl;
	std::cout << "****��Ʒ����������6****" << std::endl;
	std::cout << "****��Ʒ����������7****" << std::endl;
	std::cout << "**ȫ����Ʒչʾ������8**" << std::endl;
	std::cout << "****�鿴����������9****" << std::endl;
	std::cout << "****�˻��˳�������0****" << std::endl;
	std::cout << "***********************" << std::endl;
}
//�����ߵ��û�ѡ��
void print::printfc() const {
	std::cout << "***********************" << std::endl;
	std::cout << "****�޸�����������1****" << std::endl;
	std::cout << "****������������2****" << std::endl;
	std::cout << "****��Ʒչʾ������3****" << std::endl;
	std::cout << "****��Ʒɸѡ������4****" << std::endl;
	std::cout << "****�鿴����������9****" << std::endl;
	std::cout << "****�˻��˳�������0****" << std::endl;
	std::cout << "***********************" << std::endl;
}

//template<class T>
//void print::input(T& x) const {
//	std::cin >> x;
//	//ȷ�������������ȷ�������\n��β�����ڶ�����ַ�
//	while (std::cin.get() != '\n' || std::cin.fail()) {
//		std::cout << "��������ȷ�����룺" << std::endl;
//		std::cin.clear(); //��մ�����
//		std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');//������������ַ�
//		std::cin >> x;
//	}
//}