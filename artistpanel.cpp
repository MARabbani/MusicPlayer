#include "artistpanel.h"
#include "AddSongDialog.h"
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QVariant>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QDialogButtonBox>

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

    connect(albumlist, &QListWidget::currentItemChanged, this,[this](QListWidgetItem* current,QListWidgetItem* previous/* &ArtistPanel::refreshSongs*/){
        if(current) refreshSongs(current->data(Qt::UserRole).toInt());
    });
    connect(addalbumbtn, &QPushButton::clicked, this, [this](){
        bool ok;
        QString text = QInputDialog::getText(this, "creating album", "input the name of new album:", QLineEdit::Normal, "", &ok);
        if (ok && !text.isEmpty()) {
            string name = text.toStdString();
            artistservice.createAlbum(currentartist.id, name);
            refreshAlbums();
        }
    });

    connect(deletebtn, &QPushButton::clicked, this, [this](){
        if (songlist->currentItem() && songlist->currentItem()->isSelected()) {
            int songId = songlist->currentItem()->data(Qt::UserRole).toInt();
            artistservice.deleteSong(songId);

            int albumId = albumlist->currentItem() ? albumlist->currentItem()->data(Qt::UserRole).toInt() : 0;
            refreshSongs(albumId);
        }
        else if (albumlist->currentItem() && albumlist->currentItem()->isSelected()) {
            int albumId = albumlist->currentItem()->data(Qt::UserRole).toInt();
            if (albumId == 0) {
                QMessageBox::warning(this, "error", "U cannot delete the Singles folder!");
                return;
            }

            artistservice.deleteAlbum(albumId);
            refreshAlbums();
            songlist->clear();
        }
    });
    connect(addsongbtn, &QPushButton::clicked, this, [this]() {
        AddSongDialog dlg(this);
        if (dlg.exec() != QDialog::Accepted) return;

        QListWidgetItem* item = albumlist->currentItem();
        int albumId = item ? item->data(Qt::UserRole).toInt() : 0;

        std::string name = dlg.name().toStdString();
        std::string genre = dlg.genre().toStdString();
        std::string path = dlg.path().toStdString();
        artistservice.createSong(currentartist.id, name, dlg.year(), genre, path, albumId);

        refreshSongs(albumId);
    });

    connect(editbtn, &QPushButton::clicked, this, [this](){
        if (songlist->currentItem() && songlist->currentItem()->isSelected()) {
            int songId = songlist->currentItem()->data(Qt::UserRole).toInt();
            int albumId = albumlist->currentItem() ? albumlist->currentItem()->data(Qt::UserRole).toInt() : 0;

            vector<Song> songs = (albumId == 0) ? artistservice.getSingle(currentartist.id) : artistservice.getAlbumSong(albumId);
            Song targetSong;
            bool found = false;
            for(auto& s : songs) {
                if(s.songid == songId) {
                    targetSong = s;
                    found = true;
                    break;
                }
            }

            if (found) {
                QDialog editDlg(this);
                editDlg.setWindowTitle("editing the song");
                auto* formLayout = new QFormLayout(&editDlg);

                auto* nameEdit = new QLineEdit(QString::fromStdString(targetSong.songname), &editDlg);
                auto* genreEdit = new QLineEdit(QString::fromStdString(targetSong.genre), &editDlg);
                auto* pathEdit = new QLineEdit(QString::fromStdString(targetSong.filename), &editDlg);
                auto* yearEdit = new QSpinBox(&editDlg);
                yearEdit->setRange(1000, 3000);
                yearEdit->setValue(targetSong.releaseyear);

                formLayout->addRow("song name:", nameEdit);
                formLayout->addRow("genre:", genreEdit);
                formLayout->addRow("file path:", pathEdit);
                formLayout->addRow("year:", yearEdit);

                auto* btnBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &editDlg);
                formLayout->addWidget(btnBox);

                connect(btnBox, &QDialogButtonBox::accepted, &editDlg, &QDialog::accept);
                connect(btnBox, &QDialogButtonBox::rejected, &editDlg, &QDialog::reject);

                if (editDlg.exec() == QDialog::Accepted) {
                    if (!nameEdit->text().isEmpty()) {
                        targetSong.songname = nameEdit->text().toStdString();
                        targetSong.genre = genreEdit->text().toStdString();
                        targetSong.filename = pathEdit->text().toStdString();
                        targetSong.releaseyear = yearEdit->value();

                        artistservice.updateSong(targetSong);
                        refreshSongs(albumId);
                    }
                }
            }
        }
        else if (albumlist->currentItem() && albumlist->currentItem()->isSelected()) {
            int albumId = albumlist->currentItem()->data(Qt::UserRole).toInt();
            if (albumId == 0) {
                QMessageBox::warning(this, "Error", "You cannot edit the Singles folder!");
                return;
            }

            bool ok;
            QString text = QInputDialog::getText(this, "Edit Album", "Enter new album name:", QLineEdit::Normal, albumlist->currentItem()->text(), &ok);
            if (ok && !text.isEmpty()) {
                auto albums = artistservice.getArtistAlbum(currentartist.id);
                for(auto& a : albums) {
                    if(a.albumid == albumId) {
                        a.albumname = text.toStdString();
                        artistservice.updateAlbum(a);
                        refreshAlbums();
                        break;
                    }
                }
            }
        }
    });

    refreshAlbums();
}

void ArtistPanel::refreshAlbums() {
    albumlist->clear();
    QListWidgetItem* singleItem = new QListWidgetItem("Singles (no album)");
    singleItem->setData(Qt::UserRole, 0);
    albumlist->addItem(singleItem);

    for (auto& a:artistservice.getArtistAlbum(currentartist.id)) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(a.albumname));
        item->setData(Qt::UserRole, a.albumid);
        albumlist->addItem(item);
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