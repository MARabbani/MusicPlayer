#include "artistpanel.h"
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QVariant>
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

    connect(albumlist, &QListWidget::currentRowChanged, this,[this](QListWidgetItem* current,QListWidgetItem* previous/* &ArtistPanel::refreshSongs*/){
        if(current) refreshSongs(current->data(Qt::UserRole).toInt());
    });
    connect(addalbumbtn, &QPushButton::clicked, this, [this](){
        bool ok;
        QString text = QInputDialog::getText(this, "ایجاد آلبوم", "input the name of new album:", QLineEdit::Normal, "", &ok);
        if (ok && !text.isEmpty()) {
            string name = text.toStdString();
            artistservice.createAlbum(currentartist.id, name);
            refreshAlbums();
        }
    });

    connect(deletebtn, &QPushButton::clicked, this, [this](){
        QListWidgetItem* currentItem = albumlist->currentItem();
        if(!currentItem) return;
        int albumId = currentItem->data(Qt::UserRole).toInt();

        if (albumId == 0) {
            QMessageBox::warning(this,"error", "U cannot delete the Singles folder!");
            return;
        }

        artistservice.deleteAlbum(albumId);
        refreshAlbums();
        songlist->clear();
    });

    refreshAlbums();
}

void ArtistPanel::refreshAlbums() {
    albumlist->clear();
    QListWidgetItem* singleItem = new QListWidgetItem("Singles (بدون آلبوم)");
    singleItem->setData(Qt::UserRole, 0);
    albumlist->addItem(singleItem);

    for (auto& a:artistservice.getArtistAlbum(currentartist.id)) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(a.albumname));
        item->setData(Qt::UserRole, a.albumid);
        albumlist->addItem(QString::fromStdString(a.albumname));
    }
}

void ArtistPanel::refreshSongs(int albumId) {
    songlist->clear();
    vector<Song> songsToDisplay;
    if (albumId == 0) {
        songsToDisplay = artistservice.getSingle(currentartist.id);
    } else {
        songsToDisplay = artistservice.getAlbumSong(albumId);
    }
    for (auto& s:songsToDisplay) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(s.songname));
        item->setData(Qt::UserRole, s.songid);
        songlist->addItem(item);
    }
}