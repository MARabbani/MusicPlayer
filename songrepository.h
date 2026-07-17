#ifndef SONGREPOSITORY_H
#define SONGREPOSITORY_H
#pragma once
#include "AbstractRepository.h"
#include "Song.h"
#include <vector>
#include <unordered_map>
using namespace std;

class SongRepository:public AbstractRepository<Song>
{
    unordered_map<int,Song> data;
    int nextId=1;
public:
    int save(Song& song)override;
    bool remove(int id)override;
    optional<Song> search(int id)override;

    vector<Song> singleSongs(int artistid);
    vector<Song> getByAlbum(int albumid);
    vector<Song> getByArtist(int artistid);
    vector<Song> getByPlaylist(int playlistid , const vector<int>& songids);
    vector<Song> getByLikedSongs(int listenerid,const vector<int>& likedids);
};

#endif // SONGREPOSITORY_H
