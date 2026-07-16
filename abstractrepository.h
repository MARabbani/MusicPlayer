#pragma once
#include <optional>
using namespace std;
template <class T>
class AbstractRepository
{
public:
    virtual ~AbstractRepository()=default;
    virtual int save(T& ent)=0;
    virtual bool remove(int id)=0;
    virtual optional<T> search(int id)=0;
};
