//#include "pch.h"
#include<iostream>
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")
//void initialization();
int main() {
	//定义长度变量
	int send_len = 0;
	int recv_len = 0;
	//定义发送缓冲区和接受缓冲区
	//char send_buf[1000];
	char recv_buf[1000];
	std::string send_buffer;
	//std::string recv_buffer;
	//定义服务端套接字，接受请求套接字
	SOCKET s_server;
	//服务端地址客户端地址
	SOCKADDR_IN server_addr;
	//初始化套接字库
	WORD w_req = MAKEWORD(2, 2);//版本号
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		std::cout << "初始化套接字库失败！" << std::endl;
	}
	else {
		std::cout << "初始化套接字库成功！" << std::endl;
	}
	//检测版本号
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		std::cout << "套接字库版本号不符！" << std::endl;
		WSACleanup();
	}
	else {
		std::cout << "套接字库版本正确！" << std::endl;
	}
	//填充服务端信息
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(8080);
	//创建套接字
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		std::cout << "服务器连接失败！" << std::endl;
		WSACleanup();
	}
	else {
		std::cout << "服务器连接成功！" << std::endl;
	}

	//发送,接收数据
	while (1) {
		
		recv_len = recv(s_server, recv_buf, 1000, 0);
		if (recv_len < 0) {
			std::cout << "接受失败！" << std::endl;
			break;
		}
		else {
			//std::cout << "服务端信息:\n" << recv_buf << std::endl;
			std::cout << recv_buf;
		}
		if (std::string(recv_buf) == "退出程序成功\n") {
			break;
		}

		std::cout << "请输入发送信息:";
		std::cin >> send_buffer;
		//每次输入后都要加上一个\n表示字符串的结束
		send_buffer += "\n";
		send_len = send(s_server, send_buffer.c_str(), sizeof(send_buffer), 0);
		if (send_len < 0) {
			std::cout << "发送失败！" << std::endl;
			break;
		}
	}
	//关闭套接字
	closesocket(s_server);
	//释放DLL资源
	WSACleanup();
	return 0;
}
//void initialization() {
//	//初始化套接字库
//	WORD w_req = MAKEWORD(2, 2);//版本号
//	WSADATA wsadata;
//	int err;
//	err = WSAStartup(w_req, &wsadata);
//	if (err != 0) {
//		std::cout << "初始化套接字库失败！" << std::endl;
//	}
//	else {
//		std::cout << "初始化套接字库成功！" << std::endl;
//	}
//	//检测版本号
//	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
//		std::cout << "套接字库版本号不符！" << std::endl;
//		WSACleanup();
//	}
//	else {
//		std::cout << "套接字库版本正确！" << std::endl;
//	}
//	//填充服务端地址信息
//
//}