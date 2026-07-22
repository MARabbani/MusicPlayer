#ifndef ARTISTREPOSITORY_H
#define ARTISTREPOSITORY_H
#include "AccountRepository.h"
#include <vector>

class ArtistRepository : public AccountRepository
{
public:
    vector<Account> getAllArtists();
};

#endif // ARTISTREPOSITORY_H
