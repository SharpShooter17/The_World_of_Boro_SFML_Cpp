#include "Enemy.h"

cEnemy::cEnemy(sf::Sprite *tmp)
{
    Enemy = *tmp;
    direct = 1;
}

void cEnemy::RysujWroga(sf::RenderWindow & app, int lewo,int prawo)
{
    if ( getEnemyX() >= lewo && getEnemyX() <= prawo )
        app.draw(Enemy);
}

void cEnemy::RuchWroga(cMapa *pCMAP)
{
    if ( pCMAP->getObiekt(getEnemyY()+SizeKafelka, getEnemyX()) != ziemia || ///nie ma ziemi pod soba
            pCMAP->getObiekt(getEnemyY() + SizeKafelka, getEnemyX() + SizeKafelka) != ziemia ||
            pCMAP->getObiekt(getEnemyY(), getEnemyX() - 1) == ziemia || ///uderzyl w ziemie
            pCMAP->getObiekt(getEnemyY(), getEnemyX()+SizeKafelka) == ziemia )
    {
        direct = -direct;
        if ( direct < 0)
        {
            Enemy.setOrigin(getEnemyWidth()/1.9,0);
            Enemy.setScale( sf::Vector2f( 1, 1 ) );
        }
        else
            Enemy.setScale( sf::Vector2f( -1, 1 ) );
    }

    Enemy.move(direct*SzybkoscWroga,0);
}
