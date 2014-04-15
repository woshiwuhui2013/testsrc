/*************************************************************************
	> File Name: ReverseFile.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Sun 13 Apr 2014 09:38:12 CST
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
using namespace std;
#define CHK(x) if(x<0) {cout <<__LINE__<<"FAIL"<<endl;}
#define CHK2(val, fun) if((val=fun)<0) {cout << __LINE__<< "fail"<<endl;}
#define BUF_SIZE 20
int Reversebuff(const char* inbuff, int len , char *obuff, int olen)
{
	if (len > olen)
	{
		return -1;
	}
	int j = 0;
	for (int i= len-1 ; i>=0 ; --i)
	{
		obuff[j++] = inbuff[i];
	}
	return 0;
}
int ReverseFile(const char* spath, const char * dpath)
{
	int rfd = 0;
	int wfd = 0;
	CHK2(rfd, open(spath, O_RDONLY));
	CHK2(wfd,open(dpath, O_CREAT|O_APPEND|O_WRONLY));
	struct stat filestat;
	bzero(&filestat, sizeof(filestat));
	CHK(fstat(rfd, &filestat));
	cout << filestat.st_size <<endl;
	int filesize = filestat.st_size;
	int len = 0;
	char buff[BUF_SIZE];
	char rbuff[BUF_SIZE];
	bzero(buff, BUF_SIZE+1);
	bzero(rbuff, BUF_SIZE);
    int seeklen = filesize;
	while(seeklen > BUF_SIZE)
	{
		seeklen -=BUF_SIZE;
		CHK(lseek(rfd,seeklen, SEEK_SET));
		CHK(read(rfd, buff, BUF_SIZE));
		Reversebuff(buff,BUF_SIZE,rbuff,BUF_SIZE);
		CHK(write(wfd,rbuff, BUF_SIZE));

	}
	bzero(buff, BUF_SIZE);
	CHK(lseek(rfd, 0, SEEK_SET));
	CHK(read(rfd,buff, seeklen));	
	Reversebuff(buff,BUF_SIZE,rbuff,BUF_SIZE);

	CHK(write(wfd, rbuff, BUF_SIZE));
	close(rfd);
	close(wfd);
	return 0;
}

int main(int argc , char *argv[])
{
	ReverseFile("pipe.cpp", "out.cpp");
	return 0;
}
