#pragma once
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include "ArtistService.h"
#include "account.h"

class ArtistPanel:public QWidget{
    Q_OBJECT
    Account currentartist;
    ArtistService& artistservice;
    QListWidget* albumlist;
    QListWidget* songlist;
    QPushButton* addalbumbtn;
    QPushButton* addsongbtn;
    QPushButton* editbtn;
    QPushButton* deletebtn;

public:
    ArtistPanel(Account artist,ArtistService& service,QWidget* parent=nullptr);

private slots:
    void refreshAlbums(){
        albumlist->clear();
        for (auto& a:artistservice.getArtistAlbum(currentartist.id))
            albumlist->addItem(QString::fromStdString(a.albumname));
    }
    void refreshSongs(int albumId) {
        songlist->clear();
        for (auto& s:artistservice.getAlbumSong(albumId))
            songlist->addItem(QString::fromStdString(s.songname));
    }
};