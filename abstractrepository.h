#ifndef ABSTRACTREPOSITORY_H
#define ABSTRACTREPOSITORY_H
using namespace std;
#include <QObject>

class AbstractRepository
{
    Q_OBJECT
protected:
    virtual string Save()=0;
    virtual string remove()=0;
    virtual string search()=0;
public:
    AbstractRepository();
};

#endif // ABSTRACTREPOSITORY_H
