#include "playlistrepository.h"

int PlaylistRepository::save(PlayList& playlist){
    PlayList p=playlist;
    if(p.playlistid==0){p.playlistid=nextid++;}
    data[p.playlistid]=p;
    return p.playlistid;
};
bool PlaylistRepository:: remove(int id){
    return data.erase(id)>0;
};
optional<PlayList> PlaylistRepository:: search(int id){
    auto it=data.find(id);
    if(it!=data.end()){return it->second;}
    return nullopt;
};
