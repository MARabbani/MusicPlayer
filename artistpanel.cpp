#include "artistpanel.h"
ArtistPanel::ArtistPanel(Account artist, ArtistService& service, QWidget* parent)
    : QWidget(parent), currentartist(artist), artistservice(service)
{
    // کدهای مربوط به مقداردهی دکمه‌ها و لیست‌ها و چیدمان (Layout)
}
void ArtistPanel::refreshAlbums() {
    albumlist->clear();
    for (auto& a : artistservice.getArtistAlbum(currentartist.id)) {
        albumlist->addItem(QString::fromStdString(a.albumname));
    }
}

// پیاده‌سازی Slot دوم
void ArtistPanel::refreshSongs(int albumId) {
    songlist->clear();
    for (auto& s : artistservice.getAlbumSong(albumId)) {
        songlist->addItem(QString::fromStdString(s.songname));
    }
}