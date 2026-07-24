#include "playlistrepository.h"
#include <algorithm>

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


bool PlaylistRepository::insertSong(int playlistid , int songid){
    auto it=data.find(playlistid);
    if(it==data.end()) return false;
    it->second.songsid.push_back(songid);
    return true;
};
bool PlaylistRepository::removeSong(int playlistid, int songid){
    auto it=data.find(playlistid);
    if(it==data.end()) return false;
    auto& ids=it->second.songsid;
    auto find=std::find(ids.begin(),ids.end(),songid);
    if(find==ids.end()) return false;
    ids.erase(find);
    return true;
};
vector<PlayList> PlaylistRepository::playlists(int listenerid){
    vector<PlayList> result;
    for (auto& [id, p] :data)
        if (p.listenerid==listenerid) result.push_back(p);
    return result;
}
