#ifndef SONGSERVICE_H
#define SONGSERVICE_H
#pragma once
#include "Song.h"
#include <vector>

class SongService
{
public:
    static vector<Song> searchByName(vector<Song> songs,string& query);
    static vector<Song> filterByGenre(vector<Song> songs,string& genre);
    static vector<Song> filterByYear(vector<Song> songs, int year);
    static void sortByName(vector<Song>& songs);
    static void sortByYear(vector<Song>& songs);
};

#endif // SONGSERVICE_H
