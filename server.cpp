/*************************************************************************
	> File Name: server.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Wed 02 Apr 2014 11:23:17 CST
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<list>
#include<strings.h>

using namespace std;
#define CHK(val) if(val <0) {perror("val");exit(-1);}
#define CHK2(res, eval) if((res=eval)<0) {perror("eval"); exit(-1);}

#define SERVER_HOST;
#define SERVER_PORT 50000
#define EPOLL_SIZE 10000
#define EPOLL_WAIT_TIME -1
#define MSG_SIZE 1024 
#define MSG_WELCOME "welcome to sechat you id is:client #%d"

int setnonblock(int sock)
{
	CHK(fcntl(sock, F_SETFL, fcntl(sock, F_GETFD,0)|O_NONBLOCK));
	return;
}

list<int> clisocklist;
int main(int argc, char* argv[])
{
	int listener;
	CHK2(listener, socket(AF_INET, SOCK_STREAM, 0));
	setnonblock(listener);

	sockaddr_in addr_ser;
	addr_ser.sin_family= AF_INET;
	addr_ser.sin_port =htons((in_port_t)SERVER_PORT);
	CHK(inet_pton(AF_INET, SERVER_HOST, &addr_ser.sin_addr.s_addr)));
	socklen_t addrlen = sizeof(addr_ser);
	CHK(bind(listener, (sockaddr*)&addr_ser, addrlen));
	CHK(listen(listener, 10));
	
	int epfd ;
	CHK2(epfd, epoll_creat(EPOLL_SIZE));
	
	epoll_event ev;
	epoll_event events[EPOLL_SIZE];
	ev.events = EPOOLLIN|EPOLLET;
	ev.data.fd = listener;
	CHK(epoll_ctl(epfd, EPOLL_CTL_ADD, listener, &ev));
    
	int epoll_event_count=0;
	clock_t tStart;
	sockaddr_in peeraddr;
	socklen_t peerlen;

	char message[MSG_SIZE];
	int res;
	while(1)
	{
		// here have some defect it should be check the errno type .not exit in all time
		CHK2(epoll_event_count, epoll_wait(epfd, events, EPOLL_SIZE, EPOLL_WAIT_TIME));
        for(int i =0; i < epoll_event_count; ++i)
		{
			if(events[i].fd == listener)
			{
				CHK2( clisock, accept(listener, &peeraddr, peerlen));
				setnonblock(clisock);
				ev.data.fd = clisock;
	            CHK(epoll_ctl(epfd, EPOLL_CTL_ADD, clisock, &ev));
				clisocklist.push_back(clisock);
				bzero(message, MSG_SIZE);
				sprintf(message, STR_WELCOME, clisock);
				CHK2(res, send(clisock, message, MSG_SIZE, 0));

			}
			else
			{
				CHK2(res, handlemsg(events[i].fd));
			}
		}
		printf(statistics:%d events handled at: %.2f second(s)\n", epoll_events_count, (double)(clock()-tStart)/CLOCKS_PER_SEC);
	}

	close(listener);
	close(epfd);
}
