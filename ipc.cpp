/*************************************************************************
	> File Name: ipc.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Tue 25 Mar 2014 14:09:40 CST
 ************************************************************************/

#include<iostream>
#include<sys/ipc.h>
#include<unistd.h>
#include<string.h>
#include<sys/msg.h>
#include<sys/stat.h>
#include<sys/shm.h>
#include<sys/sem.h>
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
	key_t key = ftok("testfd",100);
	if (-1 == key)
	{
		return  -1;

	}

	int pid = fork();
	if(pid == 0)
	{
		int ret = execl("ipcchild", "ipcchild", (char*)0);
		if (-1 == ret)
		{
			cout << "errer execl" <<endl;
			return -1;
		}
	}
	else
	{
		cout << "parent here" <<endl;
	}
	// msg
	int msgid = msgget(key,0666);
	if (-1==msgid)
	{
		msgid = msgget(key,0666|IPC_CREAT|IPC_EXCL);
	}
	//share memory
	int shmid = shmget(key, 1024, 0666);
	if(shmid == -1)
	{
		shmid = shmget(key, 1024,0666|IPC_CREAT|IPC_EXCL);
	}
	//sem
	int semid = semget(key, 1, 0666);
	if (semid == -1)
	{
		semid = semget(key,1,0666|IPC_CREAT|IPC_EXCL);
	}

	void *p = shmat(shmid, 0,0);
	
	typedef struct mymesg
	{
		long mtype;
		char mtext[512];
	}TYPE;
	TYPE msg;
	msg.mtype =100;
	char buf[] = "this msg from parent xxxxxxxxxxxxxxxx";
	
	cout << " parent msgid:" <<msgid <<endl;
	strncpy(msg.mtext, buf, 512);
	msgsnd(msgid, &msg, sizeof(msg.mtype), IPC_NOWAIT);
        
	// communication with share memory
	sembuf stbuf;
	stbuf.sem_num = 1;
	

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
	char bufm[] = "this msg send from share momory";
	memcpy(p,bufm, sizeof(bufm));
	cout << (char*)p<<endl;

    if (semaphore_v(semid)==-1)
	{
		cout << "semaphore v error" <<endl;
		return -1;
	}
    return 0;
	

}
