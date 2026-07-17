#ifndef PLAYLISTSERVICE_H
#pragma once
#include "PlaylistRepository.h"
#include "SongRepository.h"
#include <vector>

class PlaylistService
{
    PlaylistRepository& playlistrep;
    SongRepository& songrep;
public:
    PlaylistService(PlaylistRepository& prep,SongRepository& srep);
    int createPlaylist(int listenerid,string& name);
    void renamePlaylist(int playlistid,string& newName);
    void deletePlaylist(int playlistid);
    void addSong(int playlistid,int songid);
    void removeSong(int playlistid,int songid);
    vector<Song> getPlaylistSongs(int playlistid);
    vector<PlayList> getListenerPlaylists(int listenerid);
    static void sortByName(vector<PlayList>& playlists);
};

#endif // PLAYLISTSERVICE_H
