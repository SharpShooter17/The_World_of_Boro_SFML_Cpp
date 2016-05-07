#include "Fire.h"

Fire::Fire(float X, float Y, float kierunek, sf::Texture *pt)
{
    Bullet = pt;
    x = X;
    y = Y;
    direct = kierunek;
}

void Fire::DrawBullet(sf::RenderWindow & app, int lewo,int prawo)
{

    if ( getX() >= lewo && getX() <= prawo ) {
    sf::Sprite tmp;
    tmp.setTexture(*Bullet);
    tmp.setPosition(x,y);
    app.draw(tmp);
    }
}

sf::Sprite Fire::getSprite()
{
    sf::Sprite tmp;
    tmp.setTexture(*Bullet);
    tmp.setPosition(x,y);
    return tmp;
}

