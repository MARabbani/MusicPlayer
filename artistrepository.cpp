#include "artistrepository.h"

vector<Account> ArtistRepository::getAllArtists() {
    vector<Account> result;
    for (auto& [id, acc] : data)
        if (acc.role == Role::Artist) result.push_back(acc);
    return result;
}