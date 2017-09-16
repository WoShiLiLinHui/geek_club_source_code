// ConsoleApplication2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int main() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = AF_INET;

	//----get ip address----
	char szHost[256], filepath[256];
	memset(szHost, 0, 256);
	memset(filepath, 0, 256);
	strcpy(szHost, "img1.cache.netease.com");
	strcpy(filepath, "/catchpic/A/AB/AB6F8545A8A76BCD0F7E7E8883674D3C.png");
	hostent *pHE = gethostbyname(szHost);
	memcpy(&sockAddr.sin_addr.s_addr, pHE->h_addr_list[0], pHE->h_length);

	//----connect and send request----
	sockAddr.sin_port = htons(80);
	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	char requeststr[512];
	memset(requeststr, 0, 512);
	strcpy(requeststr, "Get ");
	strcat(requeststr, filepath);
	strcat(requeststr, " HTTP/1.1\r\nHost:");
	strcat(requeststr, szHost); //url
	strcat(requeststr, "\r\nConnection:Close\r\n\r\n");
	send(sock, requeststr, sizeof(requeststr), 0);

	//----write and save file on receiving----
	FILE * file1;
	char fileName[] = "AB6F8545A8A76BCD0F7E7E8883674D3C.png";
	file1=fopen(fileName, "wb");
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	int n = 0;
	n = recv(sock, buf, sizeof(buf) - sizeof(char), 0);
	char* cpos = strstr(buf, "\r\n\r\n");
	//printf("%s\n", buf);
	fwrite(cpos + strlen("\r\n\r\n"), n - (cpos - buf) - strlen("\r\n\r\n"), 1, file1);
	while ((n = recv(sock, buf, sizeof(buf) - sizeof(char), 0)) > 0) {
		fwrite(&buf[0], n, 1, file1);
	// 	printf("%d\t", n);
	}
	fclose(file1);

	//----close----
	closesocket(sock);
	WSACleanup();
	system("pause");
	return 0;
}
