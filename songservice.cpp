#include <algorithm>
#include "songservice.h"

vector<Song> SongService::searchByName(vector<Song> songs,string& query){
    vector<Song> result;
    for (auto& s:songs){
        if (s.songname.find(query)!=string::npos) result.push_back(s);
    }
    return result;
};
vector<Song> SongService::filterByGenre(vector<Song> songs,string& genre){
    vector<Song> result;
    for (auto& s :songs){
        if (s.genre==genre) result.push_back(s);
    }
    return result;
};
vector<Song> SongService::filterByYear(vector<Song> songs,int year){
    vector<Song> result;
    for (auto& s :songs){
        if (s.releaseyear==year) result.push_back(s);
    }
    return result;
};
void SongService::sortByName(vector<Song>& songs){
    sort(songs.begin(), songs.end(),[](Song& a,Song& b){return a.songname<b.songname;});
};
void SongService::sortByYear(vector<Song>& songs){
    std::sort(songs.begin(), songs.end(),[](Song& a,Song& b){return a.releaseyear<b.releaseyear;});
};