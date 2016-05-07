#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "naglowki.h"
#include "Mapa.h"

class cMapa;

class cEnemy
{
private:
    sf::Sprite Enemy;
    float direct;
public:
    cEnemy(sf::Sprite *tmp);

    inline float getEnemyX() { return Enemy.getGlobalBounds().left; }
    inline float getEnemyY() { return Enemy.getGlobalBounds().top; }
    inline float getEnemyWidth() { return Enemy.getGlobalBounds().width; }
    inline float getEnemyHeight() { return Enemy.getGlobalBounds().height; }

    void RuchWroga(cMapa *pCMAP);
    void RysujWroga(sf::RenderWindow & app, int lewo,int prawo);

};

#endif // ENEMY_H_INCLUDED
