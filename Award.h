#ifndef AWARD_H_INCLUDED
#define AWARD_H_INCLUDED

#include "naglowki.h"

class cAward
{
private:
    sf::Sprite Nagroda;
public:
    cAward(sf::Sprite *tmp);

    inline float getAwardX() { return Nagroda.getGlobalBounds().left; }
    inline float getAwardY() {  return Nagroda.getGlobalBounds().top; }
    inline float getAwardWidth() { return Nagroda.getGlobalBounds().width;  }
    inline float getAwardHeight() { return Nagroda.getGlobalBounds().height; }
    void RysujNagrode(sf::RenderWindow & app, int lewo,int prawo);

};

#endif // AWARD_H_INCLUDED
