#ifndef LISTENERREPOSITORY_H
#define LISTENERREPOSITORY_H
#include "AccountRepository.h"
#include <vector>

class ListenerRepository: public AccountRepository
{
    unordered_map<int,vector<int>> likedsongs;
public:
};

#endif // LISTENERREPOSITORY_H
