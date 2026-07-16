#pragma once
#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <string>
#include <vector>

using namespace std;
class PlayList
{
public:
    string playlistname;
    int listenerid;
    int playlistid;
    vector<int> songsid;

    PlayList();
    PlayList(string playlisttname, int listenerid,int playlistid);
};

#endif // PLAYLIST_H
