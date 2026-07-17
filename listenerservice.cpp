#include "listenerservice.h"

ListenerService::ListenerService(PlaylistRepository& prep,SongRepository& srep,ListenerRepository& lrep):playlistrep(prep),songrep(srep),listenerrep(lrep){};
int ListenerService::createFavoritePlaylist(int listenerid){
    PlayList p("favorite song",listenerid,0);
    return playlistrep.save(p);
};
int ListenerService::createPlaylist(int listenerid,string& name){
    PlayList p(name,listenerid,0);
    return playlistrep.save(p);
};
void ListenerService::updatePlaylist(PlayList& playlist){
    playlistrep.save(playlist);
};
void ListenerService::deletePlaylist(int playlistid){playlistrep.remove(playlistid);};
void ListenerService::addSongToPlaylist(int playlistid,int songid){
    playlistrep.insertSong(playlistid,songid);
};
void ListenerService::removeSongFromPlaylist(int playlistid,int songid){
    playlistrep.removeSong(playlistid,songid);
};
void ListenerService::likeSong(int listenerid,int songid){
    listenerrep.updateLiked(listenerid,songid,true);
};
void ListenerService::unlikeSong(int listenerid , int songid){
    listenerrep.updateLiked(listenerid,songid,false);
};
bool ListenerService::isLiked(int listenerid,int songid){
    return listenerrep.isLiked(listenerid,songid);
};
vector<PlayList> ListenerService::getPlaylists(int listenerid){
    return playlistrep.playlists(listenerid);
};
