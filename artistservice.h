#ifndef ARTISTSERVICE_H
#define ARTISTSERVICE_H
#pragma once
#include "AlbumRepository.h"
#include "SongRepository.h"
#include "accountrepository.h"

class ArtistService
{
    AlbumRepository& albumrep;
    SongRepository& songrep;
    AccountRepository& accountrep;
public:
    ArtistService(AlbumRepository& arep, SongRepository& srep, AccountRepository& accrep);
    int createAlbum(int artistid,string& name);
    void updateAlbum(Album& album);
    void deleteAlbum(int albumid);
    int createSong(int artistid, string& name, int year,string& genre,string& filepath,int albumid=0);
    void updateSong(Song& song);
    void deleteSong(int songid);
    vector<Album> getArtistAlbum(int artistid);
    vector<Song> getAlbumSong(int albumid);
    vector<Song> getSingle(int artistid);
    void updateAccount(Account& account);
    void deleteAccount(int accountId);

};

#endif // ARTISTSERVICE_H
