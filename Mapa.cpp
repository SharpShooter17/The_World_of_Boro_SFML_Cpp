#include "Mapa.h"

cMapa::cMapa(std::vector<cEnemy> *pp0,
             sf::Texture *pp1,
             sf::Texture *pp2,
             sf::Texture *pp3,
             sf::Texture *pp4,
             sf::Texture *pp5,
             sf::Texture *pp6,
             std::vector<cAward> *pp7,
             sf::Texture *pp8,
             sf::Texture *pp9)
{

    std::ifstream fin("konfiguracja/mapy.txt");

    while (fin.good())
    {
        std::string tmp;
        fin >> tmp;
        numer_mapy.push_back(tmp);
    }

    fin.close();

    MaxLevel = numer_mapy.size();

    level = 0;

    p0 = pp0;
    p1 = pp1;
    p2 = pp2;
    p3 = pp3;
    p4 = pp4;
    p5 = pp5;
    p6 = pp6;
    p7 = pp7;
    p8 = pp8;
    p9 = pp9;
}

void cMapa::NowaMapa()
{

    Mapa.clear();

    std::ifstream FileMap;
    FileMap.open( numer_mapy[level].c_str() );

    int x = 0;
    int y = 0;
    int kafelek;

    std::vector<MAPA_ID> temporary;

    FileMap >> map_height;
    FileMap >> map_width;

    for (int j = 0; FileMap.good() ; ++j )
    {
        FileMap >> kafelek;

        MAPA_ID TEMPORARY;

        switch(kafelek)
        {
        case trawa:
            TEMPORARY.Spr.setTexture(*p5);
            TEMPORARY.Spr.setPosition(y*p5->getSize().x, x*p5->getSize().y);
            TEMPORARY.przedmiot = ziemia;
            temporary.push_back(TEMPORARY);
            break;
        case wrog:
        {
            sf::Sprite tmp;
            tmp.setTexture(*p4);
            tmp.setPosition(y*p4->getSize().x, x*p4->getSize().y);
            cEnemy TEMP(&tmp);
            p0->push_back(TEMP);
            TEMPORARY.Spr.setTexture(*p3);
            TEMPORARY.Spr.setPosition(y*p3->getSize().x, x*p3->getSize().y);
            TEMPORARY.przedmiot = niebo;
            temporary.push_back(TEMPORARY);
            break;
        }
        case niebo:
            TEMPORARY.Spr.setTexture(*p3);
            TEMPORARY.Spr.setPosition(y*p3->getSize().x, x*p3->getSize().y);
            TEMPORARY.przedmiot = niebo;
            temporary.push_back(TEMPORARY);
            break;
        case ziemia:
            TEMPORARY.Spr.setTexture(*p1);
            TEMPORARY.Spr.setPosition(y*p1->getSize().x, x*p1->getSize().y);
            TEMPORARY.przedmiot = ziemia;
            temporary.push_back(TEMPORARY);
            break;
        case woda:
            TEMPORARY.Spr.setTexture(*p2);
            TEMPORARY.Spr.setPosition(y*p2->getSize().x, x*p2->getSize().y);
            TEMPORARY.przedmiot = woda;
            temporary.push_back(TEMPORARY);
            break;
        case skala:
            TEMPORARY.Spr.setTexture(*p6);
            TEMPORARY.Spr.setPosition(y*p6->getSize().x, x*p6->getSize().y);
            TEMPORARY.przedmiot = ziemia;
            temporary.push_back(TEMPORARY);
            break;
        case nagroda:
        {
            sf::Sprite tmp;
            tmp.setTexture(*p8);
            tmp.setPosition(y*p8->getSize().x, x*p8->getSize().y);
            cAward TEMP(&tmp);
            p7->push_back(TEMP);
            TEMPORARY.Spr.setTexture(*p3);
            TEMPORARY.Spr.setPosition(y*p3->getSize().x, x*p3->getSize().y);
            TEMPORARY.przedmiot = niebo;
            temporary.push_back(TEMPORARY);
        }
        break;
        case drabinka:
            TEMPORARY.Spr.setTexture(*p9);
            TEMPORARY.Spr.setPosition(y*p9->getSize().x, x*p9->getSize().y);
            TEMPORARY.przedmiot = drabinka;
            temporary.push_back(TEMPORARY);
            break;
        default:
            TEMPORARY.Spr.setTexture(*p3);
            TEMPORARY.Spr.setPosition(y*p3->getSize().x, x*p3->getSize().y);
            TEMPORARY.przedmiot = niebo;
            temporary.push_back(TEMPORARY);
            break;
        }

        if ( y >= map_width-1 )
        {
            y = 0;
            ++x;
            Mapa.push_back(temporary);
            temporary.clear();
        }
        else
        {
            ++y;
        }
    }

    FileMap.close();
}

void cMapa::RysujMape(sf::RenderWindow & app, int lewy, int prawy, int gora, int dol)
{
    if (lewy < 0) lewy = 0; else lewy = lewy/SizeKafelka;
    if (gora < 0) gora = 0; else gora = gora/SizeKafelka;
    if (prawy > map_width * SizeKafelka) prawy = map_width; else  prawy = prawy/SizeKafelka;
    if (dol > map_height * SizeKafelka) dol = map_height; else dol = dol/SizeKafelka;

    for (int x = gora; x < dol; ++x)
    {
        for (int y = lewy; y < prawy; ++y)
        {
            app.draw(Mapa[x][y].Spr);
        }
    }
}

sf::Sprite cMapa::getSprite(float x, float y)
{
    return Mapa[static_cast<int>(x)/SizeKafelka][static_cast<int>(y)/SizeKafelka].Spr;
}
obiekt cMapa::getObiekt(float x, float y)
{
    return Mapa[static_cast<int>(x)/SizeKafelka][static_cast<int>(y)/SizeKafelka].przedmiot;
}
