#ifndef ALBUMREPOSITORY_H
#define ALBUMREPOSITORY_H
#pragma once
#include "AbstractRepository.h"
#include "Album.h"
#include <unordered_map>
#include <vector>
using namespace std;

class AlbumRepository : public AbstractRepository<Album>
{
    unordered_map<int,Album> data;
    int nextid=1;
public:
    int save(Album& album) override;
    bool remove(int id) override ;
    optional<Album> search(int id) override;
    vector<Album> albums(int artistid);



};
#endif // ALBUMREPOSITORY_H
