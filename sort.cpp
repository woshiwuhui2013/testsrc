/*************************************************************************
	> File Name: sort.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Wed 16 Apr 2014 14:04:49 CST
 ************************************************************************/

#include<iostream>
using namespace std;

typedef struct _ARRAY
{   _ARRAY(int len)
	{
		pbuf = new int[len];
		length = len;
	}
	int *pbuf;
	int length;

}ARRAY;

void swap(ARRAY *p, int i, int j)
{
	int tmp = p->pbuf[i];
	p->pbuf[i] = p->pbuf[j];
	p->pbuf[j] = tmp;

}
void prtArray(ARRAY *p)
{
	for(int i = 0 ; i < p->length; ++i)
	{
		cout << p->pbuf[i] <<endl;
	}
}

void bubblesort1(ARRAY *p)
{
	for (int i = 0; i < p->length; ++i)
	{
		for(int j = i+1; j < p->length; ++j)
		{
			if (p->pbuf[i]>p->pbuf[j])
			swap(p, i, j);
		}
	}
}
void bubblesort2(ARRAY *p)
{
	for (int i = 0; i < p->length; ++i)
	{
		for(int j=p->length-1; j>i;--j)
		{
			if(p->pbuf[j]<p->pbuf[j-1])
			{
				swap(p,j,j-1);
			}
		}
	}
}
void selectsort(ARRAY *p)
{
	int min = 0;
	for (int i = 0 ; i < p-> length -1; ++i)
	{
		min = i;
		for (int j = i+1; j < p->length-1; ++j)
		{
			if (p->pbuf[min] > p->pbuf[j])
			{
				min = j;
			}
		}
		swap(p, i, min);
	}
}
void insertsort(ARRAY *p)
{
	int tmp = 0;
	for (int i = 1; i < p->length; ++ i)
	{
		if (p->pbuf[i] < p->pbuf[i-1])
		{
			tmp = p->pbuf[i];
			int j = 0; // j mean the sort list
			for(j =i-1; j >=0; --j)
			{
				if (p->pbuf[j] > tmp)
				{	
					p->pbuf[j+1] = p->pbuf[j];
				}	
				else
				{
					break;
				}
			}
			p->pbuf[++j] = tmp;	
		}
	}
}
// d is interval 
void shellinsert(ARRAY *p , int d)
{
	for (int i = d ; i < p->length; ++i)
	{
		int j = i-d;
		int tmp = p->pbuf[i];
		while (j >=0 && p->pbuf[j] > tmp)
		{
			p->pbuf[j+d] = p->pbuf[j];
			j=j-d;
		}
		if ((j+d) != i)
		{
		    p->pbuf[j+d] = tmp;
		}
	}
}
void shellsort(ARRAY* p)
{
	int d = p->length/2;
	while(d >=1)
	{
		shellinsert(p, d);
		d = d/2;

	}
}
#if 0
int downsort(ARRAY *p, int i)
{
	int len = p->length;
	pelem = i;

	while(pelem < len)
	{
		child = pelem*2+1;
		if (p->pbuf[chile]<p->pbuf[child+1])
		{
			++child;
		}

		if (p->pbuf[pelem]<p->pbuf[child])
		{
			int tmp = p->pbuf[pelem];
			p->pbuf[elem]=p->pbuf[child];
			p->pbuf[child]=tmp;
		}
		pelem = pelem*2+1;
	}
}
#endif
//
//i is index n is array length
int minheapfixdown(ARRAY *p, int i, int n)
{
	int parent = i;
	int child = i*2+1;
	int tmp = p->pbuf[i];
	while(child<n)
	{
		if((child+1)<n)
		{
			if (p->pbuf[child]>p->pbuf[child+1])
			{
				++child;
			}
		}
		if (tmp > p->pbuf[child])
		{
			p->pbuf[parent] = p->pbuf[child];
		}
		else
		{
			break;
		}
		parent = child;
		child = 2*parent +1;
	}
	p->pbuf[parent] = tmp;
}
int makeheap(ARRAY *p)
{
	int len = p->length;
	int last = ((len-2)/2);

	while(last>=0)
	{
		minheapfixdown(p,last,p->length);
#if 0
		int j = last;
	    int	k = 2*j+1;
		int tmp = p->pbuf[j];
		while(k <(len))
		{
			if ((k+1) < len)
			{
				if(p->pbuf[k]>p->pbuf[k+1])
					k++;
			}
			if (tmp>p->pbuf[k])
			{
				p->pbuf[j]=p->pbuf[k];
				j=k;
			}
			else
			{
				break;
			}
			k = 2*j+1;
		}
		p->pbuf[j] = tmp;
#endif
		last--;
	}
}
#if 0
int bucketsort(ARRAY* p)
{

	int len = p->length;
	for (int i = (len-1)/2; i>=0;i--)
	{
		downsort(p, i);
	}
}
#endif
int heapsort(ARRAY * p)
{
	makeheap(p);	
	int n = p->length;
	for(int i = n-1; i >=0;i--)
	{
		int tmp = p->pbuf[i];
		p->pbuf[i]= p->pbuf[0];
		p->pbuf[0] = tmp;
		minheapfixdown(p,0,i);
	}
}
int main()
{
	ARRAY *p = new ARRAY(10);
	int  tmp[] = {2,3,1,8,5,7,0,1,9,4};
	int i = 0;
	while(i< sizeof(tmp)&& i< p->length)
	{
		p->pbuf[i] = tmp[i];
		++i;
	}
	prtArray(p);
	cout << "after sort:" <<endl;

    //bubblesort2(p);
	//selectsort(p);
	//insertsort(p);
	//shellsort(p);
	heapsort(p);
	prtArray(p);
	return 0;

}
