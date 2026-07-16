#ifndef SONGREPOSITORY_H
#define SONGREPOSITORY_H
#pragma once
#include "AbstractRepository.h"
#include "Song.h"
#include <vector>
#include <unordered_map>
using namespace std;

class SongRepository:public AbstractRepository<Song>
{
    unordered_map<int,Song> data;
    int nextId=1;
public:
    int save(Song& song)override;
    bool remove(int id)override;
    optional<Song> search(int id)override;
};

#endif // SONGREPOSITORY_H
