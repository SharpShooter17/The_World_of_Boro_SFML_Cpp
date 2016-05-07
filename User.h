#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include "naglowki.h"

class cUser
{
private:

    std::string name;

public:
    cUser();
    void Zapisz(std::string *str);
    inline const std::string getNick() { return name;  }
};

#endif // USER_H_INCLUDED
