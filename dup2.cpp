/*************************************************************************
	> File Name: dup2.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Tue 25 Mar 2014 05:41:44 CST
 ************************************************************************/
#include<iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;
int dup_cpy(int fd, int newfd)
{
	int getfd = 0;
	getfd == dup(fd);
	if (getfd == -1)
	{
		cout << "error" <<endl;
		return -1;
	}
	else
	{
		close(getfd);
	}

	if (fd  == newfd)
	{
		cout << "same fd" <<endl;
		return fd;
	}

	close(newfd);
	int *ptmpfd= new int[newfd] ;
	memset(ptmpfd,  0, 100);
	while(1)
	{
		getfd = dup(fd);
		if (getfd == -1)
		{
			cout << "error"<<endl;
			exit(-1);
		}
             
		if(getfd == newfd)
		{
			cout << "get fd now" <<endl;
			break;
		}
		else
		{
			ptmpfd[getfd] =  1;
		}
	}
	for (int i =0 ; i < newfd; ++i)
	{
		if (ptmpfd[i] == 1)
		{
			close(i);
			cout << "close tmp" << i <<endl;
		}
	}
	return getfd;
}
int main()
{
	int fd = open("testfd",O_CREAT| O_WRONLY);

	if (fd == -1)
	{
		cout << "open err"<<endl;
		exit(-1);
	}
	int newfd = dup_cpy(fd, 100);
	cout << "get newfd is :"<<newfd<<endl;

	char buf[] = "hello   world";
	ssize_t ret = write(newfd, buf, sizeof(buf));
	if (ret == -1)
	{
		cout << "write err" << endl;
	}
	else
	{
		cout << "have write :"<< ret << "bype"<<endl;
	}
	exit(0);
}


