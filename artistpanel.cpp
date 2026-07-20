#include "artistpanel.h"
#include <QVBoxLayout>
ArtistPanel::ArtistPanel(Account artist, ArtistService& service, QWidget* parent):QWidget(parent),currentartist(artist),artistservice(service)
{
    albumlist = new QListWidget(this);
    songlist  = new QListWidget(this);
    addalbumbtn = new QPushButton("Add Album", this);
    addsongbtn  = new QPushButton("Add Song", this);
    editbtn     = new QPushButton("Edit", this);
    deletebtn   = new QPushButton("Delete", this);

    auto* layout = new QVBoxLayout(this);
    layout->addWidget(albumlist);
    layout->addWidget(addalbumbtn);
    layout->addWidget(songlist);
    layout->addWidget(addsongbtn);
    layout->addWidget(editbtn);
    layout->addWidget(deletebtn);

    connect(albumlist, &QListWidget::currentRowChanged, this, &ArtistPanel::refreshSongs);
    refreshAlbums();
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