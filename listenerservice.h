#ifndef LISTENERSERVICE_H
#define LISTENERSERVICE_H
#pragma once
#include "PlaylistRepository.h"
#include "SongRepository.h"
#include "ListenerRepository.h"

class ListenerService
{
    PlaylistRepository& playlistrep;
    SongRepository& songrep;
    ListenerRepository& listenerrep;
public:
    ListenerService(PlaylistRepository& prep,SongRepository& srep,ListenerRepository& lrepo);
    int createFavoritePlaylist(int listenerid);
    int createPlaylist(int listenerid,string& name);
    void updatePlaylist(PlayList& playlist);
    void deletePlaylist(int playlistid);
    void addSongToPlaylist(int playlistid,int songid);
    void removeSongFromPlaylist(int playlistid,int songid);
    void likeSong(int listenerid,int songid);
    void unlikeSong(int listenerid , int songid);
    bool isLiked(int listenerid,int songid);
    vector<PlayList> getPlaylists(int listenerid);
    void ensureFavoritePlaylist(int listenerId);
};

#endif // LISTENERSERVICE_H
