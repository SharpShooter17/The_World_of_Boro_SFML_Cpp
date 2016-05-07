#include "Award.h"

cAward::cAward(sf::Sprite *tmp)
{
    Nagroda = *tmp;
}

void cAward::RysujNagrode(sf::RenderWindow & app, int lewo, int prawo)
{
    if ( getAwardX() >= lewo && getAwardX() <= prawo )
    app.draw(Nagroda);
}
