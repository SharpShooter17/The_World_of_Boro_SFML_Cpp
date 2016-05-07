#include "Player.h"

Player::Player(sf::Texture *pludz, sf::Sprite *pGRACZ)
{
    ludzik = pludz;
    GRACZ = pGRACZ;
    GRACZ->setTexture(*pludz);
    GRACZ->setPosition(100,100);
    bJump = false;
    ilePixeliSkoczyl = 0.0f;
    zmianaTextury = SizeKafelka;
}
