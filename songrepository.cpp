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
