#include "listenerpanel.h"

ListenerPanel::ListenerPanel(Account listener, ListenerService& service, QWidget* parent)
    : QWidget(parent),
    currentlistener(listener),
    listenerservice(service)
{
    playlistlist = new QListWidget(this);
    songlist = new QListWidget(this);
    searchedit = new QLineEdit(this);

}

void ListenerPanel::refreshPlaylists() {
    playlistlist->clear();
    playlistlist->addItem("Songs Favorite");

    for (auto& p : listenerservice.getPlaylists(currentlistener.id)) {
        playlistlist->addItem(QString::fromStdString(p.playlistname));
    }
}
