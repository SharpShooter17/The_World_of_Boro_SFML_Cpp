#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

#include "naglowki.h"
#include "Fire.h"
#include "Enemy.h"
#include "Award.h"

///0 - niebo
///1 - ziemia
///2 - woda
///3 - wrog
///4 - trawa
///5 - skala
///6 - nagroda
///7 drabina

class cEnemy;

class cMapa
{
private:
    int level;
    int MaxLevel;

    std::vector< std::vector < MAPA_ID > > Mapa;

    int map_width;
    int map_height;

    std::vector<cEnemy> *p0;
    sf::Texture *p1;
    sf::Texture *p2;
    sf::Texture *p3;
    sf::Texture *p4;
    sf::Texture *p5;
    sf::Texture *p6;
    std::vector<cAward> *p7;
    sf::Texture *p8;
    sf::Texture *p9;

    std::vector <std::string> numer_mapy;

public:
    cMapa(std::vector<cEnemy> *pp0,
          sf::Texture *pp1,
          sf::Texture *pp2,
          sf::Texture *pp3,
          sf::Texture *pp4,
          sf::Texture *pp5,
          sf::Texture *pp6,
          std::vector<cAward> *pp7,
          sf::Texture *pp8,
          sf::Texture *pp9);

    void RysujMape(sf::RenderWindow & app, int lewy, int prawy, int gora, int dol);
    sf::Sprite getSprite(float x, float y);
    obiekt getObiekt(float x, float y);
    int getSizeWidth() { return map_width-1;}
    int getSizeHeight() { return map_height-1;}
    inline void NextLevel() { ++level;}
    inline void ResetLevel() { level = 0; }
    inline int getLevel() { return level;}
    inline void setLevel(int x) { level = x; }
    inline int getMaxLevel() {  return MaxLevel; }
    void NowaMapa();
};

#endif // MAPA_H_INCLUDED
