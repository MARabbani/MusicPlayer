#pragma once
#ifndef ALBUM_H
#define ALBUM_H
#include <string>
using namespace std;
class Album
{
public:
    string albumname;
    int albumid;
    int artistid;

    Album();
    Album(string albumname,int albumid, int artistid);
};

#endif // ALBUM_H
