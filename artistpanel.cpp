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
#include <qlabel.h>
#include <QComboBox>

ArtistPanel::ArtistPanel(Account artist, ArtistService& service, QWidget* parent):QWidget(parent),currentartist(artist),artistservice(service)
{
    searchEdit=new QLineEdit();
    searchEdit->setPlaceholderText("Search by name...");
    sortCombo =new QComboBox();
    sortCombo->addItems({"Sort: Name ↑","Sort: Name ↓","Sort: Year ↑","Sort: Year ↓"});
    genreFilter = new QComboBox();
    genreFilter->addItem("All Genres");
    yearFilter = new QSpinBox();
    yearFilter->setRange(0, 2100);
    yearFilter->setSpecialValueText("Any Year");
    yearFilter->setValue(0);
    editAccountBtn = new QPushButton("Edit Account");
    deleteAccountBtn = new QPushButton("Delete Account");
    addalbumbtn = new QPushButton("Add Album", this);
    addsongbtn = new QPushButton("Add Song", this);
    editbtn= new QPushButton("Edit", this);
    deletebtn= new QPushButton("Delete", this);

    searchEdit   = new QLineEdit(this);
    searchEdit->setPlaceholderText("Search by name...");
    sortCombo    = new QComboBox(this);
    sortCombo->addItems({"Name ↑","Name ↓","Year ↑","Year ↓"});
    genreFilter  = new QComboBox(this);
    genreFilter->addItem("All Genres");
    yearFilter   = new QSpinBox(this);
    yearFilter->setRange(0,2100);
    yearFilter->setSpecialValueText("Any Year");
    yearFilter->setValue(0);
    albumlist =new QListWidget(this);
    songlist =new QListWidget(this);

    auto* filterWidget = new QWidget(this);
    auto* filterBar = new QHBoxLayout(filterWidget);
    filterBar->setContentsMargins(0,0,0,0);
    filterBar->addWidget(searchEdit);
    filterBar->addWidget(sortCombo);
    filterBar->addWidget(new QLabel("Genre:",this));
    filterBar->addWidget(genreFilter);
    filterBar->addWidget(new QLabel("Year:",this));
    filterBar->addWidget(yearFilter);

    editAccountBtn=new QPushButton("Edit Account", this);
    deleteAccountBtn = new QPushButton("Delete Account", this);
    auto* accountWidget = new QWidget(this);
    auto* accountBar=new QHBoxLayout(accountWidget);
    accountBar->setContentsMargins(0,0,0,0);
    accountBar->addWidget(editAccountBtn);
    accountBar->addWidget(deleteAccountBtn);



    auto* layout = new QVBoxLayout(this);

    layout->addWidget(albumlist);
    layout->addWidget(addalbumbtn);
    layout->addWidget(filterWidget);
    layout->addWidget(songlist);
    layout->addWidget(addsongbtn);
    layout->addWidget(editbtn);
    layout->addWidget(deletebtn);
    layout->addWidget(accountWidget);


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

    connect(searchEdit, &QLineEdit::textChanged,this, &ArtistPanel::applyFilter);
    connect(sortCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ArtistPanel::applyFilter);
    connect(genreFilter,QOverload<int>::of(&QComboBox::currentIndexChanged), this,&ArtistPanel::applyFilter);
    connect(yearFilter,QOverload<int>::of(&QSpinBox::valueChanged),this, &ArtistPanel::applyFilter);

    connect(editAccountBtn,   &QPushButton::clicked, this, &ArtistPanel::editAccount);
    connect(deleteAccountBtn, &QPushButton::clicked, this, &ArtistPanel::deleteAccount);

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
    if (albumId == 0)
        currentSongs = artistservice.getSingle(currentartist.id);
    else
        currentSongs = artistservice.getAlbumSong(albumId);

    genreFilter->blockSignals(true);
    QString cur = genreFilter->currentText();
    genreFilter->clear(); genreFilter->addItem("All Genres");
    for (auto& s : currentSongs) {
        QString g = QString::fromStdString(s.genre);
        if (genreFilter->findText(g) == -1) genreFilter->addItem(g);
    }
    int idx = genreFilter->findText(cur);
    genreFilter->setCurrentIndex(idx >= 0 ? idx : 0);
    genreFilter->blockSignals(false);

    applyFilter();
}

void ArtistPanel::applyFilter() {
    QString search = searchEdit->text().toLower();
    QString genre  = genreFilter->currentText();
    int     year   = yearFilter->value();

    vector<Song> filtered;
    for (auto& s : currentSongs) {
        if (!search.isEmpty() && !QString::fromStdString(s.songname).toLower().contains(search)) continue;
        if (genre != "All Genres" && s.genre != genre.toStdString()) continue;
        if (year != 0 && s.releaseyear != year) continue;
        filtered.push_back(s);
    }

    int sortIdx = sortCombo->currentIndex();
    sort(filtered.begin(), filtered.end(), [sortIdx](const Song& a, const Song& b){
        if (sortIdx == 0) return a.songname < b.songname;
        if (sortIdx == 1) return a.songname > b.songname;
        if (sortIdx == 2) return a.releaseyear < b.releaseyear;
        return a.releaseyear > b.releaseyear;
    });

    songlist->clear();
    for (auto& s : filtered) {
        auto* item = new QListWidgetItem(QString::fromStdString(s.songname));
        item->setData(Qt::UserRole, s.songid);
        songlist->addItem(item);
    }
}

void ArtistPanel::editAccount() {
    bool ok;
    QString newName = QInputDialog::getText(this, "Edit Account", "New username:", QLineEdit::Normal,
                                            QString::fromStdString(currentartist.username), &ok);
    if (!ok || newName.trimmed().isEmpty()) return;
    QString newPass = QInputDialog::getText(this, "Edit Account", "New password:", QLineEdit::Password, "", &ok);
    if (!ok) return;

    currentartist.username = newName.toStdString();
    if (!newPass.isEmpty()) currentartist.password = newPass.toStdString();
    artistservice.updateAccount(currentartist);
}

void ArtistPanel::deleteAccount() {
    auto btn = QMessageBox::question(this, "Delete Account", "Are you sure?");
    if (btn != QMessageBox::Yes) return;
    artistservice.deleteAccount(currentartist.id);
    emit accountDeleted();

}

