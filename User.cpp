#include "User.h"

cUser::cUser()
{
    std::ifstream fin("konfiguracja/user.dat");

    if ( fin.is_open())
    {
        fin >> name;
    }
    else
    {
        name = "Nickname";
    }
}

void cUser::Zapisz(std::string *str)
{
    std::fstream fout("konfiguracja/user.dat");

    fout << *str;

    fout.close();
}
