#include "listenerrepository.h"
#include <algorithm>

void ListenerRepository::updateLiked(int listenerid,int songid,bool val){
    auto& liked=likedsongs[listenerid];
    auto it =std::find(liked.begin(), liked.end(), songid);
    if(val && it==liked.end()) liked.push_back(songid);
    else if(!val && it!=liked.end()) liked.erase(it);

};
bool ListenerRepository::isLiked(int listenerid,int songid){
    auto it=likedsongs.find(listenerid);
    if (it==likedsongs.end()) return false;
    auto& liked=it->second;
    return std::find(liked.begin(),liked.end(),songid)!=liked.end();
};