#pragma once
#include<sstream>
#include<winsock2.h>
#undef max 
#undef min



//enum class myendl { endl };
class serve
{
	//���������׽��֣����������׽���
	SOCKET s_server;
	SOCKET s_accept;
	//����˵�ַ�ͻ��˵�ַ
	SOCKADDR_IN server_addr;
	SOCKADDR_IN accept_addr;
	std::stringstream send_buffer;
	std::stringstream receive_buffer;
	//��ʱ����
	char tempdata[300];
	int ifsend = 1;
	int ifreceive = 1;
public:
	void initialization();//��ʼ��
	void setup();//��������
	//void sendBuffer(const std::string & s);
	void close();//�ر�����
	void mySend();//�Զ��巢��
	bool iflegal();//�ж������Ƿ�Ϸ�����

	std::stringstream& myReceive();//�Զ�����ȡ
	std::stringstream& out() { return receive_buffer; }//�����
	std::stringstream& in() { return send_buffer; }//������
	/*template<class T>
	serve& operator <<(T& t) {
		send_buffer << t;
		return *this;
	}
	std::stringstream & operator <<(T & t) {
		send_buffer << t;
		return send_buffer;
	}
	serve& operator <<(myendl) {
		send_buffer << std::endl;
		return *this;
	}*/
};

extern serve ser;