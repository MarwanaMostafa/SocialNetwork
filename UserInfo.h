#ifndef USERINFO_H
#define USERINFO_H
#include<iostream>
#include "FriendList.h"
using namespace std;
class UserInfo {
private:
	string userName;
	string Name;
	string Email;
	FriendList friendBST;
public:
	UserInfo()
	{
		userName = "";
		Name = "";
		Email = "";
	}

	UserInfo(string username, string name, string email)
	{
		userName = username;
		Name = name;
		Email = email;
	}
	
	void setName(string name) {
		Name = name;
	}


	void setEmail(string email) {
		Email = email;
	}
	
	
	void setUserName(string UserName) {
		userName = UserName;
	}
	
	
	void setFriendList(FriendList& FIRENDLIST) {
		friendBST = FIRENDLIST;
	}


	FriendList& getFriendList() {
		return friendBST;
	}


	string getName() {
		return Name;
	}


	string getEmail() {
		return Email;
	}

	string getUserName() {
		return userName;
	}

	void operator = (const UserInfo& U) {
		Email = U.Email;
		Name = U.Name;
		userName = U.userName;
		friendBST = U.friendBST;
	}

	friend ostream& operator<<(ostream& output, const UserInfo& User) {
		output << "UserName: " << User.userName << "Name : " << User.Name << " Email : " << User.Email << endl;
		return output;
	}

};
#endif // USERINFO_H
