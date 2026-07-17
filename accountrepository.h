#ifndef ACCOUNTREPOSITORY_H
#define ACCOUNTREPOSITORY_H
#pragma once
#include "AbstractRepository.h"
#include "Account.h"
#include <unordered_map>
using namespace std;

class AccountRepository:public AbstractRepository<Account>
{
protected:
    unordered_map<int,Account> data;
    int nextid=1;
public:
    int save(Account& account) override;
    bool remove(int id) override;
    optional<Account> search(int id) override;
    optional<Account> searchByUsername(string& username);
};

#endif // ACCOUNTREPOSITORY_H
