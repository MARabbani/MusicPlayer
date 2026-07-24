#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    AccountRepository accountrep;
    AlbumRepository albumrep;
    SongRepository songrep;
    PlaylistRepository playlistrep;
    ListenerRepository listenerrep;
    ArtistRepository artistrep;

    AuthService authService(accountrep);
    ArtistService artistService(albumrep, songrep, accountrep);
    ListenerService listenerService(playlistrep, songrep, listenerrep, artistrep, albumrep, accountrep);

    MainWindow w(authService, artistService, listenerService);
    w.show();

    return a.exec();
}
