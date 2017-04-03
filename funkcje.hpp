///
///     PLIK funkcje.hpp
///             Zawiera wszystkie funkcje wolne i struktury
/// ////////////////////////////////////////////////////////////

#ifndef funkcjion
#define funkcjion

#include <SFML/Graphics.hpp>
#include <sys/stat.h>
#include <sstream>
#include <iostream>
//#include <cstdlib>
#include <cmath>

//########################################################### Struktury
struct soczewka
{
    float polozenie;
    float ogniskowa;
    float ognisko;
};

struct przedmiot
{
    float polozenie;
    float wysokosc;
};

struct prosta   //proste typu y=ax+b - opisujace ruch promieni
{
    float a;
    float b;
    float kat_padania;
};

struct punkt
{
    float x;
    float y;
};
//########################################################### Funkcje Wolne

//prosta generuj_prosta(float x1,float y1,float x2,float y2);
prosta generuj_prosta2(float x1,float y1,float x2,float y2);
bool zrzut(sf::RenderWindow &Obraz);
std::string inttostr(int liczba);
std::string flttostr(float liczba);
void wyswietl_napis(sf::RenderWindow &ekran,std::string napis,int x,int y,char style);
punkt rozw_uklad(float a1,float b1,float c1, float a2, float b2,float c2);


#endif
