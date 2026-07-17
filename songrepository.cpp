#include "songrepository.h"

int SongRepository::save(Song& song){
    Song s=song;
    if (s.songid==0){s.songid=nextId++;}
    data[s.songid]=s;
    return s.songid;
};
bool SongRepository::remove(int id){
    bool erased=false;
    if(data.erase(id)>0){erased=true;}
    return erased;
};
optional<Song> SongRepository::search(int id){
    auto it=data.find(id);
    if(it!=data.end()){return it->second;}
    return nullopt;
};
vector<Song> SongRepository::singleSongs(int artistid){
    vector<Song> result;
    for(auto& [id,s]:data){
        if(s.artistid==artistid && s.albumid==0) result.push_back(s);
    }
    return result;
};
vector<Song> SongRepository::getByAlbum(int albumid){
    vector<Song> result;
    for(auto& [id,s]:data){
        if(s.albumid==albumid) result.push_back(s);
    }
    return result;
};
vector<Song> SongRepository::getByArtist(int artistid){
    vector<Song> result;
    for(auto& [id,s]:data){
        if(s.artistid==artistid) result.push_back(s);
    }
    return result;
};
vector<Song> SongRepository::getByPlaylist(int playlistid , const vector<int>& songids){
    vector<Song> result;
    for(int si:songids){
        auto op=search(si);
        if(op) result.push_back(*op);
    }
    return result;
};
vector<Song> SongRepository::getByLikedSongs(int listenerid,const vector<int>& likedids){
    return getByPlaylist(0,likedids);
};
