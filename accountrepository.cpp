#include "accountrepository.h"

int AccountRepository::save(Account& account){
    Account a =account;
    if (a.id==0) a.id = nextid++;
    data[a.id] =a;
    return a.id;
}
bool AccountRepository::remove(int id){
    return data.erase(id)>0;
}
optional<Account> AccountRepository::search(int id){
    auto it=data.find(id);
    if (it!=data.end()) return it->second;
    return std::nullopt;
}