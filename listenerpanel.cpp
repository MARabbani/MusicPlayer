#include "listenerpanel.h"
#include <QVBoxLayout>
#include <QLineEdit>

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
    searchedit->setPlaceholderText("searching song...");

    refreshPlaylists();

connect(searchedit, &QLineEdit::textChanged, this, [this](const QString &text){
        if(songlist->count() == 0) return;
        for(int i = 0; i < songlist->count(); ++i) {
            QListWidgetItem* item = songlist->item(i);
            if(item->text().contains(text, Qt::CaseInsensitive)) {
                item->setHidden(false);
            } else {
                item->setHidden(true);
            }
        }
    });

}

void ListenerPanel::refreshPlaylists() {
    playlistlist->clear();
    playlistlist->addItem("Songs Favorite");

    for (auto& p : listenerservice.getPlaylists(currentlistener.id)) {
        playlistlist->addItem(QString::fromStdString(p.playlistname));
    }
}
