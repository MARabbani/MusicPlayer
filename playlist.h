#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "account.h"
#include <QObject>

class PlayList : public Account
{
    Q_OBJECT
    string playlistname;
    string listenerid;
    string playlistid;
public:
    PlayList();
};

#endif // PLAYLIST_H
