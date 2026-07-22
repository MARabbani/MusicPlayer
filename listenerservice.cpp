#include "listenerservice.h"

ListenerService::ListenerService(PlaylistRepository& prep, SongRepository& srep,
                                 ListenerRepository& lrep, ArtistRepository& arep, AlbumRepository& abrep)
    : playlistrep(prep), songrep(srep), listenerrep(lrep), artistrep(arep), albumrep(abrep) {}

int ListenerService::createFavoritePlaylist(int listenerid) {
    string name = "Favorite Songs";
    PlayList p(name, listenerid, 0);
    return playlistrep.save(p);
}
int ListenerService::createPlaylist(int listenerid, string& name) {
    PlayList p(name, listenerid, 0);
    return playlistrep.save(p);
}
void ListenerService::updatePlaylist(PlayList& playlist) { playlistrep.save(playlist); }
void ListenerService::deletePlaylist(int playlistid) { playlistrep.remove(playlistid); }
void ListenerService::addSongToPlaylist(int playlistid, int songid) { playlistrep.insertSong(playlistid, songid); }
void ListenerService::removeSongFromPlaylist(int playlistid, int songid) { playlistrep.removeSong(playlistid, songid); }
void ListenerService::likeSong(int listenerid, int songid) { listenerrep.updateLiked(listenerid, songid, true); }
void ListenerService::unlikeSong(int listenerid, int songid) { listenerrep.updateLiked(listenerid, songid, false); }
bool ListenerService::isLiked(int listenerid, int songid) { return listenerrep.isLiked(listenerid, songid); }
vector<PlayList> ListenerService::getPlaylists(int listenerid) { return playlistrep.playlists(listenerid); }

vector<Account> ListenerService::getAllArtists() { return artistrep.getAllArtists(); }
vector<Album> ListenerService::getArtistAlbums(int artistid) { return albumrep.albums(artistid); }
vector<Song> ListenerService::getAlbumSongs(int albumid) { return songrep.getByAlbum(albumid); }
vector<Song> ListenerService::getSingles(int artistid) { return songrep.singleSongs(artistid); }

optional<PlayList> ListenerService::getFavoritePlaylist(int listenerid) {
    for (auto& p : playlistrep.playlists(listenerid))
        if (p.playlistname == "Favorite Songs") return p;
    return nullopt;
}
vector<Song> ListenerService::getPlaylistSongs(int playlistid) {
    auto opt = playlistrep.search(playlistid);
    if (!opt) return {};
    return songrep.getByPlaylist(playlistid, opt->songsid);
}