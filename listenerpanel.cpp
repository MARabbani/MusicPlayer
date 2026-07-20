#include "listenerpanel.h"
#include <QVBoxLayout>

ListenerPanel::ListenerPanel(Account listener, ListenerService& service, QWidget* parent)
    : QWidget(parent),
    currentlistener(listener),
    listenerservice(service)
{
    playlistlist = new QListWidget(this);
    songlist = new QListWidget(this);
    searchedit = new QLineEdit(this);

    auto* layout = new QVBoxLayout(this);
    layout->addWidget(searchedit);
    layout->addWidget(playlistlist);
    layout->addWidget(songlist);

    refreshPlaylists();

}

void ListenerPanel::refreshPlaylists() {
    playlistlist->clear();
    playlistlist->addItem("Songs Favorite");

    for (auto& p : listenerservice.getPlaylists(currentlistener.id)) {
        playlistlist->addItem(QString::fromStdString(p.playlistname));
    }
}
