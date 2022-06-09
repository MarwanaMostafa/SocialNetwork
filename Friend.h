#pragma once
#include<iostream>
using namespace std;
class UserInfo;
class Friend
{
private:
	string userName;
	UserInfo* FRIEND;
public:
	void setUser(UserInfo& user);

	string getUserName();
	
	string getName();
	
	string getEmail();
	
	UserInfo& getUser();
	
	friend ostream& operator<<(ostream& output, const Friend& User);
};
