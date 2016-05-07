#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include "naglowki.h"

class cScore
{
private:
    int zycie;
    long int punkty;
    sf::Font *font;
    int POZOSTALO_PUNKTOW;
public:
    cScore(sf::Font *p1);
    inline int getZycie() { return zycie; }
    inline void changeZycie(long int x) { zycie +=x; }
    inline void resetZycie() { zycie = 100; }
    inline long int getPunkty() { return punkty; }
    inline void changePunkty(long int x){ punkty +=x; }
    inline void resetPunkty() { punkty = 0; }
    inline void setPunkty(long int x) { punkty = x; }
    inline void UstawMaXPUNKTOW(int x){POZOSTALO_PUNKTOW = x; }
    inline int getPUNKTOW_DO_ZDOBYCIA() { return POZOSTALO_PUNKTOW;}
    inline void ZDOBYTY_PUNKT() { --POZOSTALO_PUNKTOW; }
    void RysujPunkty(sf::RenderWindow &app, float width, float top);
};

#endif // SCORE_H_INCLUDED
