#ifndef LISTENERREPOSITORY_H
#define LISTENERREPOSITORY_H
#include "AccountRepository.h"
#include <vector>

class ListenerRepository: public AccountRepository
{
    unordered_map<int,vector<int>> likedsongs;
public:
    void updateLiked(int listenerd,int songid,bool val);
    bool isLiked(int listenerid,int songid);
};

#endif // LISTENERREPOSITORY_H
