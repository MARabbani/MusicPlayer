#ifndef ACCOUNTREPOSITORY_H
#define ACCOUNTREPOSITORY_H
#pragma once
#include "AbstractRepository.h"
#include "Account.h"
#include <unordered_map>
#include <vector>
using namespace std;

class AccountRepository:public AbstractRepository<Account>
{
protected:
    unordered_map<int,Account> data;
    int nextid=1;

    void loadFromFile();
    void saveToFile();

public:
    int save(Account& account) override;
    bool remove(int id) override;
    optional<Account> search(int id) override;
    optional<Account> searchByUsername(string& username);
    vector<Account> getAllArtists() {
        vector<Account> result;
        for (auto& [id, acc] : data)
            if (acc.role == Role::Artist) result.push_back(acc);
        return result;
    }
};

#endif // ACCOUNTREPOSITORY_H
