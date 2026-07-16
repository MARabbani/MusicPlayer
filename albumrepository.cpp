#include "albumrepository.h"

int AlbumRepository::save(Album& album) {
    Album a = album;
    if (a.albumid==0) a.albumid=nextid++;
    data[a.albumid] = a;
    return a.albumid;
}
bool AlbumRepository::remove(int id) {
    return data.erase(id)>0;
}
optional<Album> AlbumRepository::search(int id)  {
    auto it=data.find(id);
    if (it!=data.end()) {return it->second;}
    return nullopt;
}
