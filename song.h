#pragma once
#ifndef SONG_H
#define SONG_H
#include <string>
using namespace std;

class Song
{
public:
    string songname;
    int releaseyear;
    string genre;
    string filename;
    int songid;
    int artistid;
    int albumid;

    Song();
    Song(string songname, int releaseyear,string genre, string filename, int songid , int artistid,int albumid);
};

#endif // SONG_H
