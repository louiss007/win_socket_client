#include<WinSock2.h>
#include<stdio.h>

#pragma comment(lib,"ws2_32.lib")

void main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested=MAKEWORD(1,1);
	err=WSAStartup(wVersionRequested,&wsaData);
	if(err!=0)
		return;
	if(LOBYTE(wsaData.wVersion)!=1||
		HIBYTE(wsaData.wVersion)!=1)
	{
		WSACleanup();
		return ;
	}
	SOCKET sockClient=socket(AF_INET,SOCK_STREAM,0);	//将其第三个参数设为0，让其自动选择协议
	SOCKADDR_IN addrSrv;	//设定服务器端的IP和端口
	addrSrv.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");	//本地回路地址
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(6000);
	connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));	//与服务器建立连接
	char recvBuf[100];
	recv(sockClient,recvBuf,100,0);
	printf("%s\n",recvBuf);
	send(sockClient,"This is zhengfu",strlen("This is zhengfu")+1,0);
	closesocket(sockClient);
	WSACleanup();
}