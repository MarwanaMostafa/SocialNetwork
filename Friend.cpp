#include "Friend.h"
#include"UserInfo.h"

void Friend::setUser(UserInfo& user) {
	FRIEND = &user;
	userName = user.getUserName();
}

string Friend::getUserName()
{
	return userName;
}
string	Friend::getName()
{
	return FRIEND->getName();
}

string	Friend::getEmail()
{
	return FRIEND->getEmail();
}

UserInfo& Friend::getUser()
{
	return *FRIEND;
}

ostream& operator<<(ostream& output, const Friend& User) {
	output << "UserName: " << User.userName << "Name : " << User.FRIEND->getName() << " Email : " << User.FRIEND->getEmail() << endl;
	return output;
}
