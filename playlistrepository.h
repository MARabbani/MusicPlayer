#ifndef PLAYLISTREPOSITORY_H
#define PLAYLISTREPOSITORY_H
#pragma once
#include "AbstractRepository.h"
#include "Playlist.h"
#include <unordered_map>
#include <vector>

class PlaylistRepository : AbstractRepository<PlayList>
{
    unordered_map<int,PlayList> data;
    int nextid=1;
public:
    int save(PlayList& playlist) override;
    bool remove(int id) override;
    optional<PlayList> search(int id) override;


    bool insertSong(int playlistid , int songid);
    bool removeSong(int playlistid, int songid);
    vector<PlayList> playlists(int listenerid);
};

#endif // PLAYLISTREPOSITORY_H
