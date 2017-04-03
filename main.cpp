///
///     PLIK main.cpp
///             Zawiera wszystkie wywolania oraz wyswietla grafike
/// ////////////////////////////////////////////////////////////////


#include "funkcje.hpp"
//########################################

void teleskop(sf::RenderWindow &Ekran, sf::Event ewent);
void mikroskop(sf::RenderWindow &Ekran, sf::Event ewent);

//################################################################################################################### Main

int main()
{
    int wybor;

    //ladowanie grafik
    sf::Image SFML_IMG;
    SFML_IMG.LoadFromFile("obrazki/sfml.png");
    sf::Image NAPIS;
    NAPIS.LoadFromFile("obrazki/napis.png");
    sf::Sprite rysownik;

    sf::RenderWindow Ekran(sf::VideoMode(1024, 786, 32), "Teleskop & Mikroskop - fizyka");
    sf::Shape kwadrat = sf::Shape::Rectangle(0,Ekran.GetHeight()/2,210,Ekran.GetHeight()/2+200,sf::Color::Black,2);
    kwadrat.EnableFill(true);

    sf::Event ewent;
    while(Ekran.IsOpened())
    {
        Ekran.Clear();
        while(Ekran.GetEvent(ewent))
        {
            if (ewent.Type == sf::Event::Closed)
                Ekran.Close();
            if(ewent.Type == sf::Event::KeyPressed)
            {
                switch(ewent.Key.Code)
                {
                    case sf::Key::Num1: teleskop(Ekran,ewent); break;
                    case sf::Key::Num2: mikroskop(Ekran,ewent); break;
                    case sf::Key::Num3: Ekran.Close(); break;
                    case sf::Key::Escape: Ekran.Close();
                    default: break;
                }
            }
        }
        Ekran.Clear(sf::Color(100,100,230));

        rysownik.SetImage(NAPIS);
        rysownik.SetX(Ekran.GetWidth()/3);
        rysownik.SetY(100);
        Ekran.Draw(rysownik);

        rysownik.SetImage(SFML_IMG);
        rysownik.SetX(Ekran.GetWidth()-200);
        rysownik.SetY(Ekran.GetHeight()-150);
        Ekran.Draw(rysownik);
        wyswietl_napis(Ekran,"Autorzy programu : Wojciech Janeczek, Michal Telus, Michal Basinski, Patryk Zawadzki",10,Ekran.GetHeight()-100,'a');
        Ekran.Draw(kwadrat);
        wyswietl_napis(Ekran,"1) Teleskop\n\n2) Mikroskop\n\n3) Zakoncz",0,Ekran.GetHeight()/2,'w');
        Ekran.Display();
    }
    return 0;
}

//################################################################################################################### TELESKOP
void teleskop(sf::RenderWindow &Ekran, sf::Event ewent)
{
    soczewka obiektyw, okular;
    przedmiot pt,obraz1,obraz2;
    std::string napis;
    bool mouseon=false, koniec = false;
    int copodniesc=0;
    prosta p2,p3,p4,p1;

//*************************************************************************************************** poczatkowe ustawienie elementow

    obiektyw.polozenie = ( Ekran.GetWidth()/2 ) - 200;
    okular.ogniskowa = 200;
    obiektyw.ogniskowa = okular.ogniskowa*2;
    okular.polozenie = ( Ekran.GetWidth()/2 ) + 200;
    pt.polozenie = obiektyw.ogniskowa+20;
    pt.wysokosc = 40;

//*************************************************************************************************** ewent startuje - przyjmowanie polecen od uzytkownika
    while ((Ekran.IsOpened()) && (koniec == false))
    {
        const sf::Input &ster = Ekran.GetInput();

        while (Ekran.GetEvent(ewent))
        {
            if (ewent.Type == sf::Event::Closed)
                Ekran.Close();
            if(ewent.Type == sf::Event::KeyPressed)
                switch(ewent.Key.Code)
                {
                    case sf::Key::Escape: koniec=true; break;
                    case sf::Key::S: zrzut(Ekran); break;
                    default: break;
                }
            if(ewent.Type == sf::Event::MouseButtonPressed)
            {
                mouseon=true;
                if((ster.GetMouseX() < obiektyw.polozenie+2) and (ster.GetMouseX() > obiektyw.polozenie-2))
                    copodniesc=2;
                if(((ster.GetMouseX() < obiektyw.polozenie-obiektyw.ogniskowa+2) and (ster.GetMouseX() > obiektyw.polozenie-obiektyw.ogniskowa-2)) or ((ster.GetMouseX() < obiektyw.polozenie+obiektyw.ogniskowa+2) and (ster.GetMouseX() > obiektyw.polozenie+obiektyw.ogniskowa-2)))
                    copodniesc=3;
                if((ster.GetMouseX() < obiektyw.polozenie-pt.polozenie+2) and (ster.GetMouseX() > obiektyw.polozenie-pt.polozenie-2))
                    copodniesc=1;
                if((ster.GetMouseX() < okular.polozenie+2) and (ster.GetMouseX() > okular.polozenie-2))
                    copodniesc=4;

            }
            if(ewent.Type == sf::Event::MouseButtonReleased)
            {
                mouseon=false;
                copodniesc=0;
            }
        }

        // czysc ekran
        Ekran.Clear();

//*************************************************************************************************** rozpoznanie rzeczy podniesionej przez uzytkownika
        if(mouseon == true)
        {
            switch(copodniesc)
            {
                case 1:
                        pt.polozenie = obiektyw.polozenie - ster.GetMouseX();
                        pt.wysokosc = Ekran.GetHeight()/2 - ster.GetMouseY();
                        if(pt.polozenie < 0) pt.polozenie = 1;
                        if((pt.wysokosc < 5) or (ster.GetMouseY() > Ekran.GetHeight()/2)) pt.wysokosc = 5;
                        if(pt.wysokosc > 100) pt.wysokosc = 100;
                        napis = "p: "+flttostr(pt.polozenie)+"\nw: "+flttostr(pt.wysokosc);
                        wyswietl_napis(Ekran,napis,ster.GetMouseX(),ster.GetMouseY()+30,'m');
                        break;
                case 2:
                        obiektyw.polozenie=ster.GetMouseX();
                        napis = "p: "+flttostr(obiektyw.polozenie-Ekran.GetWidth()/2);
                        wyswietl_napis(Ekran,napis,ster.GetMouseX(),ster.GetMouseY()+30,'m');
                        break;
                case 3:
                        if(ster.GetMouseX() < obiektyw.polozenie)
                        {
                            obiektyw.ogniskowa = obiektyw.polozenie - ster.GetMouseX();
                            if(obiektyw.ogniskowa < 10) obiektyw.ogniskowa = 10;

                        }
                        else
                        {
                            obiektyw.ogniskowa = ster.GetMouseX() -obiektyw.polozenie;
                            if(obiektyw.ogniskowa < 10) obiektyw.ogniskowa = 10;
                        }
                    //    if(obiektyw.ogniskowa < okular.ogniskowa)obiektyw.ogniskowa = okular.ogniskowa;
                        napis = "p: "+flttostr(obiektyw.ogniskowa);
                        wyswietl_napis(Ekran,napis,ster.GetMouseX(),ster.GetMouseY()+30,'m');
                        break;
                case 4:
                        okular.ogniskowa = ster.GetMouseX() - obiektyw.polozenie - obiektyw.ogniskowa;
                        if(okular.ogniskowa < 10)okular.ogniskowa = 10;
                     //   if(okular.ogniskowa > obiektyw.ogniskowa) okular.ogniskowa = obiektyw.ogniskowa;
                        napis = "p: "+flttostr(okular.polozenie-obiektyw.polozenie)+"\no: "+flttostr(okular.ogniskowa);
                        wyswietl_napis(Ekran,napis,ster.GetMouseX()+5,ster.GetMouseY()+30,'m');
                        break;
                default: break;
            }
        }

//*************************************************************************************************** obliczenia

        //liczenie prostych
        p1=generuj_prosta2(obiektyw.polozenie-pt.polozenie, Ekran.GetHeight()/2-pt.wysokosc, obiektyw.polozenie, Ekran.GetHeight()/2);
        p2=p1;
        p2.b=p1.b+30;
        p3=generuj_prosta2(obiektyw.polozenie, p2.a*obiektyw.polozenie+p2.b, okular.polozenie-okular.ogniskowa, p1.a*(okular.polozenie-okular.ogniskowa)+p1.b);
        p4=generuj_prosta2(okular.polozenie, p1.a*okular.polozenie+p1.b, okular.polozenie+okular.ogniskowa, Ekran.GetHeight()/2);


        //liczenie obrazu posredniego
        obraz1.polozenie = okular.polozenie-okular.ogniskowa;
        obraz1.wysokosc = p1.a*obraz1.polozenie+p1.b;

        //liczenie obrazu ostatecznego
        obraz2.polozenie = okular.polozenie;
        obraz2.wysokosc = p4.a*okular.polozenie+p4.b;
//*************************************************************************************************** wyswietlenie elementow na ekran

        //linia
        Ekran.Draw(sf::Shape::Line(0,Ekran.GetHeight()/2,Ekran.GetWidth(),Ekran.GetHeight()/2,1,sf::Color::White));

        //obiektyw
        Ekran.Draw(sf::Shape::Line(obiektyw.polozenie,Ekran.GetHeight()/2+80,obiektyw.polozenie,Ekran.GetHeight()/2-80,2,sf::Color::Cyan));
        Ekran.Draw(sf::Shape::Line(obiektyw.polozenie-obiektyw.ogniskowa,Ekran.GetHeight()/2+10,obiektyw.polozenie-obiektyw.ogniskowa,Ekran.GetHeight()/2-10,2,sf::Color::Cyan));
        Ekran.Draw(sf::Shape::Line(obiektyw.polozenie+obiektyw.ogniskowa,Ekran.GetHeight()/2+10,obiektyw.polozenie+obiektyw.ogniskowa,Ekran.GetHeight()/2-10,2,sf::Color::Cyan));

        //okular
        okular.polozenie=obiektyw.polozenie+obiektyw.ogniskowa+okular.ogniskowa;
        Ekran.Draw(sf::Shape::Line(okular.polozenie,Ekran.GetHeight()/2+80,okular.polozenie,Ekran.GetHeight()/2-80,2,sf::Color::Cyan));
        Ekran.Draw(sf::Shape::Line(okular.polozenie+okular.ogniskowa,Ekran.GetHeight()/2+10,okular.polozenie+okular.ogniskowa,Ekran.GetHeight()/2-10,2,sf::Color::Cyan));

        //przedmiot
        Ekran.Draw(sf::Shape::Line(obiektyw.polozenie-pt.polozenie,Ekran.GetHeight()/2-pt.wysokosc,obiektyw.polozenie-pt.polozenie,Ekran.GetHeight()/2,2,sf::Color::Green));
        Ekran.Draw(sf::Shape::Line(obiektyw.polozenie-pt.polozenie,Ekran.GetHeight()/2-pt.wysokosc,obiektyw.polozenie-pt.polozenie-5,Ekran.GetHeight()/2-pt.wysokosc+5,2,sf::Color::Green));
        Ekran.Draw(sf::Shape::Line(obiektyw.polozenie-pt.polozenie,Ekran.GetHeight()/2-pt.wysokosc,obiektyw.polozenie-pt.polozenie+5,Ekran.GetHeight()/2-pt.wysokosc+5,2,sf::Color::Green));
        Ekran.Draw(sf::Shape::Line(obiektyw.polozenie-pt.polozenie-5,Ekran.GetHeight()/2-pt.wysokosc+5,obiektyw.polozenie-pt.polozenie+5,Ekran.GetHeight()/2-pt.wysokosc+5,2,sf::Color::Green));

        if(obiektyw.ogniskowa > okular.ogniskowa)
        {
            //promienie
            Ekran.Draw(sf::Shape::Line(0, p1.b, okular.polozenie, p1.a*okular.polozenie+p1.b, 1, sf::Color::Yellow));
            Ekran.Draw(sf::Shape::Line(0, p2.b, obiektyw.polozenie, p2.a*obiektyw.polozenie+p2.b, 1, sf::Color::Yellow));
            Ekran.Draw(sf::Shape::Line(obiektyw.polozenie, p2.a*obiektyw.polozenie+p2.b, okular.polozenie, p3.a*okular.polozenie+p3.b, 1, sf::Color::Yellow));
            Ekran.Draw(sf::Shape::Line(0, p4.b, obraz2.polozenie, obraz2.wysokosc, 1, sf::Color(250,150,0)));    //promien koncowy

            //Obraz1
            Ekran.Draw(sf::Shape::Line(obraz1.polozenie, obraz1.wysokosc, obraz1.polozenie, Ekran.GetHeight()/2,2,sf::Color::Green));
            Ekran.Draw(sf::Shape::Line(obraz1.polozenie, obraz1.wysokosc, obraz1.polozenie-5, obraz1.wysokosc-5,2,sf::Color::Green));
            Ekran.Draw(sf::Shape::Line(obraz1.polozenie, obraz1.wysokosc, obraz1.polozenie+5, obraz1.wysokosc-5,2,sf::Color::Green));
            Ekran.Draw(sf::Shape::Line(obraz1.polozenie-5, obraz1.wysokosc-5, obraz1.polozenie+5, obraz1.wysokosc-5,2,sf::Color::Green));
        }
        else
            wyswietl_napis(Ekran,"Obraz nie powstaje, zmien pozycje ogniskowych",Ekran.GetWidth()/2-200,Ekran.GetHeight()/2-200,'s');

        //napisy informacyjne
        napis = "Odleglosc miedzy soczewkami: "+flttostr(okular.polozenie - obiektyw.polozenie)+"\nOgniskowa obiektywu: "+flttostr(obiektyw.ogniskowa)+
        "\nOgniskowa okularu: "+flttostr(okular.ogniskowa)+"\nOdleglosc przedmiotu: "+flttostr(pt.polozenie)+"\nWysokosc przedmiotu: "+flttostr(pt.wysokosc);


        if(obiektyw.ogniskowa > okular.ogniskowa)
            napis += "\nPowiekszenie: "+flttostr(obraz2.wysokosc/pt.wysokosc);
        else
            napis +="\nPowiekszenie: n/a";

        wyswietl_napis(Ekran,napis,10,10,'s');
        Ekran.Display();
    }
}

//################################################################################################################### MIKROSKOP
void mikroskop(sf::RenderWindow &Ekran, sf::Event ewent)
{
    soczewka obiektyw, okular;
    przedmiot pt;
    std::string napis;
    bool mouseon=false, koniec = false;
    int copodniesc=0;
    prosta p2,p1,p3,p4;
    punkt pun;
    float x;

//*************************************************************************************************** poczatkowe dane

    obiektyw.polozenie = ( Ekran.GetWidth()/2 ) - 100;
    obiektyw.ogniskowa = 100;
    okular.ogniskowa = 50;
    okular.polozenie = ( Ekran.GetWidth()/2 ) + 100;
    pt.polozenie = 300;
    pt.wysokosc = 40;

//*************************************************************************************************** ewent startuje - sterowanie programem
    while ((Ekran.IsOpened()) && (koniec == false))
    {
        if((obiektyw.polozenie-pt.polozenie) < 0 && (obiektyw.polozenie-obiektyw.ogniskowa < 2))pt.polozenie = obiektyw.ogniskowa;
        const sf::Input &ster = Ekran.GetInput();

        while (Ekran.GetEvent(ewent))
        {
            if (ewent.Type == sf::Event::Closed)
                Ekran.Close();
            if(ewent.Type == sf::Event::KeyPressed)
                switch(ewent.Key.Code)
                {
                    case sf::Key::Escape: koniec = true; break;
                    case sf::Key::S: zrzut(Ekran); break;
                    default: break;
                }
            if(ewent.Type == sf::Event::MouseButtonPressed)
            {
                mouseon=true;
                if(((ster.GetMouseX() < okular.polozenie-okular.ogniskowa+2) and (ster.GetMouseX() > okular.polozenie-okular.ogniskowa-2)) or ((ster.GetMouseX() < okular.polozenie+okular.ogniskowa+2) and (ster.GetMouseX() > okular.polozenie+okular.ogniskowa-2)))
                    copodniesc=5;
                if((ster.GetMouseX() < obiektyw.polozenie+2) and (ster.GetMouseX() > obiektyw.polozenie-2))
                    copodniesc=2;
                if(((ster.GetMouseX() < obiektyw.polozenie-obiektyw.ogniskowa+2) and (ster.GetMouseX() > obiektyw.polozenie-obiektyw.ogniskowa-2)) or ((ster.GetMouseX() < obiektyw.polozenie+obiektyw.ogniskowa+2) and (ster.GetMouseX() > obiektyw.polozenie+obiektyw.ogniskowa-2)))
                    copodniesc=3;
                if((ster.GetMouseX() < obiektyw.polozenie-pt.polozenie+2) and (ster.GetMouseX() > obiektyw.polozenie-pt.polozenie-2))
                    copodniesc=1;
                if((ster.GetMouseX() < okular.polozenie+2) and (ster.GetMouseX() > okular.polozenie-2))
                    copodniesc=4;
            }
            if(ewent.Type == sf::Event::MouseButtonReleased)
            {
                mouseon=false;
                copodniesc=0;
            }
        }

        // czysc ekran
        Ekran.Clear();

//*************************************************************************************************** ustawianie elementow - sprawdza co podnosi uzytkownik
        if(mouseon == true)
        {
            switch(copodniesc)
            {
                case 1:
                        pt.polozenie = obiektyw.polozenie - ster.GetMouseX();
                        pt.wysokosc = Ekran.GetHeight()/2 - ster.GetMouseY();
                        if(pt.polozenie < obiektyw.ogniskowa) pt.polozenie = obiektyw.ogniskowa;
                        if((pt.wysokosc < 5) or (ster.GetMouseY() > Ekran.GetHeight()/2)) pt.wysokosc = 5;
                        if(pt.wysokosc > 100) pt.wysokosc = 100;
                        napis = "p: "+flttostr(pt.polozenie)+"\nw: "+flttostr(pt.wysokosc);
                        wyswietl_napis(Ekran,napis,ster.GetMouseX(),ster.GetMouseY()+30,'m');
                        break;
                case 2:
                        obiektyw.polozenie=ster.GetMouseX();
                        if(obiektyw.polozenie+obiektyw.ogniskowa > okular.polozenie-okular.ogniskowa)obiektyw.polozenie = (okular.polozenie-okular.ogniskowa)-obiektyw.ogniskowa;
                        napis = "p: "+flttostr(obiektyw.polozenie-Ekran.GetWidth()/2);
                        wyswietl_napis(Ekran,napis,ster.GetMouseX(),ster.GetMouseY()+30,'m');
                        break;
                case 3:
                        if(ster.GetMouseX() < obiektyw.polozenie)
                        {
                            obiektyw.ogniskowa = obiektyw.polozenie - ster.GetMouseX();
                            if(obiektyw.ogniskowa < 10) obiektyw.ogniskowa = 10;

                        }
                        else
                        {
                            obiektyw.ogniskowa = ster.GetMouseX() -obiektyw.polozenie;
                            if(obiektyw.ogniskowa < 10) obiektyw.ogniskowa = 10;
                        }
                        napis = "p: "+flttostr(obiektyw.ogniskowa);
                        wyswietl_napis(Ekran,napis,ster.GetMouseX(),ster.GetMouseY()+30,'m');
                        if(obiektyw.polozenie+obiektyw.ogniskowa > okular.polozenie - okular.ogniskowa)obiektyw.ogniskowa =(okular.polozenie-okular.ogniskowa) - obiektyw.polozenie;
                        if(pt.polozenie < obiektyw.ogniskowa)pt.polozenie = obiektyw.ogniskowa;
                        break;
                case 4:
                        okular.polozenie = ster.GetMouseX();
                        if(okular.polozenie-okular.ogniskowa < obiektyw.polozenie+obiektyw.ogniskowa)okular.polozenie = (obiektyw.polozenie+obiektyw.ogniskowa)+okular.ogniskowa;
                        napis = "p: "+flttostr(okular.polozenie-Ekran.GetWidth()/2);
                        wyswietl_napis(Ekran,napis,ster.GetMouseX(),ster.GetMouseY()+30,'m');
                        break;
                case 5:
                        if(ster.GetMouseX() < okular.polozenie)
                        {
                            okular.ogniskowa = okular.polozenie - ster.GetMouseX();
                            if(okular.ogniskowa < 10) okular.ogniskowa = 10;

                        }
                        else
                        {
                            okular.ogniskowa = ster.GetMouseX() - okular.polozenie;
                            if(okular.ogniskowa < 10) okular.ogniskowa = 10;
                        }
                        napis = "p: "+flttostr(okular.ogniskowa);
                        wyswietl_napis(Ekran,napis,ster.GetMouseX(),ster.GetMouseY()+30,'m');
                        if(okular.polozenie-okular.ogniskowa < obiektyw.polozenie + obiektyw.ogniskowa)okular.ogniskowa = okular.polozenie - (obiektyw.polozenie+obiektyw.ogniskowa);
                        break;
                default: break;
            }
        }

//***************************************************************************************************  obliczenia

        //obliczanie promieni
        p1=generuj_prosta2(obiektyw.polozenie-pt.polozenie, Ekran.GetHeight()/2-pt.wysokosc, obiektyw.polozenie, Ekran.GetHeight()/2);
        p2=generuj_prosta2(obiektyw.polozenie-pt.polozenie, Ekran.GetHeight()/2-pt.wysokosc, obiektyw.polozenie-obiektyw.ogniskowa, Ekran.GetHeight()/2);
        p3=generuj_prosta2(x, p1.a*x+p1.b, okular.polozenie, Ekran.GetHeight()/2);
        p4=generuj_prosta2(okular.polozenie, p2.a*obiektyw.polozenie+p2.b, okular.polozenie+okular.ogniskowa, Ekran.GetHeight()/2);

        x=(p2.a*obiektyw.polozenie+p2.b-p1.b)/p1.a; // wylicza x, potrzebne do sprawdzenia obrazu

//***************************************************************************************************  wyswietlanie elementow na ekran


        //linia
        Ekran.Draw(sf::Shape::Line(0,Ekran.GetHeight()/2,Ekran.GetWidth(),Ekran.GetHeight()/2,1,sf::Color::White));

        //obiektyw
        Ekran.Draw(sf::Shape::Line(obiektyw.polozenie,Ekran.GetHeight()/2+80,obiektyw.polozenie,Ekran.GetHeight()/2-80,2,sf::Color::Cyan));
        Ekran.Draw(sf::Shape::Line(obiektyw.polozenie-obiektyw.ogniskowa,Ekran.GetHeight()/2+10,obiektyw.polozenie-obiektyw.ogniskowa,Ekran.GetHeight()/2-10,2,sf::Color::Cyan));
        Ekran.Draw(sf::Shape::Line(obiektyw.polozenie+obiektyw.ogniskowa,Ekran.GetHeight()/2+10,obiektyw.polozenie+obiektyw.ogniskowa,Ekran.GetHeight()/2-10,2,sf::Color::Cyan));

        //okular
        Ekran.Draw(sf::Shape::Line(okular.polozenie,Ekran.GetHeight()/2+80,okular.polozenie,Ekran.GetHeight()/2-80,2,sf::Color::Cyan));
        Ekran.Draw(sf::Shape::Line(okular.polozenie+okular.ogniskowa,Ekran.GetHeight()/2+10,okular.polozenie+okular.ogniskowa,Ekran.GetHeight()/2-10,2,sf::Color::Cyan));
        Ekran.Draw(sf::Shape::Line(okular.polozenie-okular.ogniskowa,Ekran.GetHeight()/2+10,okular.polozenie-okular.ogniskowa,Ekran.GetHeight()/2-10,2,sf::Color::Cyan));

        //przedmiot
        Ekran.Draw(sf::Shape::Line(obiektyw.polozenie-pt.polozenie,Ekran.GetHeight()/2-pt.wysokosc,obiektyw.polozenie-pt.polozenie,Ekran.GetHeight()/2,2,sf::Color::Green));
        Ekran.Draw(sf::Shape::Line(obiektyw.polozenie-pt.polozenie,Ekran.GetHeight()/2-pt.wysokosc,obiektyw.polozenie-pt.polozenie-5,Ekran.GetHeight()/2-pt.wysokosc+5,2,sf::Color::Green));
        Ekran.Draw(sf::Shape::Line(obiektyw.polozenie-pt.polozenie,Ekran.GetHeight()/2-pt.wysokosc,obiektyw.polozenie-pt.polozenie+5,Ekran.GetHeight()/2-pt.wysokosc+5,2,sf::Color::Green));
        Ekran.Draw(sf::Shape::Line(obiektyw.polozenie-pt.polozenie-5,Ekran.GetHeight()/2-pt.wysokosc+5,obiektyw.polozenie-pt.polozenie+5,Ekran.GetHeight()/2-pt.wysokosc+5,2,sf::Color::Green));

        //promienie
        Ekran.Draw(sf::Shape::Line(obiektyw.polozenie-pt.polozenie, Ekran.GetHeight()/2-pt.wysokosc, obiektyw.polozenie, Ekran.GetHeight()/2, 1, sf::Color::Yellow));
        Ekran.Draw(sf::Shape::Line(obiektyw.polozenie, Ekran.GetHeight()/2, okular.polozenie, p1.a*okular.polozenie+p1.b, 1, sf::Color::Yellow));

        Ekran.Draw(sf::Shape::Line(obiektyw.polozenie-pt.polozenie, Ekran.GetHeight()/2-pt.wysokosc, obiektyw.polozenie, p2.a*obiektyw.polozenie+p2.b, 1, sf::Color::Yellow));
        Ekran.Draw(sf::Shape::Line(obiektyw.polozenie, p2.a*obiektyw.polozenie+p2.b, okular.polozenie, p2.a*obiektyw.polozenie+p2.b, 1, sf::Color::Yellow));

        //Obrazy
         if(x<okular.polozenie && x>okular.polozenie-okular.ogniskowa)  //sprawdzanie czy obraz powstaje
        {
            //obraz1
            Ekran.Draw(sf::Shape::Line(x, p1.a*x+p1.b, x, Ekran.GetHeight()/2,2,sf::Color::Green));
            Ekran.Draw(sf::Shape::Line(x, p1.a*x+p1.b, x-5, p1.a*x+p1.b-5,2,sf::Color::Green));
            Ekran.Draw(sf::Shape::Line(x, p1.a*x+p1.b, x+5, p1.a*x+p1.b-5,2,sf::Color::Green));
            Ekran.Draw(sf::Shape::Line(x+5, p1.a*x+p1.b-5, x-5, p1.a*x+p1.b-5,2,sf::Color::Green));

            //promienie
            Ekran.Draw(sf::Shape::Line(okular.polozenie, Ekran.GetHeight()/2, 0, p3.b, 1, sf::Color(250,150,0)));
            Ekran.Draw(sf::Shape::Line(okular.polozenie+okular.ogniskowa, Ekran.GetHeight()/2, 0, p4.b, 1, sf::Color(250,150,0)));

            //obraz2
            pun=rozw_uklad(p3.a,-1,-p3.b,p4.a,-1,-p4.b);
            Ekran.Draw(sf::Shape::Line(pun.x, pun.y, pun.x, Ekran.GetHeight()/2,2,sf::Color::Green));

            Ekran.Draw(sf::Shape::Line(pun.x, pun.y, pun.x-5, pun.y-5,2,sf::Color::Green));
            Ekran.Draw(sf::Shape::Line(pun.x, pun.y, pun.x+5, pun.y-5,2,sf::Color::Green));
            Ekran.Draw(sf::Shape::Line(pun.x+5, pun.y-5, pun.x-5, pun.y-5,2,sf::Color::Green));

        }
        else
            wyswietl_napis(Ekran,"Obraz nie powstaje, ustaw inaczej przedmiot",Ekran.GetWidth()/2-200,Ekran.GetHeight()/2-200,'s');

        //napisy stale
        napis = "Odleglosc miedzy soczewkami: "+flttostr(okular.polozenie - obiektyw.polozenie)+"\nOgniskowa obiektywu: "+flttostr(obiektyw.ogniskowa)+"\nOgniskowa okularu: "+
        flttostr(okular.ogniskowa)+"\nOdleglosc przedmiotu: "+flttostr(pt.polozenie)+"\nWysokosc przedmiotu: "+flttostr(pt.wysokosc);


        if(x<okular.polozenie && x>okular.polozenie-okular.ogniskowa)
            napis +="\nWysokosc Obrazu: "+flttostr((pun.y-Ekran.GetHeight()/2))+"\nPowiekszenie: "+flttostr((pun.y-Ekran.GetHeight()/2)/pt.wysokosc);
        else
            napis +="\nWysokosc Obrazu: n/a\nPowiekszenie: n/a";
        wyswietl_napis(Ekran,napis,10,10,'s');
        Ekran.Display();
    }
}
