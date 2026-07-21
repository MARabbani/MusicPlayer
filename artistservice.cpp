#include "artistservice.h"

ArtistService::ArtistService(AlbumRepository& arep,SongRepository& srep):albumrep(arep) , songrep(srep){};
int ArtistService::createAlbum(int artistid,string& name){
    Album album(name, 0,artistid);
    return albumrep.save(album);
};
void ArtistService::updateAlbum(Album& album){albumrep.save(album);};
void ArtistService::deleteAlbum(int albumid){
    auto songs = songrep.getByAlbum(albumid);
    for (auto& s: songs){
        songrep.remove(s.songid);
    }
    albumrep.remove(albumid);
};
int ArtistService::createSong(int artistid, string& name, int year,string& genre,string& filepath,int albumid){
    Song song(name,year,genre,filepath,0,artistid,albumid);
    return songrep.save(song);
};
void ArtistService::updateSong(Song& song){songrep.save(song);};
void ArtistService::deleteSong(int songid){songrep.remove(songid);};
vector<Album> ArtistService::getArtistAlbum(int artistid){return albumrep.albums(artistid);};
vector<Song> ArtistService::getAlbumSong(int albumid){return songrep.getByAlbum(albumid);};
vector<Song> ArtistService::getSingle(int artistid){return songrep.singleSongs(artistid);};



