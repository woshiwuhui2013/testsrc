/*************************************************************************
	> File Name: endian.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Thu 27 Mar 2014 15:19:48 CST
 ************************************************************************/

#include<iostream>
#include<arpa/inet.h>
using namespace std;
union uType
{
	int iNum;
	char ch[4];
};
int main()
{
	uType tmp;
	tmp.iNum = 0x11223344;
	cout <<hex<<(int)tmp.ch[0] <<(int)tmp.ch[1] << (int)tmp.ch[2] << (int)tmp.ch[3] <<endl;
	int netvalue = htonl(tmp.iNum);
	cout << hex << netvalue<<endl;
	return 0;
}
