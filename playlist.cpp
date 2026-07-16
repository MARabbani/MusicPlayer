#include "playlist.h"

PlayList::PlayList() {
    playlistname="";
    listenerid=0;
    playlistid=0;
}

PlayList:: PlayList(string playlisttname, int listenerid,int playlistid){
    this->playlistname=playlisttname;
    this->listenerid=listenerid;
    this->playlistid=playlistid;
};

