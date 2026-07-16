#ifndef ALBUM_H
#define ALBUM_H
#include "account.h"
#include <QObject>

class Album : public Account
{
    Q_OBJECT
    string albumname;
    string albumid;
    string artistid;
public:
    Album();
};

#endif // ALBUM_H
