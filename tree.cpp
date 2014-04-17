/*************************************************************************
	> File Name: tree.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Thu 17 Apr 2014 12:47:02 CST
 ************************************************************************/

#include<iostream>
#include "def.h"

using namespace std;
typedef struct _TREE_NODE
{
	_TREE_NODE()
	{
		parent = NULL;
		left_child = NULL;
		right_child = NULL;
	}
	int data;
	_TREE_NODE *parent;
	_TREE_NODE *left_child;
	_TREE_NODE *right_child;
}TREE_NODE;


TREE_NODE *creat_tree_node(int data)
{
	TREE_NODE *p = new TREE_NODE;
	CHK(p != NULL);
	p->data = data;

	return p;
}

int insert_node_to_tree(TREE_NODE * &head_node, int data)
{
	TREE_NODE *p = creat_tree_node(data);

	return 0;
}
int main()
{
	return 0;
}
