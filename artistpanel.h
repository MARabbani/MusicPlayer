#pragma once
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include "ArtistService.h"

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
    QLineEdit* searchEdit;
    QComboBox* sortCombo;
    QComboBox* genreFilter;
    QSpinBox* yearFilter;
    QPushButton* editAccountBtn;
    QPushButton* deleteAccountBtn;
    vector<Song> currentSongs;

public:
    ArtistPanel(Account artist,ArtistService& service,QWidget* parent=nullptr);
signals:
    void accountDeleted();

private slots:
    void refreshAlbums();
    void refreshSongs(int albumId);
    void applyFilter();
    void editAccount();
    void deleteAccount();
};