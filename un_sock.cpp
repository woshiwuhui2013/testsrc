/*************************************************************************
	> File Name: un_sock.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Thu 03 Apr 2014 11:27:23 CST
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<strings.h>
#include<sys/un.h>
#include<sys/socket.h>
#include<stdlib.h>

using namespace std;
#define CHK(val) if(val<0) {perror("val:"); exit(-1);}

#define CHK2(res, val) if((res=val)<0) {perror("val:"); exit(-1);}
#define Conn(x,y) x##y
#define ToString(x)  #x
int main(int argc, char* argv[])
{
	int sock ;
	CHK2(sock, socket(AF_LOCAL, SOCK_STREAM, 0));
	sockaddr_un addr;
	bzero(&addr, sizeof(addr));
	addr.sun_family = AF_LOCAL;
	unlink(argv[1]);

	strncpy(addr.sun_path, argv[1], sizeof(addr.sun_path)-1);
	CHK(bind(sock, (sockaddr*)&addr, sizeof(addr)));
	
	sockaddr_un addr2;
	socklen_t len = sizeof(addr2);
	getsockname(sock, (sockaddr*)&addr2, &len);
	cout << addr2.sun_family << addr2.sun_path<<endl;

	int val = 111234;
	char a[]=ToString(val);
	cout << a<<endl;
	return 0;

}
