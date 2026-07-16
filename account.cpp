#include "account.h"

Account::Account() {
    fullname="";
    username="";
    biography="";
    id=0;
    role=Role::Listener;
    password="";
}
Account::Account(int id, string fullname , string username,  string biography, Role role, string password){
    this->fullname= fullname;
    this->username= username;
    this->biography= biography;
    this->id= id;
    this->role= role;
    this->password= password;
};