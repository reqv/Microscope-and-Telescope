///
///     PLIK funkcje.cpp
///             Zawiera definicje funkcji z pliku "funkcje.hpp"
/// //////////////////////////////////////////////////////////////

#include "funkcje.hpp"

//########################################################### funkcje obliczeniowe

prosta generuj_prosta2(float x1,float y1,float x2,float y2)

{
 prosta p;
 p.a=(y2-y1)/(x2-x1);
 p.b=y1-p.a*x1;
 p.kat_padania=atan(p.a);
 return p;

}

punkt rozw_uklad(float a1,float b1,float c1, float a2, float b2,float c2)
{
    float W,Wx,Wy;
    punkt p;
    p.x=0;  p.y=0;
    W = a1 * b2 - a2 * b1;
 Wx = b2 * c1 - c2 * b1;
 Wy = a1 * c2 - a2 * c1;

 if(W != 0)
 {
 p.x = Wx / W;
 p.y = Wy / W;
 }

 return p;
}

//########################################################### funkcje dodatkowe

void wyswietl_napis(sf::RenderWindow &ekran, std::string napis,int x, int y, char style)
{
    static sf::String tekst;
    tekst.SetText(napis);
    tekst.SetPosition(x,y);

    switch(style)
    {
        case 'm': tekst.SetColor(sf::Color::Green); tekst.SetScale(.5,.5); break;
        case 'i': tekst.SetColor(sf::Color::Yellow); tekst.SetScale(2,2); break;
        case 's': tekst.SetColor(sf::Color::White); tekst.SetScale(.5,.5); break;
        case 'w': tekst.SetColor(sf::Color::Yellow); tekst.SetScale(1.2,1.2); break;
        case 'a': tekst.SetColor(sf::Color::Black); tekst.SetScale(0.8,0.8); break;
        default: break;
    }
    ekran.Draw(tekst);
}

bool zrzut(sf::RenderWindow &Obraz)
{
    std::string nazwa;
    struct stat buf;
    sf::Image screenshot = Obraz.Capture();
    int i=0;
    if(stat("zdjecia", &buf) == 0)
    {
    do{
        nazwa="zdjecia/soczewka"+inttostr(i)+".jpg";
        i++;
    }while(stat(nazwa.c_str(), &buf) == 0);
    screenshot.SaveToFile(nazwa);
    return 0;
    }
    else return 1;

}

std::string inttostr(int liczba)
{
    std::ostringstream ss;
    ss<<liczba;
    return ss.str();
}

std::string flttostr(float liczba)
{
    std::ostringstream ss;
    ss<<liczba;
    return ss.str();
}
