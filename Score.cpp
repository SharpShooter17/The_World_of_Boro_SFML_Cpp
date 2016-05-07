#include "Score.h"

cScore::cScore(sf::Font *p1)
{
    font = p1;
    zycie = 100;
    punkty = 0;
}

template<class T>
std::string toString(T var)
{
    std::ostringstream oss;
    oss << var;
    return oss.str();
}

void cScore::RysujPunkty(sf::RenderWindow &app, float width, float top)
{
    sf::Text wyswietl_zycie;
    std::string LIFE = toString(zycie);

    wyswietl_zycie.setString(LIFE);
    wyswietl_zycie.setPosition(width + Width/2 - 150, top + 10);
    wyswietl_zycie.setFont(*font);
    wyswietl_zycie.setCharacterSize(20);

    if ( zycie <= 100 && zycie >= 75)
    {
        wyswietl_zycie.setColor(sf::Color::Green);
    }
    else if ( zycie < 75 && zycie >= 50)
    {
        wyswietl_zycie.setColor(sf::Color::Blue);
    }
    else if (zycie < 50 && zycie >= 25 )
    {
        wyswietl_zycie.setColor(sf::Color::Yellow);
    }
    else
    {
        wyswietl_zycie.setColor(sf::Color::Red);
    }
    sf::Text tPunkty;
    std::string Point = toString(punkty);

    tPunkty.setString(Point);
    tPunkty.setCharacterSize(20);
    tPunkty.setColor(sf::Color::White);
    tPunkty.setPosition(width - Width/2 + 50,top + 10);
    tPunkty.setFont(*font);

    ///liczba punktow do zdobycia

    sf::Text LiczbaPunktow;
    std::string strLiczbaPunktow = toString(POZOSTALO_PUNKTOW);

    LiczbaPunktow.setString(strLiczbaPunktow);
    LiczbaPunktow.setCharacterSize(20);
    LiczbaPunktow.setColor(sf::Color::Blue);
    LiczbaPunktow.setPosition(width, top + 10);
    LiczbaPunktow.setFont(*font);

    app.draw(LiczbaPunktow);
    app.draw(wyswietl_zycie);
    app.draw(tPunkty);
}
