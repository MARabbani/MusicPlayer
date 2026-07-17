#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H
#pragma once
#include "AccountRepository.h"

class AuthService
{
    AccountRepository& accountrep;
public:
    AuthService(AccountRepository& rep);
    Account login(string& username,string& password);
    int signUp(Account& newaccount);


};

#endif // AUTHSERVICE_H
