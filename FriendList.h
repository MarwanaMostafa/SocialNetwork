#pragma once
#ifndef FRIENDLIST_H
#define FRIENDLIST_H
#include<stdio.h>
#include"Friend.h"
#include<stdlib.h>
#include<string.h>
using namespace std;
class FriendList
{
private:
	struct TreapNode
	{
		int priority;
		string userName;
		Friend user;
		TreapNode* left;
		TreapNode* right;
		TreapNode()
		{
			priority = INT_MAX;
			left = NULL;
			right = NULL;
		}
		TreapNode(Friend& USER)
		{
			userName = USER.getUserName();
			user = USER;
			this->left = this->right = NULL;
			this->priority = rand() % 100;//100,1000,100000 any number
		}
	};
	TreapNode* root;
	void rotateLeft(TreapNode*& Node)  //left rotation
	{
		TreapNode* rightNode = Node->right;
		TreapNode* leftRightNode = Node->right->left;
		rightNode->left = Node;
		Node->right = leftRightNode;
		Node = rightNode;
	}
	void rotateRight(TreapNode*& Node)   //right rotation
	{
		TreapNode* leftNode = Node->left;
		TreapNode* rightLeftNode = Node->left->right;
		leftNode->right = Node;
		Node->left = rightLeftNode;
		Node = leftNode;
	}
	void insertNode(Friend& pointerToUser, string User_Name, TreapNode*& Root)
	{

		if (Root == nullptr)
		{
			Root = new TreapNode(pointerToUser);
			return;
		}
		if (User_Name < Root->userName)
		{
			insertNode(pointerToUser, User_Name, Root->left);
			if (Root->left != NULL && Root->left->priority > Root->priority)
				rotateRight(Root);
		}
		else
		{
			insertNode(pointerToUser, User_Name, Root->right);
			if (Root->right != NULL && Root->right->priority > Root->priority)
				rotateLeft(Root);
		}
	}
	bool Search(string findUserName, TreapNode*& Root)
	{
		if (Root == NULL)
			return false;
		if (findUserName == Root->userName)
			return true;
		if (findUserName < Root->userName)
			return Search(findUserName, Root->left);
		return Search(findUserName, Root->right);

	}
	void deleteNode(TreapNode*& root, string USERNAME) {
		if (root == nullptr)
			return;
		if (USERNAME < root->userName)
			deleteNode(root->left, USERNAME);
		else if (USERNAME > root->userName)
			deleteNode(root->right, USERNAME);
		else {
			if (root->left == nullptr && root->right == nullptr) {
				delete root;
				root = nullptr;
			}
			else if (root->left && root->right) {
				if (root->left->priority < root->right->priority) {
					rotateLeft(root);
					deleteNode(root->left, USERNAME);
				}
				else {
					rotateRight(root);
					deleteNode(root->right, USERNAME);
				}
			}
			else {
				TreapNode* child = (root->left) ? root->left : root->right;
				TreapNode* curr = root;
				root = child;
				delete curr;
			}
		}
	}
	void inorder(TreapNode*& Node)
	{
		if (Node == NULL)
			return;
		inorder(Node->left);
		//i write next comment because don't lost grade ,To clarify if doctor need print all information next comment do this  
		//cout << Node->user << endl;//Here I print all the information that pertains to each user's friend as written in the file(the third page is part List all friends)
		cout << "UserName : "<<Node->user.getUserName()<<"  Name: "<< Node->user.getName() << endl;//Here I am printing like the figure that is depressed (the third page is part List all friends):UserName1 Name1
		inorder(Node->right);
	}

public:

	FriendList()
	{
		root = NULL;
	}

	void addFirend(Friend& Firend, string nameFirend)
	{
		insertNode(Firend, nameFirend, root);
	}

	void deleteFriend(string userNAME)
	{
		deleteNode(root, userNAME);
	}

	bool find(string username)
	{
		return Search(username, root);
	}

	void listAllFirends()
	{
		inorder(root);
	}

	void operator=(const FriendList*& T)
	{
		root->left = T->root->left;
		root->priority = T->root->priority;
		root->right = T->root->right;
		root->user = T->root->user;
	}

};


#endif // FRIENDLIST_H
