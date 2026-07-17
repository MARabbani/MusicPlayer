#include "playlistservice.h"
#include <algorithm>

PlaylistService::PlaylistService(PlaylistRepository& prep,SongRepository& srep):playlistrep(prep),songrep(srep){}
int PlaylistService::createPlaylist(int listenerid,string& name){
    PlayList p(name,listenerid,0);
    return playlistrep.save(p);
};
void PlaylistService::renamePlaylist(int playlistid,string& newName){
    auto playlists=playlistrep.playlists(-1);
    for (auto& p:playlists) {
        if (p.playlistid==playlistid) {
            p.playlistname =newName;
            playlistrep.save(p);
            break;
        }
    }
};
void PlaylistService::deletePlaylist(int playlistid){
    playlistrep.remove(playlistid);
};
void PlaylistService::addSong(int playlistid,int songid){
    playlistrep.insertSong(playlistid,songid);
};
void PlaylistService::removeSong(int playlistid,int songid){
    playlistrep.removeSong(playlistid,songid);
};
vector<Song> PlaylistService::getPlaylistSongs(int playlistid){
    return songrep.getByPlaylist(playlistid);
};
vector<PlayList> PlaylistService::getListenerPlaylists(int listenerid){
    return playlistrep.playlists(listenerid);
};
void PlaylistService::sortByName(vector<PlayList>& playlists){
    std::sort(playlists.begin(),playlists.end(),[](PlayList& a,PlayList& b){return a.playlistname<b.playlistname;});
};