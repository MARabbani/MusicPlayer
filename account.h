#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
using namespace std;

enum class Role{Artist , Listener};
class Account
{
    string fullname;
    string username;
    string biography;
    int id;
    Role role;
    string password;
public:
    Account();
};

#endif // ACCOUNT_H
