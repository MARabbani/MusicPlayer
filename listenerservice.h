#ifndef LISTENERSERVICE_H
#define LISTENERSERVICE_H
#pragma once
#include "PlaylistRepository.h"
#include "SongRepository.h"
#include "ListenerRepository.h"
#include "ArtistRepository.h"
#include "AlbumRepository.h"

class ListenerService
{
    PlaylistRepository& playlistrep;
    SongRepository& songrep;
    ListenerRepository& listenerrep;
    ArtistRepository& artistrep;
    AlbumRepository& albumrep;
public:
    ListenerService(PlaylistRepository& prep, SongRepository& srep,
                    ListenerRepository& lrep, ArtistRepository& arep, AlbumRepository& abrep);
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
    vector<Account> getAllArtists();
    vector<Album> getArtistAlbums(int artistid);
    vector<Song> getAlbumSongs(int albumid);
    vector<Song> getSingles(int artistid);
    optional<PlayList> getFavoritePlaylist(int listenerid);
    vector<Song> getPlaylistSongs(int playlistid);
};

#endif // LISTENERSERVICE_H
