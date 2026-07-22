#include "listenerpanel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QDialog>
#include <QFormLayout>
#include <QDialogButtonBox>

ListenerPanel::ListenerPanel(Account listener, ListenerService& service, QWidget* parent)
    : QWidget(parent), currentlistener(listener), listenerservice(service)
{
    if (!listenerservice.getFavoritePlaylist(listener.id).has_value())
        listenerservice.createFavoritePlaylist(listener.id);

    auto* mainLayout = new QVBoxLayout(this);

    auto* navLayout = new QHBoxLayout();
    showartistsbtn  = new QPushButton("Artists", this);
    showplaylistsbtn = new QPushButton("Playlists", this);
    navLayout->addWidget(showartistsbtn);
    navLayout->addWidget(showplaylistsbtn);
    mainLayout->addLayout(navLayout);

    stack = new QStackedWidget(this);
    mainLayout->addWidget(stack);

    artistsPage = new QWidget();
    auto* apLayout = new QVBoxLayout(artistsPage);
    artistlist = new QListWidget();
    apLayout->addWidget(new QLabel("Artists:"));
    apLayout->addWidget(artistlist);
    stack->addWidget(artistsPage);

    artistDetailPage = new QWidget();
    auto* adLayout = new QVBoxLayout(artistDetailPage);
    auto* backFromArtist = new QPushButton("← Back");
    artistnamelabel = new QLabel();
    albumlist = new QListWidget();
    albumsonglist = new QListWidget();
    addtoplaylistbtn = new QPushButton("Add to Playlist");
    likesonginartistbtn = new QPushButton("Like");
    auto* artistActLayout = new QHBoxLayout();
    artistActLayout->addWidget(addtoplaylistbtn);
    artistActLayout->addWidget(likesonginartistbtn);
    adLayout->addWidget(backFromArtist);
    adLayout->addWidget(artistnamelabel);
    adLayout->addWidget(new QLabel("Albums:"));
    adLayout->addWidget(albumlist);
    adLayout->addWidget(new QLabel("Songs:"));
    adLayout->addWidget(albumsonglist);
    adLayout->addLayout(artistActLayout);
    stack->addWidget(artistDetailPage);

    playlistsPage = new QWidget();
    auto* ppLayout = new QVBoxLayout(playlistsPage);
    playlistlist = new QListWidget();
    createplaylistbtn = new QPushButton("Create Playlist");
    deleteplaylistbtn = new QPushButton("Delete Playlist");
    editplaylistbtn   = new QPushButton("Edit Playlist");
    auto* plActLayout = new QHBoxLayout();
    plActLayout->addWidget(createplaylistbtn);
    plActLayout->addWidget(editplaylistbtn);
    plActLayout->addWidget(deleteplaylistbtn);
    ppLayout->addWidget(new QLabel("Playlists:"));
    ppLayout->addWidget(playlistlist);
    ppLayout->addLayout(plActLayout);
    stack->addWidget(playlistsPage);

    playlistDetailPage = new QWidget();
    auto* pdLayout = new QVBoxLayout(playlistDetailPage);
    auto* backFromPlaylist = new QPushButton("← Back");
    playlistnamelabel = new QLabel();
    playlistsonglist = new QListWidget();
    removesongbtn = new QPushButton("Remove Song");
    pdLayout->addWidget(backFromPlaylist);
    pdLayout->addWidget(playlistnamelabel);
    pdLayout->addWidget(new QLabel("Songs:"));
    pdLayout->addWidget(playlistsonglist);
    pdLayout->addWidget(removesongbtn);
    stack->addWidget(playlistDetailPage);

    // Connections
    connect(showartistsbtn,  &QPushButton::clicked, this, &ListenerPanel::showArtistsPage);
    connect(showplaylistsbtn, &QPushButton::clicked, this, &ListenerPanel::showPlaylistsPage);
    connect(backFromArtist,  &QPushButton::clicked, this, [this]{ stack->setCurrentWidget(artistsPage); });
    connect(backFromPlaylist, &QPushButton::clicked, this, [this]{ stack->setCurrentWidget(playlistsPage); });

    connect(artistlist, &QListWidget::itemClicked, this, &ListenerPanel::onArtistSelected);
    connect(albumlist, &QListWidget::itemClicked, this, &ListenerPanel::onAlbumSelected);
    connect(addtoplaylistbtn, &QPushButton::clicked, this, &ListenerPanel::addSelectedSongToPlaylist);
    connect(likesonginartistbtn, &QPushButton::clicked, this, &ListenerPanel::likeSelectedSong);
    connect(createplaylistbtn, &QPushButton::clicked, this, &ListenerPanel::createPlaylist);
    connect(deleteplaylistbtn, &QPushButton::clicked, this, &ListenerPanel::deletePlaylist);
    connect(editplaylistbtn, &QPushButton::clicked, this, &ListenerPanel::editPlaylist);
    connect(playlistlist, &QListWidget::itemClicked, this, &ListenerPanel::openPlaylistDetail);
    connect(removesongbtn, &QPushButton::clicked, this, &ListenerPanel::removeSelectedSongFromPlaylist);

    showArtistsPage();
}

void ListenerPanel::showArtistsPage() {
    refreshArtists();
    stack->setCurrentWidget(artistsPage);
}

void ListenerPanel::showPlaylistsPage() {
    refreshPlaylists();
    stack->setCurrentWidget(playlistsPage);
}

void ListenerPanel::refreshArtists() {
    artistlist->clear();
    for (auto& a : listenerservice.getAllArtists()) {
        auto* item = new QListWidgetItem(QString::fromStdString(a.fullname));
        item->setData(Qt::UserRole, a.id);
        artistlist->addItem(item);
    }
}

void ListenerPanel::onArtistSelected(QListWidgetItem* item) {
    selectedArtistId = item->data(Qt::UserRole).toInt();
    artistnamelabel->setText(item->text());
    refreshArtistAlbums();
    albumsonglist->clear();
    stack->setCurrentWidget(artistDetailPage);
}

void ListenerPanel::refreshArtistAlbums() {
    albumlist->clear();
    auto* singles = new QListWidgetItem("Singles");
    singles->setData(Qt::UserRole, 0);
    albumlist->addItem(singles);
    for (auto& a : listenerservice.getArtistAlbums(selectedArtistId)) {
        auto* item = new QListWidgetItem(QString::fromStdString(a.albumname));
        item->setData(Qt::UserRole, a.albumid);
        albumlist->addItem(item);
    }
}

void ListenerPanel::onAlbumSelected(QListWidgetItem* item) {
    int albumId = item->data(Qt::UserRole).toInt();
    albumsonglist->clear();
    vector<Song> songs = (albumId == 0)
                             ? listenerservice.getSingles(selectedArtistId)
                             : listenerservice.getAlbumSongs(albumId);
    for (auto& s : songs) {
        auto* si = new QListWidgetItem(QString::fromStdString(s.songname));
        si->setData(Qt::UserRole, s.songid);
        albumsonglist->addItem(si);
    }
}

void ListenerPanel::addSelectedSongToPlaylist() {
    auto* songItem = albumsonglist->currentItem();
    if (!songItem) return;
    int songId = songItem->data(Qt::UserRole).toInt();

    auto playlists = listenerservice.getPlaylists(currentlistener.id);
    if (playlists.empty()) { QMessageBox::information(this, "Info", "No playlists available."); return; }

    QStringList names;
    for (auto& p : playlists) names << QString::fromStdString(p.playlistname);
    bool ok;
    QString chosen = QInputDialog::getItem(this, "Add to Playlist", "Select playlist:", names, 0, false, &ok);
    if (!ok) return;
    for (auto& p : playlists) {
        if (p.playlistname == chosen.toStdString()) {
            listenerservice.addSongToPlaylist(p.playlistid, songId);
            break;
        }
    }
}

void ListenerPanel::likeSelectedSong() {
    auto* songItem = albumsonglist->currentItem();
    if (!songItem) return;
    int songId = songItem->data(Qt::UserRole).toInt();
    if (listenerservice.isLiked(currentlistener.id, songId)) {
        listenerservice.unlikeSong(currentlistener.id, songId);
        auto fav = listenerservice.getFavoritePlaylist(currentlistener.id);
        if (fav) listenerservice.removeSongFromPlaylist(fav->playlistid, songId);
        likesonginartistbtn->setText("Like");
    } else {
        listenerservice.likeSong(currentlistener.id, songId);
        auto fav = listenerservice.getFavoritePlaylist(currentlistener.id);
        if (fav) listenerservice.addSongToPlaylist(fav->playlistid, songId);
        likesonginartistbtn->setText("Unlike");
    }
}

void ListenerPanel::refreshPlaylists() {
    playlistlist->clear();
    for (auto& p : listenerservice.getPlaylists(currentlistener.id)) {
        auto* item = new QListWidgetItem(QString::fromStdString(p.playlistname));
        item->setData(Qt::UserRole, p.playlistid);
        playlistlist->addItem(item);
    }
}

void ListenerPanel::createPlaylist() {
    bool ok;
    QString name = QInputDialog::getText(this, "New Playlist", "Playlist name:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;
    string n = name.toStdString();
    listenerservice.createPlaylist(currentlistener.id, n);
    refreshPlaylists();
}

void ListenerPanel::deletePlaylist() {
    auto* item = playlistlist->currentItem();
    if (!item) return;
    int pid = item->data(Qt::UserRole).toInt();
    auto fav = listenerservice.getFavoritePlaylist(currentlistener.id);
    if (fav && fav->playlistid == pid) {
        QMessageBox::warning(this, "Error", "Cannot delete Favorite Songs playlist.");
        return;
    }
    listenerservice.deletePlaylist(pid);
    refreshPlaylists();
}

void ListenerPanel::editPlaylist() {
    auto* item = playlistlist->currentItem();
    if (!item) return;
    int pid = item->data(Qt::UserRole).toInt();
    auto fav = listenerservice.getFavoritePlaylist(currentlistener.id);
    if (fav && fav->playlistid == pid) {
        QMessageBox::warning(this, "Error", "Cannot rename Favorite Songs playlist.");
        return;
    }
    bool ok;
    QString name = QInputDialog::getText(this, "Rename Playlist", "New name:", QLineEdit::Normal, item->text(), &ok);
    if (!ok || name.isEmpty()) return;
    auto playlists = listenerservice.getPlaylists(currentlistener.id);
    for (auto& p : playlists) {
        if (p.playlistid == pid) {
            p.playlistname = name.toStdString();
            listenerservice.updatePlaylist(p);
            break;
        }
    }
    refreshPlaylists();
}

void ListenerPanel::openPlaylistDetail(QListWidgetItem* item) {
    selectedPlaylistId = item->data(Qt::UserRole).toInt();
    playlistnamelabel->setText(item->text());
    refreshPlaylistSongs();
    stack->setCurrentWidget(playlistDetailPage);
}

void ListenerPanel::refreshPlaylistSongs() {
    playlistsonglist->clear();
    for (auto& s : listenerservice.getPlaylistSongs(selectedPlaylistId)) {
        auto* item = new QListWidgetItem(QString::fromStdString(s.songname));
        item->setData(Qt::UserRole, s.songid);
        playlistsonglist->addItem(item);
    }
}

void ListenerPanel::removeSelectedSongFromPlaylist() {
    auto* item = playlistsonglist->currentItem();
    if (!item) return;
    int songId = item->data(Qt::UserRole).toInt();
    listenerservice.removeSongFromPlaylist(selectedPlaylistId, songId);
    auto fav = listenerservice.getFavoritePlaylist(currentlistener.id);
    if (fav && fav->playlistid == selectedPlaylistId)
        listenerservice.unlikeSong(currentlistener.id, songId);
    refreshPlaylistSongs();
}