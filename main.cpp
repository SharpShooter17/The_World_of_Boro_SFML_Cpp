#include "naglowki.h"
#include "Mapa.h"
#include "Player.h"
#include "Fire.h"
#include "Enemy.h"
#include "Award.h"
#include "Score.h"
#include "User.h"

///-----------Zmienne-------------///

extern float RuchGracza = 0.3;
extern float SkokGracza = 0.2;
extern float Grawitacja = 0.5;
extern float SzybkoscWroga = 0.2;
extern float SzybkoscPocisku = 0.7f;

float CoIleStrzal = 0.5f;
int CoIleZmianaTeksturyRuchu = 50;
extern int Width = 1024;
extern int Height = 760;

extern int SizeKafelka = 40;
extern int IloscKafelekWidth = 54;
extern int IloscKafelekHeight = 19;

std::string nickname;

int main()
{

///----------Kontenery----------///

    std::deque <Fire> Kule;
    std::vector <cEnemy> Przeciwnik;
    std::vector <cAward> Punkty;

///------------Tekstury-----------///

    sf::Texture tlo;
    if (!tlo.loadFromFile("graphics/tlo.png"))
        return EXIT_FAILURE;

    sf::Texture textziemia;
    if (!textziemia.loadFromFile("graphics/ziemia.png"))
        return EXIT_FAILURE;

    sf::Texture texttrawa;
    if (!texttrawa.loadFromFile("graphics/trawa.png"))
        return EXIT_FAILURE;

    sf::Texture textskala;
    if (!textskala.loadFromFile("graphics/skala.png"))
        return EXIT_FAILURE;

    sf::Texture Twoda;
    if (!Twoda.loadFromFile("graphics/woda.png"))
        return EXIT_FAILURE;

    sf::Texture textniebo;
    if (!textniebo.loadFromFile("graphics/niebo.bmp"))
        return EXIT_FAILURE;

    sf::Texture graczLeft;
    if (!graczLeft.loadFromFile("graphics/PlayerLeft.png"))
        return EXIT_FAILURE;

    sf::Texture graczRight;
    if (!graczRight.loadFromFile("graphics/PlayerRight.png"))
        return EXIT_FAILURE;

    sf::Texture graczLeft1;
    if (!graczLeft1.loadFromFile("graphics/PlayerLeft1.png"))
        return EXIT_FAILURE;

    sf::Texture graczRight1;
    if (!graczRight1.loadFromFile("graphics/PlayerRight1.png"))
        return EXIT_FAILURE;

    sf::Texture bullet;
    if (!bullet.loadFromFile("graphics/bullet.png"))
        return EXIT_FAILURE;

    sf::Texture Tenemy;
    if (!Tenemy.loadFromFile("graphics/enemy.png"))
        return EXIT_FAILURE;

    sf::Texture Taward;
    if (!Taward.loadFromFile("graphics/coin.png"))
        return EXIT_FAILURE;

    sf::Texture Tdrabina;
    if (!Tdrabina.loadFromFile("graphics/ladder.png"))
        return EXIT_FAILURE;

///----------Ikona-Gry-----------///

    sf::Image Ikona;
    Ikona.loadFromFile("graphics/icon.png");
    const unsigned char * Icon = Ikona.getPixelsPtr();

///-----------Sprity-------------///

    sf::Sprite pedzik;
    sf::Sprite TLO;
    TLO.setTexture(tlo);
    TLO.setScale( Width/tlo.getSize().x, Height/tlo.getSize().y );

///-----------Fonty-------------///

    sf::Font fPUNKTY;
    fPUNKTY.loadFromFile("fonts/comicbd.ttf");

///----------Timery-------------///

    ///Timer pocikow bohatera
    sf::Clock cFire;
    sf::Time FireGranica = sf::seconds(CoIleStrzal); /// co ile sekund wystrzal?
    sf::Time tFire = sf::Time::Zero;

    sf::Clock cSzybkoscGry;
    sf::Time tUstawSzybkosc = sf::seconds(1);
    sf::Time tSprawdz = sf::Time::Zero;


///-----------Klasy-------------///

    cMapa mapa(&Przeciwnik,
               &textziemia,
               &Twoda,
               &textniebo,
               &Tenemy,
               &texttrawa,
               &textskala,
               &Punkty,
               &Taward,
               &Tdrabina);

    Player ped(&graczRight1, &pedzik);
    cScore SCORE(&fPUNKTY);
    cUser User;

    nickname = User.getNick();

///----------Teksty------------///

///Start gry
    sf::Text StartGame;
    StartGame.setFont(fPUNKTY);
    StartGame.setString("Palenie zabija!");
    StartGame.setCharacterSize(40);
    StartGame.setColor(sf::Color::Green);
    StartGame.setPosition((Width/2 - StartGame.getLocalBounds().width/2), 150);

///wygrales!
    sf::Text YouWinYouLose;
    YouWinYouLose.setFont(fPUNKTY);
    YouWinYouLose.setString("Wygrales paczke fajek. Umrzesz!");
    YouWinYouLose.setCharacterSize(40);
    YouWinYouLose.setColor(sf::Color::Red);
    YouWinYouLose.setPosition((Width/2 - YouWinYouLose.getLocalBounds().width/2), Height/2);

///Nick
    sf::Text Nick;
    Nick.setFont(fPUNKTY);
    Nick.setString(nickname);
    Nick.setCharacterSize(40);
    Nick.setColor(sf::Color::Green);
    Nick.setPosition((Width/2 - Nick.getLocalBounds().width/2), 400);

///--------Okno gry-----------///

    sf::RenderWindow app(sf::VideoMode(Width, Height), "The World of Boro ;]");
    app.setIcon(32,32,Icon);

    sf::View widok(sf::FloatRect(0, 0, Width, Height));
    app.setView(widok);

///---------Kontrolki----------///

    bool bZmianaKierunu = true;
    bool bGAME = false;
    bool bWinLose = false;
    bool bMENU = true;
    bool bCzyProgramJestWlaczony = true;
    bool bPause = false;

///---------Petla programu-----///

    while (bCzyProgramJestWlaczony)
    {
        while (bMENU)
        {
            sf::Event event;
            while (app.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    bGAME = false;
                    bWinLose = false;
                    bMENU = false;
                    bCzyProgramJestWlaczony = false;
                    app.close();
                }

                ///zmiana koloru napisu Start gry
                if (sf::Mouse::getPosition(app).x > StartGame.getGlobalBounds().left &&
                        sf::Mouse::getPosition(app).y > StartGame.getGlobalBounds().top &&
                        sf::Mouse::getPosition(app).x < StartGame.getGlobalBounds().left + StartGame.getGlobalBounds().width &&
                        sf::Mouse::getPosition(app).y < StartGame.getGlobalBounds().top +  StartGame.getGlobalBounds().height)
                {
                    StartGame.setColor(sf::Color::Red);
                }
                else
                {
                    StartGame.setColor(sf::Color::Green);
                }

                ///Start Gry! :D
                if ( ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) &&
                        sf::Mouse::getPosition(app).x > StartGame.getGlobalBounds().left &&
                        sf::Mouse::getPosition(app).y > StartGame.getGlobalBounds().top &&
                        sf::Mouse::getPosition(app).x < StartGame.getGlobalBounds().left + StartGame.getGlobalBounds().width &&
                        sf::Mouse::getPosition(app).y < StartGame.getGlobalBounds().top +  StartGame.getGlobalBounds().height) )
                {
                    ///Ustawienie kontrolek
                    bGAME = true;
                    bWinLose = false;
                    bMENU = false;
                    bCzyProgramJestWlaczony = true;
                    ///reset kontenerow
                    Kule.clear();
                    Przeciwnik.clear();
                    Punkty.clear();
                    ///ustaw mape
                    mapa.NowaMapa();
                    pedzik.setPosition(100,100);
                    SCORE.resetPunkty();
                    SCORE.resetZycie();

                    ///-----------Ustawiam zmienne---///

                    IloscKafelekWidth = mapa.getSizeWidth();
                    IloscKafelekHeight = mapa.getSizeHeight();
                    SCORE.UstawMaXPUNKTOW(Punkty.size());
                    mapa.ResetLevel();
                }
                ///wpisz nickname

                if ( event.type == sf::Event::TextEntered &&
                        nickname.size() < 30 &&
                        event.key.code != sf::Keyboard::BackSpace
                   )
                {
                    nickname +=  event.text.unicode;
                    Nick.setString(nickname);
                    Nick.setPosition((Width/2 - Nick.getLocalBounds().width/2), 400);
                }
                else if (event.key.code == sf::Keyboard::BackSpace && nickname.size() > 0)
                {
                    nickname.erase(nickname.end() - 1);
                    Nick.setString(nickname);
                    Nick.setPosition((Width/2 - Nick.getLocalBounds().width/2), 400);
                }

            }///event

            app.clear();
            app.draw(TLO);
            app.draw(StartGame);
            app.draw(Nick);
            app.display();

        }///menu

        cSzybkoscGry.restart();

        while (bGAME)
        {
            sf::Event event;
            while (app.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    bGAME = false;
                    bWinLose = false;
                    bMENU = false;
                    bCzyProgramJestWlaczony = false;
                    app.close();
                }

                if ( event.type == sf::Event::Resized){
                    bPause = true;
                }
            }

            ///pauza gry
            if ( ( sf::Keyboard::isKeyPressed(sf::Keyboard::P) ) ||
                ( sf::Joystick::isButtonPressed( 0, 9 ) ) ){
                    bPause = true;
            } else if (event.type == sf::Event::KeyPressed ||
                       event.type == sf::Event::JoystickButtonPressed ) bPause = false;

            if (!bPause){

            ///Ustaw szybkosc

            tSprawdz += cSzybkoscGry.restart();
            float Iloczyn = tSprawdz.asSeconds();
            tSprawdz = sf::Time::Zero;
            RuchGracza = 100 * Iloczyn;
            SkokGracza = 80 * Iloczyn;
            Grawitacja = 150 * Iloczyn;
            SzybkoscWroga = 90 * Iloczyn;
            SzybkoscPocisku = 180 * Iloczyn;

            ///Ruch

            ///w prawo
            if ( ( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) == 100 )&&
                    mapa.getObiekt(pedzik.getPosition().y, pedzik.getPosition().x+SizeKafelka) != ziemia &&
                    mapa.getObiekt(pedzik.getPosition().y+SizeKafelka-1, pedzik.getPosition().x+SizeKafelka) != ziemia)
            {
                ped.right();

                if ( pedzik.getTexture() == &graczLeft ||
                        pedzik.getTexture() == &graczLeft1)
                {
                    pedzik.setTexture(graczRight1);
                }

                ped.addZmianaTextury();
                if ( ped.getZmianaTextury() >= CoIleZmianaTeksturyRuchu &&
                        ( (pedzik.getTexture() != &graczRight) ||
                          (pedzik.getTexture() != &graczRight1) ) )
                {
                    if (pedzik.getTexture() == &graczRight)
                    {
                        pedzik.setTexture(graczRight1);
                    }
                    else
                        pedzik.setTexture(graczRight);
                    ped.ZmianaTeksturyReset();
                }

            }

            /// W lewo
            if ( ( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) == -100 )&&
                    mapa.getObiekt(pedzik.getPosition().y, pedzik.getPosition().x-1) != ziemia &&
                    mapa.getObiekt(pedzik.getPosition().y+SizeKafelka-1, pedzik.getPosition().x-1) != ziemia )
            {
                ped.left();

                if ( pedzik.getTexture() == &graczRight ||
                        pedzik.getTexture() == &graczRight1)
                {
                    pedzik.setTexture(graczLeft1);
                }

                ped.addZmianaTextury();

                if ( (ped.getZmianaTextury() >= CoIleZmianaTeksturyRuchu ) &&
                        ( (pedzik.getTexture() != &graczLeft) ||
                          (pedzik.getTexture() != &graczLeft1) ) )
                {
                    if (pedzik.getTexture() == &graczLeft)
                    {
                        pedzik.setTexture(graczLeft1);
                    }
                    else
                        pedzik.setTexture(graczLeft);
                    ped.ZmianaTeksturyReset();
                }
            }

            ///Drabinka
            ///wejscie
            if ( ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == -100 ) &&
                    (mapa.getObiekt(pedzik.getPosition().y-1, pedzik.getPosition().x+SizeKafelka/2) == drabinka ||
                     mapa.getObiekt(pedzik.getPosition().y + SizeKafelka, pedzik.getPosition().x+SizeKafelka/2) == drabinka) ){
                ped.up();
            }

            ///ZEJSCIE
            if ( ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == 100 ) &&
                    ( mapa.getObiekt(pedzik.getPosition().y+SizeKafelka , pedzik.getPosition().x+SizeKafelka/2) == drabinka) ){
                ped.down();
            }

            ///Plywanie
            ///Wyjscie z wody else Ped wskoczył do wody
            if ( ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == -100 ) &&
                   mapa.getObiekt(pedzik.getPosition().y + SizeKafelka - 1, pedzik.getPosition().x+SizeKafelka/2) == woda &&
                    mapa.getObiekt(pedzik.getPosition().y - 1, pedzik.getPosition().x+SizeKafelka/2) != ziemia ){
                ped.up();
            } else if ( mapa.getObiekt( pedzik.getPosition().y+SizeKafelka, pedzik.getPosition().x+SizeKafelka/2 ) == woda &&
                        mapa.getObiekt( pedzik.getPosition().y+SizeKafelka/2 , pedzik.getPosition().x+SizeKafelka/2 ) == niebo &&
                        ped.getJump() == false ){
                   ped.grawitacja();
            }
            ///Ruch w dół w wodzie :D
            if ( ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == 100 ) &&
                mapa.getObiekt(pedzik.getPosition().y+SizeKafelka , pedzik.getPosition().x+SizeKafelka/2) == woda ) {
                ped.down();
            }
            ///skok
            if ( ( sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed( 0, 5 ) ) &&
                    (mapa.getObiekt(pedzik.getPosition().y+SizeKafelka, pedzik.getPosition().x) != niebo ||
                     mapa.getObiekt(pedzik.getPosition().y+SizeKafelka, pedzik.getPosition().x+SizeKafelka-1) != niebo ||
                     mapa.getObiekt(pedzik.getPosition().y+SizeKafelka, pedzik.getPosition().x + SizeKafelka/2) == woda ))
            {
                ped.JumpOn();
            }

            if (ped.getJump())
            {
                if ( mapa.getObiekt(pedzik.getPosition().y-1, pedzik.getPosition().x) != ziemia &&
                        mapa.getObiekt(pedzik.getPosition().y-1, pedzik.getPosition().x+SizeKafelka-1) != ziemia)  ///38?
                {
                    ped.up();
                }

                ped.addPixelJump(SkokGracza);

                if (ped.getPixelJump() >= 2.5*SizeKafelka)
                {
                    ped.JumpOff();
                    ped.resetPixelJump();
                }

            }
            else if ( mapa.getObiekt(pedzik.getPosition().y+SizeKafelka, pedzik.getPosition().x) == niebo &&
                      mapa.getObiekt(pedzik.getPosition().y+SizeKafelka, pedzik.getPosition().x+SizeKafelka-2) == niebo) ///38?
                ped.grawitacja();

            ///Strzal!

            if ( ( sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Joystick::isButtonPressed( 0,7 ) ) && tFire > FireGranica )
            {

                if (pedzik.getTexture() == &graczRight1 ||
                        pedzik.getTexture() == &graczRight)
                {
                    Fire tmp(pedzik.getPosition().x+SizeKafelka, pedzik.getPosition().y+SizeKafelka/2 - bullet.getSize().y/2, 1, &bullet);
                    Kule.push_back(tmp);
                }
                else
                {
                    Fire tmp(pedzik.getPosition().x-SizeKafelka+2, pedzik.getPosition().y+SizeKafelka/2 - bullet.getSize().y/2, - 1, &bullet);
                    Kule.push_back(tmp);
                }

                tFire = sf::Time::Zero;
            }
            tFire += cFire.restart();

            ///reset levelu
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) ||
                    sf::Joystick::isButtonPressed( 0, 8 ))
            {
                Kule.clear();
                Przeciwnik.clear();
                Punkty.clear();
                SCORE.resetZycie();
                widok.reset(sf::FloatRect(0, 0, Width, Height));
                app.setView(widok);
                pedzik.setPosition(100,100);
                SCORE.resetPunkty();
                mapa.NowaMapa();
                SCORE.UstawMaXPUNKTOW(Punkty.size());
            }

            for (int i = 0; i < Kule.size();)
            {
                ///Wyjscie pocisku poza mape
                if ( (Kule[i].getX() <= -SizeKafelka) || (Kule[i].getX() >= (SizeKafelka*IloscKafelekWidth) ) )
                {
                    Kule.erase(Kule.begin() + i);
                    continue;
                }

                ///uderzenie pocisku w ziemie
                if (  mapa.getObiekt(Kule[i].getY(), Kule[i].getX() + Kule[i].getWidth()) == ziemia ||
                        mapa.getObiekt(Kule[i].getY() + Kule[i].getHeight()-1, Kule[i].getX() + Kule[i].getHeight()) == ziemia ||
                        mapa.getObiekt(Kule[i].getY(), Kule[i].getX()-2) == ziemia ||
                        mapa.getObiekt(Kule[i].getY() + Kule[i].getHeight()-1, Kule[i].getX()-2) == ziemia )
                {
                    Kule.erase(Kule.begin() + i);
                    continue;
                }
                ++i;
            }

            ///uderzenie pocisku w wroga

            for (int i = 0; i < Kule.size(); ++i)
            {
                for (int j = 0; j < Przeciwnik.size();)
                {
                    if (MiniKolizja(Przeciwnik[j].getEnemyX(),
                                    Przeciwnik[j].getEnemyY(),
                                    Przeciwnik[j].getEnemyWidth(),
                                    Przeciwnik[j].getEnemyHeight(),
                                    Kule[i].getX(),
                                    Kule[i].getY(),
                                    Kule[i].getWidth(),
                                    Kule[i].getHeight()) )
                    {
                        Kule.erase(Kule.begin() + i);
                        Przeciwnik.erase(Przeciwnik.begin() + j);
                        SCORE.changePunkty(25);
                    }
                    else
                        ++j;
                }
            }


            ///kolizja wrog bohater
            for (int i = 0; i < Przeciwnik.size(); ++i)
            {
                if (MiniKolizja(pedzik.getGlobalBounds().left,
                                pedzik.getGlobalBounds().top,
                                pedzik.getGlobalBounds().width,
                                pedzik.getGlobalBounds().height,
                                Przeciwnik[i].getEnemyX(),
                                Przeciwnik[i].getEnemyY(),
                                Przeciwnik[i].getEnemyWidth(),
                                Przeciwnik[i].getEnemyHeight()
                               ))
                {
                    Przeciwnik.erase(Przeciwnik.begin() + i);
                    SCORE.changeZycie(-10);
                }
            }

            ///kolizja bohater - punkt - gwiazdka - pet - co kolwiek
            for (int i = 0; i< Punkty.size(); ++i)
            {
                if (MiniKolizja(pedzik.getGlobalBounds().left,
                                pedzik.getGlobalBounds().top,
                                pedzik.getGlobalBounds().width,
                                pedzik.getGlobalBounds().height,
                                Punkty[i].getAwardX(),
                                Punkty[i].getAwardY(),
                                SizeKafelka,
                                SizeKafelka))
                {
                    Punkty.erase(Punkty.begin() + i);
                    SCORE.changePunkty(50);
                    SCORE.ZDOBYTY_PUNKT();
                }
            }

            ///poruszaj strzalami
            for (int i = 0; i < Kule.size(); ++i){
                Kule[i].fly();
            }

            ///poruszaj wrogiem
            for (int i = 0; i < Przeciwnik.size(); ++i){
                Przeciwnik[i].RuchWroga(&mapa);
            }

            ///Ruch kamery
            if ( (pedzik.getGlobalBounds().left - widok.getCenter().x) > 50 &&
                    pedzik.getGlobalBounds().left <= (SizeKafelka*IloscKafelekWidth-static_cast<float>(Width)/2.5)-SizeKafelka )
            {
                widok.move(1,0);
                app.setView(widok);
            }
            else if ( (widok.getCenter().x - pedzik.getGlobalBounds().left) > SizeKafelka*10 &&  ///hmm???
                      pedzik.getGlobalBounds().left >= SizeKafelka*3 - 5 )
            {
                widok.move(-1,0);
                app.setView(widok);
            } else if ( widok.getCenter().y - pedzik.getGlobalBounds().top < 0 &&
                        widok.getCenter().y < SizeKafelka*IloscKafelekHeight - static_cast<float>(Height)/2.5 - SizeKafelka ) {
                widok.move(0,1);
                app.setView(widok);
            } else if (widok.getCenter().y - pedzik.getGlobalBounds().top > SizeKafelka * 5 &&
                       pedzik.getGlobalBounds().top >= SizeKafelka * 5){
                widok.move(0,-1);
                app.setView(widok);
            }

            ///Wyswietlanie
            app.clear();

            mapa.RysujMape(app,
                            widok.getCenter().x - Width/2,
                            widok.getCenter().x + Width/2 + SizeKafelka,
                            widok.getCenter().y - Height/2,
                            widok.getCenter().y + Height/2 + SizeKafelka);
            ///rysuj nagrody
            for (int i = 0; i < Punkty.size(); ++i) {
                    Punkty[i].RysujNagrode(app,
                            widok.getCenter().x - Width/2 - SizeKafelka,
                            widok.getCenter().x + Width/2 + SizeKafelka);
            }
            ///rysuj strzaly;
            for (int i = 0; i < Kule.size(); ++i) {
                Kule[i].DrawBullet(app,
                            widok.getCenter().x - Width/2 - SizeKafelka,
                            widok.getCenter().x + Width/2 + SizeKafelka);
            }
            ///rysuj wroga
            for (int i = 0; i < Przeciwnik.size(); ++i) {
                    Przeciwnik[i].RysujWroga(app,
                            widok.getCenter().x - Width/2 - SizeKafelka,
                            widok.getCenter().x + Width/2 + SizeKafelka);
            }
            ped.RysujPeda(app);
            SCORE.RysujPunkty(app, widok.getCenter().x, widok.getCenter().y - Height/2 );

            if ( SCORE.getZycie() <= 0 )
            {
                bGAME = false;
                bWinLose = true;
                bMENU = false;
                YouWinYouLose.setString("Przegtales zycie! \nAle nie matrw siê i tak wszyscy kiedys umrzemy :)");
                YouWinYouLose.setPosition((Width/2 - YouWinYouLose.getLocalBounds().width/2), Height/2);
                widok.reset(sf::FloatRect(0, 0, Width, Height));
                app.setView(widok);
            }

            ///przejscie do nastepnego poziomu...
            if ( SCORE.getPUNKTOW_DO_ZDOBYCIA() <= 0)
            {

                mapa.NextLevel();

                if ( (mapa.getLevel() < mapa.getMaxLevel()) )
                {
                    Kule.clear();
                    Przeciwnik.clear();
                    Punkty.clear();
                    SCORE.resetZycie();
                    widok.reset(sf::FloatRect(0, 0, Width, Height));
                    app.setView(widok);
                    pedzik.setPosition(100,100);
                    SCORE.resetPunkty();
                    mapa.NowaMapa();
                    SCORE.UstawMaXPUNKTOW(Punkty.size());
                    User.Zapisz(&nickname);
                    IloscKafelekWidth = mapa.getSizeWidth();
                    IloscKafelekHeight = mapa.getSizeHeight();
                }
                else
                {
                    bGAME = false;
                    bWinLose = true;
                    bMENU = false;
                    YouWinYouLose.setString("Wygrales paczke fajek. Umrzesz!");
                    YouWinYouLose.setPosition((Width/2 - YouWinYouLose.getLocalBounds().width/2), Height/2);
                }

                widok.reset(sf::FloatRect(0, 0, Width, Height));
                app.setView(widok);
            }

            app.display();

            }///pause
            else {
                cFire.restart();
                cSzybkoscGry.restart();
            }///jesli pauza
        }


        while (bWinLose)
        {
            sf::Event event;
            while (app.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    bGAME = false;
                    bWinLose = false;
                    bMENU = false;
                    bCzyProgramJestWlaczony = false;
                    app.close();
                }
                ///zmiana koloru napisu Start gry
                if (sf::Mouse::getPosition(app).x > StartGame.getGlobalBounds().left &&
                        sf::Mouse::getPosition(app).y > StartGame.getGlobalBounds().top &&
                        sf::Mouse::getPosition(app).x < StartGame.getGlobalBounds().left + StartGame.getGlobalBounds().width &&
                        sf::Mouse::getPosition(app).y < StartGame.getGlobalBounds().top +  StartGame.getGlobalBounds().height)
                {
                    StartGame.setColor(sf::Color::Red);
                }
                else
                {
                    StartGame.setColor(sf::Color::Green);
                }

                ///Start Gry! :D
                if ( ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) &&
                        sf::Mouse::getPosition(app).x > StartGame.getGlobalBounds().left &&
                        sf::Mouse::getPosition(app).y > StartGame.getGlobalBounds().top &&
                        sf::Mouse::getPosition(app).x < StartGame.getGlobalBounds().left + StartGame.getGlobalBounds().width &&
                        sf::Mouse::getPosition(app).y < StartGame.getGlobalBounds().top +  StartGame.getGlobalBounds().height) )
                {
                    ///Ustawienie kontrolek
                    bGAME = true;
                    bWinLose = false;
                    bMENU = false;
                    bCzyProgramJestWlaczony = true;
                    ///reset kontenerow
                    Kule.clear();
                    Przeciwnik.clear();
                    Punkty.clear();
                    mapa.ResetLevel();
                    ///ustaw mape
                    mapa.NowaMapa();
                    pedzik.setPosition(100,100);
                    SCORE.resetPunkty();
                    SCORE.resetZycie();
                    ///-----------Ustawiam zmienne-------///

                    IloscKafelekWidth = mapa.getSizeWidth();
                    IloscKafelekHeight = mapa.getSizeHeight();
                    SCORE.UstawMaXPUNKTOW(Punkty.size());

                }

                app.clear();
                app.draw(TLO);
                app.draw(StartGame);
                app.draw(YouWinYouLose);
                app.display();
            }

        }///petla wygranej

    }///duza petla programu

    return EXIT_SUCCESS;
}///main

bool MiniKolizja(float Obiekt1X,
                        float Obiekt1Y,
                        float Obiekt1Width,
                        float Obiekt1Height,
                        float Obiekt2X,
                        float Obiekt2Y,
                        float Obiekt2Width,
                        float Obiekt2Height)
{
    sf::IntRect Obiekt1(Obiekt1X,
                        Obiekt1Y,
                        Obiekt1Width,
                        Obiekt1Height);

    sf::IntRect Obiekt2(Obiekt2X,
                        Obiekt2Y,
                        Obiekt2Width,
                        Obiekt2Height);

    return Obiekt1.intersects(Obiekt2);

}
