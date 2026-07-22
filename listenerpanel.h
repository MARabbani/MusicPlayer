#ifndef LISTENERPANEL_H
#define LISTENERPANEL_H
#pragma once
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QLabel>
#include "ListenerService.h"

class ListenerPanel : public QWidget {
    Q_OBJECT
private:
    Account currentlistener;
    ListenerService& listenerservice;

    QStackedWidget* stack;

    // Artists view
    QWidget* artistsPage;
    QListWidget* artistlist;

    // Artist detail view
    QWidget* artistDetailPage;
    QLabel* artistnamelabel;
    QListWidget* albumlist;
    QListWidget* albumsonglist;
    QPushButton* addtoplaylistbtn;
    QPushButton* likesonginartistbtn;

    // Playlists view
    QWidget* playlistsPage;
    QListWidget* playlistlist;
    QPushButton* createplaylistbtn;
    QPushButton* deleteplaylistbtn;
    QPushButton* editplaylistbtn;

    // Playlist detail view
    QWidget* playlistDetailPage;
    QLabel* playlistnamelabel;
    QListWidget* playlistsonglist;
    QPushButton* removesongbtn;

    // Nav buttons
    QPushButton* showartistsbtn;
    QPushButton* showplaylistsbtn;

    int selectedArtistId = 0;
    int selectedPlaylistId = 0;

public:
    explicit ListenerPanel(Account listener, ListenerService& service, QWidget* parent = nullptr);

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
};

#endif // LISTENERPANEL_H