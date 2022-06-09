#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include"UserInfo.h"
using namespace std;
struct Node {
	UserInfo  Users;
	Node* next;
};
static Node* temp;
class LinkedList
{
private:

	Node* head;
	Node* tail;
	int numOfUers = 0;
public:
	LinkedList()
	{
		head = NULL;
		tail = NULL;

	}
	void insertEnd(UserInfo u)
	{
		numOfUers++;
		Node* temp = new Node;
		temp->Users = u;
		temp->next = NULL;
		if (tail == NULL)
		{
			head = tail = temp;
		}
		else
		{
			Node* checkUniqueValue = new Node;

			//henec we check if file (all-users.in) there is repeated username or no because username must be distinct (last line in seconde page in userlinkedlist)
			for (checkUniqueValue = head; checkUniqueValue != NULL; checkUniqueValue = checkUniqueValue->next)
			{
				if (checkUniqueValue->Users.getUserName() == u.getUserName())
				{
					throw "Sorry you repated username which It is forbidden to repeat username repated is :" + u.getUserName();
				}
			}

			tail->next = temp;
			tail = tail->next;
		}
	}
	
	int getnumOfUser() { return numOfUers; }
	
	UserInfo& searchInNodes(string username)
	{
		Node* temp = new Node();
		for (temp = head; temp != NULL; temp = temp->next)
		{
			if (temp->Users.getUserName() == username)
				return temp->Users;
		}
		throw "please enter Right userName ";
	}
	
	UserInfo& returnUser()//return user to check if this user belong to friendlist user(who log in ) or no  
	{
		if (temp == nullptr)
			temp = head;
		else if (temp->next == nullptr)
			temp = head;
		else
			temp = temp->next;
		return temp->Users;
	}

	/*void display()
	{
		Node* temp = new Node;

		for (temp = head; temp != NULL; temp = temp->next)
		{
			cout << temp->Users.getUserName() << " " << temp->Users.getName() << " " << temp->Users.getEmail();
			cout << endl;
		}
	}*/

};
#endif // LINKEDLIST_H
