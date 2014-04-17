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

int _insert_node_to_tree(TREE_NODE * &head_node, int data, TREE_NODE *parent)
{
    if (head_node == NULL)
    {
    	TREE_NODE *p = creat_tree_node(data);
        CHK(p != NULL);
        head_node = p;
        p->parent = parent;
        return 0;

    }

    if (data < head_node->data)
    {
        _insert_node_to_tree(head_node->left_child, data, head_node);
    }
    else 
    {
        _insert_node_to_tree(head_node->right_child, data, head_node);
    }
    return 0;
}

int insert_node_to_tree(TREE_NODE * &head_node, int data)
{
    if (head_node == NULL)
    {
    	TREE_NODE *p = creat_tree_node(data);
        CHK(p != NULL);

        head_node = p;
        return 0;
    }

    
	return 0;
}

int find_node_in_tree(TREE_NODE* &head_node, int data, TREE_NODE *&node)
{
    if (head_node == NULL)
    {
        node = NULL;
        return 0;
    }

    if (head_node->data == data)
    {
        node = head_node;
        return 0;
    }

    if (head_node->data > data)
    {
        find_node_in_tree(head_node->left_child, data, node);
    }
    else
    {
        find_node_in_tree(head_node->right_child, data, node);
    }

    return 0;
}

int count_node_in_tree(TREE_NODE *&head_node)
{
    if (head_node == NULL)
    {
        return 0;
    }

    return 1+ count_node_in_tree(head_node->left_child) +count_node_in_tree(head_node->right_child);
}

void print_all_node(TREE_NODE *&head_node)
{
    if (head_node == NULL)
    {
        return ;
    }
    print_all_node(head_node->left_child);
    cout << head_node->data;
    print_all_node(head_node->right_child);
}

int main()
{
    TREE_NODE *head =NULL;
    insert_node_to_tree(head, 4);
    insert_node_to_tree(head, 1);
    insert_node_to_tree(head, 5);
    insert_node_to_tree(head, 9);
    insert_node_to_tree(head, 0);

    print_all_node(head);
    cout << count_node_in_tree(head) <<endl;
    return 0;
}
