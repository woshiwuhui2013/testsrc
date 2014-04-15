/*************************************************************************
	> File Name: pipe.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Tue 25 Mar 2014 11:40:14 CST
 ************************************************************************/

#include<iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int main()
{
	int field[2] = {0};
	if(-1 == pipe(field))
	{
	
		cout << "pipe err" <<endl;
		exit(-1);
	}
    
	int pid = fork();
	if(pid < 0)
	{
		cout << "fork err" <<endl;
		exit(-1);
	}
	if (pid == 0)
	{
		close(field[1]);

		sleep(2);
		char buf[100];
		read(field[0], buf, 100);
		cout << "child read: " << buf <<endl;
	}
	else
	{
		
		close(field[0]);
		char buf[] = "here we write some word" ;
		ssize_t len = write(field[1], buf, sizeof(buf));
		cout << "parent write" <<endl;
	}
	return 0;
}
