#ifndef ALBUMSERVICE_H
#define ALBUMSERVICE_H
#pragma once
#include "AlbumRepository.h"
#include "SongRepository.h"
#include <vector>

class AlbumService
{
    AlbumRepository& albumrep;
    SongRepository& songrep;
public:
    AlbumService(AlbumRepository& arep,SongRepository& srep);
    vector<Album> getArtistAlbum(int artistid);
    vector<Song> getAlbumSongs(int albumid);
    static void sortByName(vector<Album>& albums);
    void deleteAlbum(int albumid);
};

#endif // ALBUMSERVICE_H
