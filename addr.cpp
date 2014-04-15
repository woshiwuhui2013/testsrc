/*************************************************************************
	> File Name: addr.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Thu 27 Mar 2014 15:45:10 CST
 ************************************************************************/

#include<iostream>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>
using namespace std;
int   main()
{
	hostent *p = gethostbyname("wuhui");
	if (p == NULL)
	{
		cout << "get host faile" <<endl;
		return 0;
	}
	cout << p->h_name <<endl;
	cout << "h_aliase" <<endl;
	for(char **ph = p->h_aliases; *ph != NULL; ph++)
	{
		cout << *ph <<endl;
	}
	cout << "h_addr_list:"<<endl;
	for (char **pa= p->h_addr_list; *pa!= NULL; pa++)
	{
		cout << *pa<<endl;
	}

	cout <<"/////////////////////////////" <<endl;
	sethostent(1);

	hostent *phost = NULL;
	while((phost = gethostent() )!= NULL)
	{
		cout << "begin" <<endl;
		cout << phost->h_name <<endl;
		for(char**p = phost->h_aliases; *p!= NULL; ++p)
		{
			cout << *p <<endl;
		}

		for(char**p = phost->h_addr_list; *p != NULL ; ++p)
		{	
			in_addr *paddr =(in_addr*) (*p);
			cout << inet_ntoa(*paddr)<<endl;
		}	
		cout << "end"<<endl;

	}
	endhostent();


	
	return 0;
}

