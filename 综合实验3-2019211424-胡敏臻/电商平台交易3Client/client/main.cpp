//#include "pch.h"
#include<iostream>
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")
//void initialization();
int main() {
	//���峤�ȱ���
	int send_len = 0;
	int recv_len = 0;
	//���巢�ͻ������ͽ��ܻ�����
	//char send_buf[1000];
	char recv_buf[1000];
	std::string send_buffer;
	//std::string recv_buffer;
	//���������׽��֣����������׽���
	SOCKET s_server;
	//����˵�ַ�ͻ��˵�ַ
	SOCKADDR_IN server_addr;
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
	//���������Ϣ
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(8080);
	//�����׽���
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		std::cout << "����������ʧ�ܣ�" << std::endl;
		WSACleanup();
	}
	else {
		std::cout << "���������ӳɹ���" << std::endl;
	}

	//����,��������
	while (1) {
		
		recv_len = recv(s_server, recv_buf, 1000, 0);
		if (recv_len < 0) {
			std::cout << "����ʧ�ܣ�" << std::endl;
			break;
		}
		else {
			//std::cout << "�������Ϣ:\n" << recv_buf << std::endl;
			std::cout << recv_buf;
		}
		if (std::string(recv_buf) == "�˳�����ɹ�\n") {
			break;
		}

		std::cout << "�����뷢����Ϣ:";
		std::cin >> send_buffer;
		//ÿ�������Ҫ����һ��\n��ʾ�ַ����Ľ���
		send_buffer += "\n";
		send_len = send(s_server, send_buffer.c_str(), sizeof(send_buffer), 0);
		if (send_len < 0) {
			std::cout << "����ʧ�ܣ�" << std::endl;
			break;
		}
	}
	//�ر��׽���
	closesocket(s_server);
	//�ͷ�DLL��Դ
	WSACleanup();
	return 0;
}
//void initialization() {
//	//��ʼ���׽��ֿ�
//	WORD w_req = MAKEWORD(2, 2);//�汾��
//	WSADATA wsadata;
//	int err;
//	err = WSAStartup(w_req, &wsadata);
//	if (err != 0) {
//		std::cout << "��ʼ���׽��ֿ�ʧ�ܣ�" << std::endl;
//	}
//	else {
//		std::cout << "��ʼ���׽��ֿ�ɹ���" << std::endl;
//	}
//	//���汾��
//	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
//		std::cout << "�׽��ֿ�汾�Ų�����" << std::endl;
//		WSACleanup();
//	}
//	else {
//		std::cout << "�׽��ֿ�汾��ȷ��" << std::endl;
//	}
//	//������˵�ַ��Ϣ
//
//}