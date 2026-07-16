#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
using namespace std;
#include <QObject>

class Account
{
    Q_OBJECT
    string fullname;
    string username;
    string biography;
    int ID;
    string role;
    string password;
public:
    Account();
};

#endif // ACCOUNT_H
