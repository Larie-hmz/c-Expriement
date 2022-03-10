#pragma once
#include<sstream>
#include<winsock2.h>
#undef max 
#undef min



//enum class myendl { endl };
class serve
{
	//定义服务端套接字，接受请求套接字
	SOCKET s_server;
	SOCKET s_accept;
	//服务端地址客户端地址
	SOCKADDR_IN server_addr;
	SOCKADDR_IN accept_addr;
	std::stringstream send_buffer;
	std::stringstream receive_buffer;
	//临时缓存
	char tempdata[300];
	int ifsend = 1;
	int ifreceive = 1;
public:
	void initialization();//初始化
	void setup();//建立连接
	//void sendBuffer(const std::string & s);
	void close();//关闭连接
	void mySend();//自定义发送
	bool iflegal();//判断连接是否合法建立

	std::stringstream& myReceive();//自定义收取
	std::stringstream& out() { return receive_buffer; }//输出流
	std::stringstream& in() { return send_buffer; }//输入流
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