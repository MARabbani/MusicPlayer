#include "artistpanel.h"
ArtistPanel::ArtistPanel(Account artist, ArtistService& service, QWidget* parent):QWidget(parent),currentartist(artist),artistservice(service)
{
}
void ArtistPanel::refreshAlbums() {
    albumlist->clear();
    for (auto& a:artistservice.getArtistAlbum(currentartist.id)) {
        albumlist->addItem(QString::fromStdString(a.albumname));
    }
}

void ArtistPanel::refreshSongs(int albumId) {
    songlist->clear();
    for (auto& s:artistservice.getAlbumSong(albumId)) {
        songlist->addItem(QString::fromStdString(s.songname));
    }
}