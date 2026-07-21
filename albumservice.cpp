#include "albumservice.h"
#include <algorithm>

AlbumService::AlbumService(AlbumRepository& arep,SongRepository& srep):albumrep(arep),songrep(srep){}
vector<Album> AlbumService::getArtistAlbum(int artistid){
    return albumrep.albums(artistid);
};
vector<Song> AlbumService::getAlbumSongs(int albumid){
    return songrep.getByAlbum(albumid);
};
void AlbumService::sortByName(vector<Album>& albums){
    sort(albums.begin(),albums.end(),[](Album& a,Album& b){return a.albumname<b.albumname; });
};
void AlbumService::deleteAlbum(int albumid){
    auto songs =songrep.getByAlbum(albumid);
    for(auto& s:songs){
        songrep.remove(s.songid);
    }
    albumrep.remove(albumid);
};
