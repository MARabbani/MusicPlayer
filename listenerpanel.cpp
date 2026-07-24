#include "listenerpanel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QDialog>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <algorithm>

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
    auto* adBackBtn = new QPushButton("Back", artistDetailPage);
    artistnamelabel = new QLabel(artistDetailPage);
    adLayout->addWidget(adBackBtn);
    adLayout->addWidget(artistnamelabel);

    adLayout->addWidget(new QLabel("Albums:"));
    albumlist = new QListWidget(artistDetailPage);
    adLayout->addWidget(albumlist);
    auto* artistFilterLayout = new QHBoxLayout();
    artistSongSearch = new QLineEdit(artistDetailPage);
    artistSongSearch->setPlaceholderText("Search by name...");
    artistGenreFilter = new QComboBox(artistDetailPage);
    artistGenreFilter->addItem("All Genres");
    artistYearFilter = new QSpinBox(artistDetailPage);
    artistYearFilter->setRange(0, 2100);
    artistYearFilter->setSpecialValueText("Any Year");
    artistSortCombo = new QComboBox(artistDetailPage);
    artistSortCombo->addItem("Default");
    artistSortCombo->addItem("Name Asc");
    artistSortCombo->addItem("Name Desc");
    artistSortCombo->addItem("Year Asc");
    artistSortCombo->addItem("Year Desc");
    artistFilterLayout->addWidget(artistSongSearch);
    artistFilterLayout->addWidget(artistGenreFilter);
    artistFilterLayout->addWidget(artistYearFilter);
    artistFilterLayout->addWidget(artistSortCombo);

    adLayout->addWidget(new QLabel("Songs:"));
    adLayout->addLayout(artistFilterLayout);
    albumsonglist = new QListWidget(artistDetailPage);
    adLayout->addWidget(albumsonglist);

    auto* adBtnLayout = new QHBoxLayout();
    addtoplaylistbtn = new QPushButton("Add to Playlist", artistDetailPage);
    likesonginartistbtn = new QPushButton("Like", artistDetailPage);
    adBtnLayout->addWidget(addtoplaylistbtn);
    adBtnLayout->addWidget(likesonginartistbtn);
    adLayout->addLayout(adBtnLayout);
    stack->addWidget(artistDetailPage);
    connect(adBackBtn, &QPushButton::clicked, this, &ListenerPanel::showArtistsPage);

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
    ppLayout->addWidget(playlistlist);
    auto* plBtnLayout = new QHBoxLayout();
    createplaylistbtn = new QPushButton("Create",playlistsPage);
    deleteplaylistbtn = new QPushButton("Delete", playlistsPage);
    editplaylistbtn   = new QPushButton("Edit", playlistsPage);
    auto* plActLayout = new QHBoxLayout();
    plActLayout->addWidget(createplaylistbtn);
    plActLayout->addWidget(editplaylistbtn);
    plActLayout->addWidget(deleteplaylistbtn);
    ppLayout->addWidget(new QLabel("Playlists:"));
    ppLayout->addLayout(plBtnLayout);
    stack->addWidget(playlistsPage);

    ppLayout->addLayout(plActLayout);
    stack->addWidget(playlistsPage);

    playlistDetailPage = new QWidget();
    auto* pdLayout = new QVBoxLayout(playlistDetailPage);
    auto* backFromPlaylist = new QPushButton("Back", playlistDetailPage);
    playlistnamelabel = new QLabel();
    playlistsonglist = new QListWidget();
    removesongbtn = new QPushButton("Remove Song");
    pdLayout->addWidget(backFromPlaylist);
    pdLayout->addWidget(playlistnamelabel);
    pdLayout->addWidget(new QLabel("Songs:"));
    pdLayout->addWidget(playlistsonglist);
    pdLayout->addWidget(removesongbtn);
    stack->addWidget(playlistDetailPage);
    auto* plFilterLayout = new QHBoxLayout();
    playlistSongSearch = new QLineEdit(playlistDetailPage);
    playlistSongSearch->setPlaceholderText("Search by name...");
    playlistGenreFilter = new QComboBox(playlistDetailPage);
    playlistGenreFilter->addItem("All Genres");
    playlistYearFilter = new QSpinBox(playlistDetailPage);
    playlistYearFilter->setRange(0, 2100);
    playlistYearFilter->setSpecialValueText("Any Year");
    playlistSortCombo = new QComboBox(playlistDetailPage);
    playlistSortCombo->addItem("Default");
    playlistSortCombo->addItem("Name Asc");
    playlistSortCombo->addItem("Name Desc");
    playlistSortCombo->addItem("Year Asc");
    playlistSortCombo->addItem("Year Desc");
    plFilterLayout->addWidget(playlistSongSearch);
    plFilterLayout->addWidget(playlistGenreFilter);
    plFilterLayout->addWidget(playlistYearFilter);
    plFilterLayout->addWidget(playlistSortCombo);

    pdLayout->addWidget(new QLabel("Songs:"));
    pdLayout->addLayout(plFilterLayout);
    playlistsonglist = new QListWidget(playlistDetailPage);
    pdLayout->addWidget(playlistsonglist);
    removesongbtn = new QPushButton("Remove Song", playlistDetailPage);
    pdLayout->addWidget(removesongbtn);
    stack->addWidget(playlistDetailPage);
    connect(backFromPlaylist, &QPushButton::clicked, this, &ListenerPanel::showPlaylistsPage);


    auto* accLayout = new QHBoxLayout();
    editAccountBtn   = new QPushButton("Edit Account",this);
    deleteAccountBtn = new QPushButton("Delete Account", this);
    accLayout->addWidget(editAccountBtn);
    accLayout->addWidget(deleteAccountBtn);
    mainLayout->addLayout(accLayout);

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

    connect(artistSongSearch,&QLineEdit::textChanged,this, &ListenerPanel::applyArtistSongFilter);
    connect(artistGenreFilter, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ListenerPanel::applyArtistSongFilter);
    connect(artistYearFilter, QOverload<int>::of(&QSpinBox::valueChanged), this, &ListenerPanel::applyArtistSongFilter);
    connect(artistSortCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ListenerPanel::applyArtistSongFilter);

    connect(playlistSongSearch, &QLineEdit::textChanged,this, &ListenerPanel::applyPlaylistSongFilter);
    connect(playlistGenreFilter, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ListenerPanel::applyPlaylistSongFilter);
    connect(playlistYearFilter, QOverload<int>::of(&QSpinBox::valueChanged),this, &ListenerPanel::applyPlaylistSongFilter);
    connect(playlistSortCombo,QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ListenerPanel::applyPlaylistSongFilter);

    connect(editAccountBtn,&QPushButton::clicked, this, &ListenerPanel::editAccount);
    connect(deleteAccountBtn, &QPushButton::clicked,this, &ListenerPanel::deleteAccount);


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
    auto albums = listenerservice.getArtistAlbums(selectedArtistId);
    std::sort(albums.begin(), albums.end(),
              [](const Album& a, const Album& b){ return a.albumname < b.albumname; });
    albumlist->clear();
    auto* singles = new QListWidgetItem("Singles");
    singles->setData(Qt::UserRole, 0);
    albumlist->addItem(singles);
    for (auto& a : albums) {
        auto* item = new QListWidgetItem(QString::fromStdString(a.albumname));
        item->setData(Qt::UserRole, a.albumid);
        albumlist->addItem(item);
    }
}
void ListenerPanel::onAlbumSelected(QListWidgetItem* item) {
    int albumId = item->data(Qt::UserRole).toInt();
    currentArtistSongs = (albumId == 0)
                             ? listenerservice.getSingles(selectedArtistId)
                             : listenerservice.getAlbumSongs(albumId);
    artistGenreFilter->clear();
    artistGenreFilter->addItem("All Genres");
    for (auto& s : currentArtistSongs) {
        QString g = QString::fromStdString(s.genre);
        if (artistGenreFilter->findText(g) == -1)
            artistGenreFilter->addItem(g);
    }
    applyArtistSongFilter();
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
    auto playlists = listenerservice.getPlaylists(currentlistener.id);
    std::sort(playlists.begin(), playlists.end(),
              [](const PlayList& a, const PlayList& b){ return a.playlistname < b.playlistname; });
    playlistlist->clear();
    for (auto& p : playlists) {
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
    currentPlaylistSongs = listenerservice.getPlaylistSongs(selectedPlaylistId);
    playlistGenreFilter->clear();
    playlistGenreFilter->addItem("All Genres");
    for (auto& s : currentPlaylistSongs) {
        QString g = QString::fromStdString(s.genre);
        if (playlistGenreFilter->findText(g) == -1)
            playlistGenreFilter->addItem(g);
    }
    applyPlaylistSongFilter();
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



static void applyFilterToList(QListWidget* list,
                              std::vector<Song> songs,
                              const QString& search,
                              const QString& genre,
                              int year,
                              const QString& sort)
{
    // Filter
    if (!search.isEmpty())
        songs.erase(std::remove_if(songs.begin(), songs.end(), [&](const Song& s){
                        return !QString::fromStdString(s.songname).contains(search, Qt::CaseInsensitive);
                    }), songs.end());

    if (genre != "All Genres")
        songs.erase(std::remove_if(songs.begin(), songs.end(), [&](const Song& s){
                        return QString::fromStdString(s.genre) != genre;
                    }), songs.end());

    if (year != 0)
        songs.erase(std::remove_if(songs.begin(), songs.end(), [&](const Song& s){
                        return s.releaseyear != year;
                    }), songs.end());

    // Sort
    if (sort == "Name Asc")
        std::sort(songs.begin(), songs.end(), [](const Song& a, const Song& b){ return a.songname < b.songname; });
    else if (sort == "Name Desc")
        std::sort(songs.begin(), songs.end(), [](const Song& a, const Song& b){ return a.songname > b.songname; });
    else if (sort == "Year Asc")
        std::sort(songs.begin(), songs.end(), [](const Song& a, const Song& b){ return a.releaseyear < b.releaseyear; });
    else if (sort == "Year Desc")
        std::sort(songs.begin(), songs.end(), [](const Song& a, const Song& b){ return a.releaseyear > b.releaseyear; });

    list->clear();
    for (auto& s : songs) {
        auto* item = new QListWidgetItem(QString::fromStdString(s.songname));
        item->setData(Qt::UserRole, s.songid);
        list->addItem(item);
    }
}

void ListenerPanel::applyArtistSongFilter() {
    applyFilterToList(albumsonglist, currentArtistSongs,
                      artistSongSearch->text(),
                      artistGenreFilter->currentText(),
                      artistYearFilter->value(),
                      artistSortCombo->currentText());
}

void ListenerPanel::applyPlaylistSongFilter() {
    applyFilterToList(playlistsonglist, currentPlaylistSongs,
                      playlistSongSearch->text(),
                      playlistGenreFilter->currentText(),
                      playlistYearFilter->value(),
                      playlistSortCombo->currentText());
}

void ListenerPanel::editAccount() {
    bool ok;
    QString newUsername = QInputDialog::getText(this, "Edit Account", "New username:", QLineEdit::Normal,
                                                QString::fromStdString(currentlistener.username), &ok);
    if (!ok || newUsername.trimmed().isEmpty()) return;

    QString newPassword = QInputDialog::getText(this, "Edit Account", "New password:", QLineEdit::Password, "", &ok);
    if (!ok) return;

    currentlistener.username = newUsername.toStdString();
    if (!newPassword.isEmpty())
        currentlistener.password = newPassword.toStdString();
    listenerservice.updateAccount(currentlistener);
    QMessageBox::information(this, "Success", "Account updated.");
}

void ListenerPanel::deleteAccount() {
    auto reply = QMessageBox::question(this, "Delete Account",
                                       "Are you sure you want to delete your account?",
                                       QMessageBox::Yes | QMessageBox::No);
    if (reply != QMessageBox::Yes) return;
    listenerservice.deleteAccount(currentlistener.id);
    emit accountDeleted();
}
