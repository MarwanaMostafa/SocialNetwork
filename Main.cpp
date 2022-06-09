#include <iostream>
#include "LinkedList.h"
#include <fstream>
using namespace std;

void saveAllUsers(LinkedList& LIST)
{
	string name;
	string email;
	string firstName;
	string secondName;
	string userName;

	ifstream ReadFile("all-users.in");
	while (ReadFile >> userName >> firstName >> secondName >> email)
	{
		name = firstName + secondName;//why hence we use first and second because in file there is space between name
		UserInfo  u(userName, name, email);
		LIST.insertEnd(u);
	}
	ReadFile.close();
}


UserInfo logIn(LinkedList& LIST)
{
	cout << "Login please enter UserName to log in (hint you have 3 attemps to enter wrong userName) " << endl;
	int i = 0;
	while (i < 3)
	{
		string username;
		cin >> username;
		username = username + ',';
		try {
			UserInfo USER = LIST.searchInNodes(username);
			if (USER.getUserName() == username)
			{
				cout << "Succeful login " << endl;
				return USER;
			}
		}
		catch (const char*)//catch throw if user enter username wrong (throw occur from function searchInNodes in class linked list)
		{
		}
		i++;
		cout << "you enter wrong username so enter username agin(hint you have" << 3 - i << "attemps) " << endl;
	}
	cout << "username you enter there isn't file allusers.in and you pass number of attemps  ";
	exit(0);

}


void addDefaultFirends(LinkedList& list)//add default firends(without user intervention) from file all-users-relations.in
{
	//role this function : is execute each line in file all-users-relations.in
	string userName;
	string userNameFirend;
	ifstream ReadFile("all-users-relations.in");
	Friend FRIEND;
	FriendList saveFriends;

	while (ReadFile >> userName >> userNameFirend)
	{
		userNameFirend = userNameFirend + ',';
		FRIEND.setUser(list.searchInNodes(userNameFirend));//hence we assign Friend from all-users-relations.in to add in friendlist of user
		list.searchInNodes(userName).getFriendList().addFirend(FRIEND, userNameFirend);//hence we add Friend to Friend List

		//the next tow lines:updated added friend (update the two users friendsBST) 
		//The following lines are an edit at Friend which we add user(who is log in) to be Friend
		FRIEND.setUser(list.searchInNodes(userName));
		list.searchInNodes(userNameFirend).getFriendList().addFirend(FRIEND, userName);
	}
	ReadFile.close();
}


//all next function are application action
void SearchFriend(UserInfo& USER, LinkedList& LIST)//role function : search in friendlist if entered username is Freind for user or no 
{
	string userName;
	cout << "enter Username friend " << endl;
	cin >> userName;
	userName = userName + ',';
	if (!USER.getFriendList().find(userName))//check if user belong to Friendlist or no 
		cout << "not found this friend which you are search about " << endl;
	else
		cout << LIST.searchInNodes(userName);
}

void addFirend(UserInfo& USER, LinkedList& LIST)
{
	cout << "enter username for your firend" << endl;
	string username;
	cin >> username;
	username = username + ',';

	if (USER.getFriendList().find(username))
		cout << " You are already friends" << endl;

	else {
		Friend NewFriend;
		NewFriend.setUser(LIST.searchInNodes(username));//hence we check if user enter username from file(all-users.in) or no 

		USER.getFriendList().addFirend(NewFriend, username);

		//the next tow lines:updated added friend (update the two users friendsBST) 
		//The following lines are an edit at Friend which we add user(who is log in) to be Friend
		Friend updateOtherFriend;
		updateOtherFriend.setUser(USER);
		NewFriend.getUser().getFriendList().addFirend(updateOtherFriend, USER.getUserName());
		cout << "You are now friends" << endl;
	}
}


void DeleteFriend(UserInfo& USER, LinkedList& LIST)
{
	string removedFriend;
	cout << "enter userName Friend which need remove" << endl;
	cin >> removedFriend;
	removedFriend = removedFriend + ',';

	if (USER.getFriendList().find(removedFriend))//hence check if user has this entered username in Friendlist or no 
	{
		USER.getFriendList().deleteFriend(removedFriend);

		//The following lines are an edit at Friend which we removeuser(who is log in) to be Friend
		Friend updateRemovedFriend;
		updateRemovedFriend.setUser(LIST.searchInNodes(removedFriend));
		updateRemovedFriend.getUser().getFriendList().deleteFriend(USER.getUserName());
		cout << "\nNow you and -" << removedFriend << "- are not friends" << endl;
	}

	else
		cout << "you haven't this Friend :" << removedFriend << endl;
}


void peopleyoumayknow(UserInfo& USER, LinkedList& LIST)
{

	int i = 0;
	UserInfo TEMP;
	int endAllUser = LIST.getnumOfUser();
	while (i < 5 && endAllUser > 0) {// i represent: Recommend 5 new friends ,endAllUser represent: if list ended and threre is less than Recommend 5 new friends (if the existed less than 5 view them -)
		TEMP = LIST.returnUser();
		if (!USER.getFriendList().find(TEMP.getUserName()) && USER.getUserName() != TEMP.getUserName())
		{
			cout << TEMP;
			i++;
		}
		endAllUser--;
	}
}

int main()
{
	try {
		cout << "welcome our application " << endl;
		LinkedList List;
		saveAllUsers(List);
		addDefaultFirends(List);
		int choise = 1;

		while (choise != 3)
		{
			UserInfo user = logIn(List);
			FriendList UserFriendList;
			cout << "1-if you need excute application action  enter 1 \n2-if you need log out  enter 2 \n3-if you need close application enter 3 " << endl;
			cin >> choise;

			if (choise == 1)
			{
				while (choise < 6)
				{
					cout << "\n1-if you need list all friends enter 1\n2-if you need Search in FriendList enter number 2" <<
						"\n3-if you need add new friend enter number 3\n4-if you need Delete from your FriendList enter number 4" <<
						"\n5-people you may know\n6-if you exit from application action\n" << endl;


					cin >> choise;
					switch (choise)
					{
					case 1:
						user.getFriendList().listAllFirends();
						break;
					case 2:

						try {
							SearchFriend(user, List);
						}
						catch (const char* msg)
						{
							cout << msg << endl;
						}
						break;
					case 3:
						try {
							addFirend(user, List);
						}
						catch (const char* msg)
						{
							cout << msg << endl;
						}
						break;
					case 4:
						DeleteFriend(user, List);
						break;
					case 5:
						peopleyoumayknow(user, List);
						break;
					default:
						break;

					}
				}
				cout << "if you need log out enter 2 \nif you need clsoe application please enter 3" << endl;
				cin >> choise;
			}

			if (choise == 2)
			{
				cout << "if you need log In agin please enter 1 \nif you need clsoe application please enter 3" << endl;
				cin >> choise;
			}

		}
		cout << "good bye" << endl;
		return 0;
	}

	catch (const char* msg)
	{
		cout << msg << endl;
	}

}
