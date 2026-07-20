#ifndef LISTENERPANEL_H
#define LISTENERPANEL_H
#pragma once
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include "ListenerService.h"

class ListenerPanel:public QWidget{
    Q_OBJECT
private:
    Account currentlistener;
    ListenerService& listenerservice;
    QListWidget* playlistlist;
    QListWidget* songlist;
    QLineEdit* searchedit;

public:
    explicit ListenerPanel(Account listener , ListenerService& service, QWidget* parent=nullptr);
private slots:
    void refreshPlaylists();
    // {
    //     playlistlist->clear();
    //     playlistlist->addItem("Songs Favorite");
    //     for (auto& p:listenerservice.getPlaylists(currentlistener.id))
    //         playlistlist->addItem(QString::fromStdString(p.playlistname));
    // }
};

#endif // LISTENERPANEL_H
