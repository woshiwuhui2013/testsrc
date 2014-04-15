/*************************************************************************
	> File Name: ipc.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Tue 25 Mar 2014 14:09:40 CST
 ************************************************************************/

#include<iostream>
#include<sys/ipc.h>

#include<sys/msg.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<string.h>
using namespace std;
union semun
{
	int val;
	semid_ds *buf;
	unsigned short *array;
};
int set_semvalue(int semid)
{
	semun sem_union;
	sem_union.val =1;
	if (semctl(semid, 0 ,SETVAL, sem_union)==-1)
	{
		return -1;
	}
	return 0;
}
void del_semvalue(int semid)
{
	semun sem_union;
	if (semctl(semid, 0, IPC_RMID, sem_union)==-1)
	{

	}
}

int semaphore_p(int semid)
{
	sembuf sem_b;
	sem_b.sem_num =0;
	sem_b.sem_op =-1;
	sem_b.sem_flg =SEM_UNDO;
	if (semop(semid, &sem_b, 1)==-1)
	{
		return -1;
	}
	return 0;
	
}
int semaphore_v(int semid)
{
	sembuf sem_b;
	sem_b.sem_num =0;
	sem_b.sem_op =1;
	sem_b.sem_flg = SEM_UNDO;
	if (semop(semid, &sem_b, 1)== -1)
	{
		return -1;
	}
	return 0;
}
int main()
{
	cout << "child  here" <<endl;
	key_t key = ftok("testfd", 100);

	if(-1 == key)
	{
		cout <<"ftok error" <<endl;
		return -1;
	}
	sleep(2);
	int msgid  =  msgget(key, 0666);
	if(msgid == -1)
	{
		msgid  =  msgget(key, 0666|IPC_CREAT);
	}
	//share memory
	int shmid = shmget(key, 0, 0666);
	if (shmid == -1)
	{
		shmid = shmget(key,0, 0666|IPC_CREAT|IPC_EXCL);
	}
	int semid = semget(key, 1, 0666|IPC_CREAT);
	if (semid == -1)
	{
		cout << "sem get error"<<endl;
		return -1;
	}
	typedef struct mymesg
	{ 
		long mtype;
		char mtext[512];
	}TYPE;
	TYPE msg;

	// receive msg
	memset(msg.mtext, 0 , 512);
	cout << "child msgid:" <<msgid <<endl;
	ssize_t len = msgrcv(msgid, &msg,512, 0, MSG_NOERROR);
	msg.mtext[511]='\0';
	cout  <<"len:"<< len <<endl;
	cout << "child:" << msg.mtext <<endl;

	//share memory
	if (set_semvalue(semid)==-1)
	{
		cout << "set value error" <<endl;
		return -1;
	}
    if (semaphore_p(semid)==-1)
	{
		cout << "semaphore error" <<endl;
		return -1;
	}
	void *p = shmat(shmid, 0,0);
	if (p == (void*)-1)
	{
		cout << "child shmat error" <<endl;
		return -1;
	}
	cout << "child after shmat" <<endl;
	//cout <<"child:"<< (char*)p<<endl;
    if (semaphore_v(semid)==-1)
	{
		cout << "semaphorev error" <<endl;
		return -1;
	}
    return 0;
}
