/*************************************************************************
	> File Name: substr.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Sun 13 Apr 2014 11:47:49 CST
 ************************************************************************/

#include<iostream>
#include<string.h>
#include<string>
#include<vector>
using namespace std;

#define CHK(x) if(x<0) {cout <<__LINE__<<"FAIL"<<endl;}
#define CHK2(val, fun) if((val=fun)<0) {cout << __LINE__<< "fail"<<endl;}
int getNext(const char *p, int *next, int len)
{
    if (p == NULL || next == NULL)
    {
        return -1;
    }

    int j   = 0;
    int k   = -1;
    next[0] = -1;
    while (j < len -1 )
    {
        if (k== -1 || p[k] == p[j]) // kָʾǰ׺���һ���뵱ǰ����ֵ��ȵ�λ��
        {
            ++j; // ��ǰҪд��next��λ��
            ++k; // Ӧ����ģʽ����λ��
            next[j] = k; // 

        }
        // abab
        else   // k ָʾǰ���ִ����ڲ���������ִ����λ��
        {
            k = next[k];  
        }
    }
    return 0;
}

char* mystrstr(const char *dststr, const char *substr)
{
    int dstlen = strlen(dststr);
    int sublen = strlen(substr);

    if (dststr == NULL)
    {
        return NULL;
    }

    if (substr == NULL)
    {
        return dststr;
    }

    char *next = new char[sublen+1];
    getNext(substr, next, sublen);
    

    //int tmp = i;
    while(j<=sublen && i <= dstlen)
    {
        if (dststr[i] == substr[j])
        {
            ++i;
            ++j;
        }
        else
        {
            j = next[j];
        }
    }

    if (j > sublen)
    {
        // ����ҵ�
        return dststr+i-sublen;        
    }

    return NULL;    
}


int GetSubStr(char *p , int b, int e , char *pRet, int &sublen)
{
	bzero(pRet, 20);
	int len = e-b+1;
	if (len > sublen)
	{
		return -1;
	}
	sublen = len;
	memcpy(pRet, p+b, len);
	return 0;
}
int substr(char* pstr,  char *buff)
{
	vector<string> vecsub;
	char *sub = new char[20];
	int i =0;
	int j =0;
	char *p = pstr;
	int sublen = 20;
	while(p[i]!='\0')
	{
		j = i;
		sublen =20;
		GetSubStr(p, i, j, sub, sublen);
		while(strstr(p+j+1, sub))
		{
			++j;
			sublen =20;
		    GetSubStr(p, i, j, sub, sublen);
		}
		sub[sublen-1] = '\0'; //del the last char
		vecsub.push_back(sub);
		bzero(sub,20);
		++i;
	}

    vector<string>::iterator it ;
	for(it= vecsub.begin(); it != vecsub.end(); ++it)
	{
		cout << *it <<endl;
	}
	return 0;
}
int main()
{
	//char buff[20];
	//bzero(buff, 20);
	char p[] = "abcbccbcabdabcdabcdcfabcd";
	//CHK(substr(p, buff));
	char *pos = mystrstr(p, "cbca");
	cout << pos <<endl;
	return 0;
}


