#include "album.h"

Album::Album() {
    albumname="";
    albumid=0;
    artistid=0;
}

Album:: Album(string albumname,int albumid, int artistid){
    this->albumname=albumname;
    this->albumid=albumid;
    this->artistid=artistid;
};
