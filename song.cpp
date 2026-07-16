#include "song.h"

Song::Song() {
    songname="";
    releaseyear=0;
    genre="";
    filename="";
    songid=0;
    artistid=0;
    albumid=0;
}
Song::Song(string songname, int releaseyear,string genre, string filename, int songid , int artistid,int albumid){
    this->songname= songname;
    this->releaseyear=releaseyear;
    this->genre= genre;
    this->filename= filename;
    this->songid= songid;
    this->artistid= artistid;
    this->albumid= albumid;
};

