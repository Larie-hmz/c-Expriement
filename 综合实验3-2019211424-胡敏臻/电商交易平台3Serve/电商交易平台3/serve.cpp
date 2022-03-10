//#include "pch.h"
#include<iostream>
#include "serve.h"
#pragma comment(lib,"ws2_32.lib")


//��ʼ��
void serve::initialization() {
	//��ʼ���׽��ֿ�
	WORD w_req = MAKEWORD(2, 2);//�汾��
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		std::cout << "��ʼ���׽��ֿ�ʧ�ܣ�" << std::endl;
	}
	else {
		std::cout << "��ʼ���׽��ֿ�ɹ���" << std::endl;
	}
	//���汾��
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		std::cout << "�׽��ֿ�汾�Ų�����" << std::endl;
		WSACleanup();
	}
	else {
		std::cout << "�׽��ֿ�汾��ȷ��" << std::endl;
	}
	//������˵�ַ��Ϣ

}

//��������
void serve::setup() {
	//���峤�ȱ���
	int len = 0;
	initialization();
	//���������Ϣ
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(8080);
	//�����׽���
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (bind(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		std::cout << "�׽��ְ�ʧ�ܣ�" << std::endl;
		WSACleanup();
	}
	else {
		std::cout << "�׽��ְ󶨳ɹ���" << std::endl;
	}
	//�����׽���Ϊ����״̬
	if (listen(s_server, SOMAXCONN) < 0) {
		std::cout << "���ü���״̬ʧ�ܣ�" << std::endl;
		WSACleanup();
	}
	else {
		std::cout << "���ü���״̬�ɹ���" << std::endl;
	}
	std::cout << "��������ڼ������ӣ����Ժ�...." << std::endl;
	//������������
	len = sizeof(SOCKADDR);
	s_accept = accept(s_server, (SOCKADDR*)&accept_addr, &len);
	if (s_accept == SOCKET_ERROR) {
		std::cout << "����ʧ�ܣ�" << std::endl;
		WSACleanup();
		return;
	}
	std::cout << "���ӽ�����׼����������" << std::endl;

	return;
}

//�ر�����
void serve::close() {
	//�ر��׽���
	closesocket(s_server);
	closesocket(s_accept);
	//�ͷ�DLL��Դ
	WSACleanup();
	return;
}

//void serve::sendBuffer(const std::string& s) {
//	send_buffer += s;
//}

//�Զ��巢��
void serve::mySend() {
	int send_len = send(s_accept, send_buffer.str().c_str(), send_buffer.str().length()+1, 0);
	if (send_len < 0) {
		std::cout << "����ʧ�ܣ�" << std::endl;
		ifsend = 0;
	}
	send_buffer.str("");
}

//�Զ�����ȡ
std::stringstream& serve::myReceive() {
	memset(tempdata, 0, sizeof(tempdata));
	int recv_len = recv(s_accept, tempdata, sizeof(tempdata), 0);
	if (recv_len < 0) {
		std::cout << "����ʧ�ܣ�" << std::endl;
		ifreceive = 0;
	}
	else {
		receive_buffer.str(tempdata);
		std::cout << "�ͻ�����Ϣ:\n" << receive_buffer.str();
	}
	return receive_buffer;
}

//�ж������Ƿ�Ϸ�����
bool serve::iflegal() {
	if (ifsend == 0 || ifreceive == 0) {
		return false;
		close();
	}
	return true;
}

//ȫ��
serve ser;