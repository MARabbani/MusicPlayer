#ifndef SONG_H
#define SONG_H

#include <QObject>
using namespace std;

class Song
{
    Q_OBJECT
    string songname;
    string releaseyear;
    string genre;
    string filename;
    string songid;
    string artistid;
    string albumid;
public:
    Song();
};

#endif // SONG_H
