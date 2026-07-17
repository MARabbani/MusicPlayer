#include "authservice.h"
#include <stdexcept>


AuthService::AuthService(AccountRepository& rep): accountrep(rep){};
Account AuthService::login(string& username,string& password){
    auto acc=accountrep.searchByUsername(username);
    if(!acc.has_value()) throw runtime_error("username not found");
    if(acc->password!=password) throw runtime_error("password is incorrect");
    return *acc;
};
int AuthService::signUp(Account& newaccount){
    auto exist=accountrep.searchByUsername(newaccount.username);
    if(exist.has_value()){
        throw runtime_error("this username has signed up");
    }
    return accountrep.save(newaccount);
};