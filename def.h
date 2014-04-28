/*************************************************************************
	> File Name: def.h
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Thu 17 Apr 2014 16:19:05 CST
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

using namespace std;
#define CHK(x) if(!x) { printf("%d:fail",__LINE__); exit(-1);}
#define CHK1(x) if(x<0) { printf("%d:fail",__LINE__); exit(-1);}
#define CHK2(x,ret) if((x=ret)<0) { printf("%d:fail",__LINE__); exit(-1);}


