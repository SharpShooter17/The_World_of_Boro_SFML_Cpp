#ifndef NAGLOWKI_H_INCLUDED
#define NAGLOWKI_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <vector>
#include <sstream>
#include <ostream>

using namespace std;
enum obiekt {  niebo = 0,
               ziemia = 1,
               woda = 2,
               wrog = 3,
               trawa = 4,
               skala = 5,
               nagroda = 6,
               drabinka = 7
            };

struct MAPA_ID
{
    sf::Sprite Spr;
    obiekt przedmiot;
};

///----------zmienne---------///

extern float RuchGracza;
extern float SkokGracza;
extern float Grawitacja;
extern int SizeKafelka;
extern int IloscKafelekWidth;
extern int IloscKafelekHeight;
extern float SzybkoscWroga;
extern int Width;
extern int Height;
extern float SzybkoscPocisku;

///---------Funkcje----------///

bool MiniKolizja(float Obiekt1X,
                        float Obiekt1Y,
                        float Obiekt1Width,
                        float Obiekt1Height,
                        float Obiekt2X,
                        float Obiekt2Y,
                        float Obiekt2Width,
                        float Obiekt2Height);

#endif // NAGLOWKI_H_INCLUDED
