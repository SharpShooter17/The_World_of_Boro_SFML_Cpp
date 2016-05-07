#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "naglowki.h"

class Player
{
private:
    sf::Texture *ludzik;
    sf::Sprite *GRACZ;

    bool bJump;
    float ilePixeliSkoczyl;

    int zmianaTextury;
public:
    Player(sf::Texture *pludz, sf::Sprite *pGRACZ);

    void RysujPeda(sf::RenderWindow & app) { app.draw(*GRACZ); }

    inline void down() { GRACZ->setPosition(GRACZ->getPosition().x, GRACZ->getPosition().y+RuchGracza); }
    inline void up() { GRACZ->setPosition(GRACZ->getPosition().x, GRACZ->getPosition().y-SkokGracza); }
    inline void left() { GRACZ->setPosition(GRACZ->getPosition().x-RuchGracza, GRACZ->getPosition().y); }
    inline void right() {GRACZ->setPosition(GRACZ->getPosition().x+RuchGracza, GRACZ->getPosition().y); }
    inline void JumpOn() {bJump = true; }
    inline void JumpOff() { bJump = false; }
    inline bool getJump() { return bJump; }
    inline void addPixelJump(float ile) { ilePixeliSkoczyl += ile; }
    inline void resetPixelJump () { ilePixeliSkoczyl = 0.0f; }
    inline float getPixelJump() { return ilePixeliSkoczyl; }
    inline void grawitacja() { GRACZ->setPosition(GRACZ->getPosition().x, GRACZ->getPosition().y+Grawitacja);  }
    inline void ZmianaTeksturyReset() {  zmianaTextury = 0; }
    inline void addZmianaTextury() { zmianaTextury +=1; }
    inline int getZmianaTextury() { return zmianaTextury; }
};

#endif // PLAYER_H_INCLUDED
