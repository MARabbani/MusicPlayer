#ifndef LISTENERPANEL_H
#define LISTENERPANEL_H
#pragma once
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include "ListenerService.h"

class ListenerPanel : public QWidget {
    Q_OBJECT
private:
    Account currentlistener;
    ListenerService& listenerservice;

    QStackedWidget* stack;

    QWidget* artistsPage;
    QListWidget* artistlist;

    QWidget* artistDetailPage;
    QLabel* artistnamelabel;
    QListWidget* albumlist;
    QListWidget* albumsonglist;
    QPushButton* addtoplaylistbtn;
    QPushButton* likesonginartistbtn;
    QLineEdit* artistSongSearch;
    QComboBox* artistGenreFilter;
    QSpinBox* artistYearFilter;
    QComboBox* artistSortCombo;
    std::vector<Song> currentArtistSongs;

    QWidget* playlistsPage;
    QListWidget* playlistlist;
    QPushButton* createplaylistbtn;
    QPushButton* deleteplaylistbtn;
    QPushButton* editplaylistbtn;

    QWidget* playlistDetailPage;
    QLabel* playlistnamelabel;
    QListWidget* playlistsonglist;
    QPushButton* removesongbtn;
    QLineEdit* playlistSongSearch;
    QComboBox* playlistGenreFilter;
    QSpinBox* playlistYearFilter;
    QComboBox* playlistSortCombo;
    std::vector<Song> currentPlaylistSongs;

    QPushButton* showartistsbtn;
    QPushButton* showplaylistsbtn;

    QPushButton* editAccountBtn;
    QPushButton* deleteAccountBtn;

    int selectedArtistId = 0;
    int selectedPlaylistId = 0;

public:
    explicit ListenerPanel(Account listener,ListenerService& service,QWidget* parent = nullptr);

signals:
    void accountDeleted();

private slots:
    void showArtistsPage();
    void showPlaylistsPage();
    void refreshArtists();
    void onArtistSelected(QListWidgetItem* item);
    void refreshArtistAlbums();
    void onAlbumSelected(QListWidgetItem* item);
    void addSelectedSongToPlaylist();
    void likeSelectedSong();
    void refreshPlaylists();
    void createPlaylist();
    void deletePlaylist();
    void openPlaylistDetail(QListWidgetItem* item);
    void refreshPlaylistSongs();
    void removeSelectedSongFromPlaylist();
    void editPlaylist();
    void applyArtistSongFilter();
    void applyPlaylistSongFilter();
    void editAccount();
    void deleteAccount();
};


#endif // LISTENERPANEL_H