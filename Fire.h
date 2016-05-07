#ifndef FIRE_H_INCLUDED
#define FIRE_H_INCLUDED

#include "naglowki.h"

class Fire
{
private:
    sf::Texture *Bullet;
    float x,y,direct;
public:
    Fire(float X, float Y, float kierunek, sf::Texture *pt);
    inline void fly() { x+=direct*SzybkoscPocisku; }
    void DrawBullet(sf::RenderWindow & app, int lewo,int prawo);
    inline float getX() { return x; }
    inline float getY() { return y; }
    inline float getWidth() { return Bullet->getSize().x;}
    inline float getHeight() { return Bullet->getSize().y;  }
    inline float getDirect() { return direct; }
    sf::Sprite getSprite();
};

#endif // FIRE_H_INCLUDED
