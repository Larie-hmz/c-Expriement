//#include "pch.h"
#include<iostream>
#include "serve.h"
#pragma comment(lib,"ws2_32.lib")


//初始化
void serve::initialization() {
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
	//填充服务端地址信息

}

//建立连接
void serve::setup() {
	//定义长度变量
	int len = 0;
	initialization();
	//填充服务端信息
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(8080);
	//创建套接字
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (bind(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		std::cout << "套接字绑定失败！" << std::endl;
		WSACleanup();
	}
	else {
		std::cout << "套接字绑定成功！" << std::endl;
	}
	//设置套接字为监听状态
	if (listen(s_server, SOMAXCONN) < 0) {
		std::cout << "设置监听状态失败！" << std::endl;
		WSACleanup();
	}
	else {
		std::cout << "设置监听状态成功！" << std::endl;
	}
	std::cout << "服务端正在监听连接，请稍候...." << std::endl;
	//接受连接请求
	len = sizeof(SOCKADDR);
	s_accept = accept(s_server, (SOCKADDR*)&accept_addr, &len);
	if (s_accept == SOCKET_ERROR) {
		std::cout << "连接失败！" << std::endl;
		WSACleanup();
		return;
	}
	std::cout << "连接建立，准备接受数据" << std::endl;

	return;
}

//关闭连接
void serve::close() {
	//关闭套接字
	closesocket(s_server);
	closesocket(s_accept);
	//释放DLL资源
	WSACleanup();
	return;
}

//void serve::sendBuffer(const std::string& s) {
//	send_buffer += s;
//}

//自定义发送
void serve::mySend() {
	int send_len = send(s_accept, send_buffer.str().c_str(), send_buffer.str().length()+1, 0);
	if (send_len < 0) {
		std::cout << "发送失败！" << std::endl;
		ifsend = 0;
	}
	send_buffer.str("");
}

//自定义收取
std::stringstream& serve::myReceive() {
	memset(tempdata, 0, sizeof(tempdata));
	int recv_len = recv(s_accept, tempdata, sizeof(tempdata), 0);
	if (recv_len < 0) {
		std::cout << "接受失败！" << std::endl;
		ifreceive = 0;
	}
	else {
		receive_buffer.str(tempdata);
		std::cout << "客户端信息:\n" << receive_buffer.str();
	}
	return receive_buffer;
}

//判断连接是否合法建立
bool serve::iflegal() {
	if (ifsend == 0 || ifreceive == 0) {
		return false;
		close();
	}
	return true;
}

//全局
serve ser;