#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////(pole)
sf::Texture polebeta;
class Pole
{
public:
    sf::Color color = sf::Color::Black;
    sf::Texture* point = &polebeta;
    int x = 0;
    int y = 0;
    int nr = 0;
    sf::Sprite pole;
    Pole(int b, int c, sf::Texture* a) : point(a), x(b), y(c) { pole.setTexture(*point); pole.setPosition(sf::Vector2f(x, y)); pole.setColor(sf::Color::Black); }
    Pole(int b, int c) : x(b), y(c) { pole.setTexture(*point); pole.setPosition(sf::Vector2f(x, y)); pole.setColor(sf::Color::Black); }
    void change(sf::Texture* a);
    bool hit(sf::Vector2i pos);
private:
    //empty for now
};

bool Pole::hit(sf::Vector2i pos) //funkcja sprawdzajaca hitboxy hexagonow
{
    //std::cout << std::endl << "xt: " << x << " yt: " << y << " xm: " << pos.x << " ym: " << pos.y << std::endl;
    if (pos.x > x && pos.x < (x + 60))
        return ((- pos.x + y + x + 60) < pos.y) && ((pos.x + (y - x) + 60) > pos.y);
    if (pos.x > (x + 60) && pos.x < (x + 120))
        return (pos.y > y && pos.y < (y + 120));
    if (pos.x > (x + 120) && pos.x < (x + 180))
        return ((pos.x + (y - x) - 120) < pos.y) && ((-pos.x + y + x + 240) > pos.y);
    return false;
}

void Pole::change(sf::Texture* a)
{
    pole.setTexture(*a);
    pole.setColor(sf::Color::White);
    color = sf::Color::White;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////(end pole)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////(staty)
class Staty
{
public:
    std::string nazwa = "entity";
    //witalne
    int hp = 0;
    int armor = 0;
    int witalnosc = 0;
    //do ataku
    int sila = 0;
    int dmg = 0;
    int zasieg = 0;
    int szybkosc = 0;
    //cechy
    int stamina = 0;
    int zrecznosc = 0;
    int mana = 0;
    Staty() {};
    Staty(std::string nazwa, int hp, int armor, int witalnosc, int sila, int dmg, int zasieg, int szybkosc, int stamina, int zrecznosc, int mana) :
        hp((hp < witalnosc) ? hp : witalnosc),
        armor(armor),
        witalnosc(witalnosc),
        sila(sila),
        dmg(dmg),
        zasieg(zasieg),
        szybkosc(szybkosc),
        stamina(stamina),
        zrecznosc(zrecznosc),
        mana(mana),
        nazwa(nazwa)
    {
        //if (hp > witalnosc)
            //Staty(nazwa, witalnosc, armor, witalnosc, sila, dmg, zasieg, szybkosc, stamina, zrecznosc, mana);
    };
};

Staty operator += (Staty& a, const Staty& b)
{
    return Staty(a.nazwa, a.hp + b.hp, a.armor + b.armor, a.witalnosc + b.witalnosc, a.sila + b.sila, a.dmg + b.dmg, a.zasieg + b.zasieg, a.szybkosc + b.szybkosc, a.stamina + b.stamina, a.zrecznosc + b.zrecznosc, a.mana + b.mana);
}
Staty operator + (const Staty& a, const Staty& b)
{
    return Staty("mix", a.hp + b.hp, a.armor + b.armor, a.witalnosc + b.witalnosc, a.sila + b.sila, a.dmg + b.dmg, a.zasieg + b.zasieg, a.szybkosc + b.szybkosc, a.stamina + b.stamina, a.zrecznosc + b.zrecznosc, a.mana + b.mana);
}
Staty operator -= (Staty& a, const Staty& b)
{
    return Staty(a.nazwa, a.hp - b.hp, a.armor - b.armor, a.witalnosc - b.witalnosc, a.sila - b.sila, a.dmg - b.dmg, a.zasieg - b.zasieg, a.szybkosc - b.szybkosc, a.stamina - b.stamina, a.zrecznosc - b.zrecznosc, a.mana - b.mana);
}
Staty operator - (const Staty& a, const Staty& b)
{
    return Staty("mix", a.hp - b.hp, a.armor - b.armor, a.witalnosc - b.witalnosc, a.sila - b.sila, a.dmg - b.dmg, a.zasieg - b.zasieg, a.szybkosc - b.szybkosc, a.stamina - b.stamina, a.zrecznosc - b.zrecznosc, a.mana - b.mana);
}
std::ostream& operator << (std::ostream& out, const Staty& f)
{
    return out
        << "\nNazwa: " << f.nazwa
        << "\nHp: " << f.hp
        << "\nArmor: " << f.armor
        << "\nWitalnosc: " << f.witalnosc
        << "\nSila: " << f.sila
        << "\nDmg: " << f.dmg
        << "\nZasieg: " << f.zasieg
        << "\nSzybkosc: " << f.szybkosc
        << "\nStamina: " << f.stamina
        << "\nZrecznosc: " << f.zrecznosc
        << "\nMana: " << f.mana;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////(end staty)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////(item)
class Item
{
public:

};

int main()
{
    sf::Font font;
    font.loadFromFile("resources/Jack.ttf"); //czcionka

    //wczytywanie tekstur
    /////////////////////////////////////////////////////////////////////////////
    //tworzy zmienne tekstur
    sf::Texture map_back;
    sf::Texture eq_back;
    sf::Texture pole_blok;
    /////////////////////////////////////////////////////////////////////////////
    //pobiera z pliku
    pole_blok.loadFromFile("resources/poleblok.png");
    polebeta.loadFromFile("resources/betapolee.png");
    map_back.loadFromFile("resources/mapa.png");
    eq_back.loadFromFile("resources/ekwipunek.png");
    /////////////////////////////////////////////////////////////////////////////
    sf::RenderWindow window(sf::VideoMode(1900, 1000), "Call Of The Tunnels"); //tworzy okno
    window.setFramerateLimit(30); //limit klatek (bez tego komputer plonie)
   
    std::vector<sf::RectangleShape> beta_obj;
    std::vector<sf::Text> texts; //vectory zawierajace wczytywane obiekty
    std::vector<sf::Sprite> obj;
    std::vector<Pole> pola;

    int state = 0;
    int pole_map = 2;
    bool change_status = true; //zmienne zarzadzajace wczytywaniem zasobow
    bool odswmap = false;

    sf::Vector2i pos;

    while (window.isOpen())
    {
        if (change_status) //wczytywanie
        {
            beta_obj.clear();
            obj.clear(); //reset
            texts.clear();
            pola.clear();

            switch (state)
            {
            case 0: //menu
                for (int i = 0; i < 6; i++)
                {
                    beta_obj.push_back(sf::RectangleShape(sf::Vector2f(760, 50)));
                    beta_obj[i].setPosition(sf::Vector2f(570, 500 + (i * 75)));
                    beta_obj[i].setFillColor(sf::Color::Blue);
                    texts.push_back(sf::Text());
                    texts[i].setFont(font);
                    texts[i].setFillColor(sf::Color::Black);
                    texts[i].setPosition(sf::Vector2f(950, 510 + (i * 75)));
                    texts[i].setCharacterSize(30);
                    texts[i].setString("opcja" + std::to_string(i + 1));
                }
                break;

            case 1: //mapa
                beta_obj.push_back(sf::RectangleShape(sf::Vector2f(760, 50)));
                beta_obj[0].setPosition(sf::Vector2f(570, 875));
                beta_obj[0].setFillColor(sf::Color::Blue);
                texts.push_back(sf::Text());
                texts.push_back(sf::Text());
                for (int i = 0; i < 2; i++)
                {
                    texts[i].setCharacterSize(30);
                    texts[i].setFont(font);
                }
                texts[0].setFillColor(sf::Color::Black);
                texts[1].setFillColor(sf::Color::White);
                texts[0].setString("menu");
                texts[1].setString("1");
                texts[0].setPosition(sf::Vector2f(950, 885));
                texts[1].setPosition(sf::Vector2f(990, 490));
                if (!(pola.size() != 0))
                {
                    int xowe = 380, yowe = 140;
                    for (int i = 0; i < 4; i++)
                    {
                        xowe = 380;
                        for (int j = 0; j < 5; j++)
                        {
                            pola.push_back(Pole(xowe, yowe));
                            pola.back().nr = pola.size();
                            xowe += 240;
                        }
                        yowe += 60;
                        xowe = 500;
                        for (int j = 0; j < 4; j++)
                        {
                            pola.push_back(Pole(xowe, yowe));
                            pola.back().nr = pola.size();
                            xowe += 240;
                        }
                        yowe += 60;
                    }
                    pola[17].change(&pole_blok);
                    std::cout << "happen";
                }
                obj.push_back(sf::Sprite());
                obj.back().setTexture(map_back);
                obj.back().setPosition(sf::Vector2f(0, 0));
                break;

            case 2:
                beta_obj.push_back(sf::RectangleShape(sf::Vector2f(760, 50)));
                beta_obj[0].setPosition(sf::Vector2f(570, 875));
                beta_obj[0].setFillColor(sf::Color::Blue);
                texts.push_back(sf::Text());
                texts.push_back(sf::Text());
                for (int i = 0; i < 2; i++)
                {
                    texts[i].setCharacterSize(30);
                    texts[i].setFont(font);
                }
                texts[0].setFillColor(sf::Color::Black);
                texts[1].setFillColor(sf::Color::White);
                texts[0].setString("menu");
                texts[1].setString("2");
                texts[0].setPosition(sf::Vector2f(950, 885));
                texts[1].setPosition(sf::Vector2f(990, 490));
                obj.push_back(sf::Sprite());
                obj.back().setTexture(eq_back);
                obj.back().setPosition(sf::Vector2f(0, 0));
                break;

            case 3:
                beta_obj.push_back(sf::RectangleShape(sf::Vector2f(760, 50)));
                beta_obj[0].setPosition(sf::Vector2f(570, 875));
                beta_obj[0].setFillColor(sf::Color::Blue);
                texts.push_back(sf::Text());
                texts.push_back(sf::Text());
                for (int i = 0; i < 2; i++)
                {
                    texts[i].setCharacterSize(30);
                    texts[i].setFont(font);
                }
                texts[0].setFillColor(sf::Color::Black);
                texts[1].setFillColor(sf::Color::White);
                texts[0].setString("menu");
                texts[1].setString("3");
                texts[0].setPosition(sf::Vector2f(950, 885));
                texts[1].setPosition(sf::Vector2f(990, 490));
                break;

            case 4:
                beta_obj.push_back(sf::RectangleShape(sf::Vector2f(760, 50)));
                beta_obj[0].setPosition(sf::Vector2f(570, 875));
                beta_obj[0].setFillColor(sf::Color::Blue);
                texts.push_back(sf::Text());
                texts.push_back(sf::Text());
                for (int i = 0; i < 2; i++)
                {
                    texts[i].setCharacterSize(30);
                    texts[i].setFont(font);
                }
                texts[0].setFillColor(sf::Color::Black);
                texts[1].setFillColor(sf::Color::White);
                texts[0].setString("menu");
                texts[1].setString("4");
                texts[0].setPosition(sf::Vector2f(950, 885));
                texts[1].setPosition(sf::Vector2f(990, 490));
                break;

            case 5:
                beta_obj.push_back(sf::RectangleShape(sf::Vector2f(760, 50)));
                beta_obj[0].setPosition(sf::Vector2f(570, 875));
                beta_obj[0].setFillColor(sf::Color::Blue);
                texts.push_back(sf::Text());
                texts.push_back(sf::Text());
                for (int i = 0; i < 2; i++)
                {
                    texts[i].setCharacterSize(30);
                    texts[i].setFont(font);
                }
                texts[0].setFillColor(sf::Color::Black);
                texts[1].setFillColor(sf::Color::White);
                texts[0].setString("menu");
                texts[1].setString("5");
                texts[0].setPosition(sf::Vector2f(950, 885));
                texts[1].setPosition(sf::Vector2f(990, 490));
                break;

            case 6:
                beta_obj.push_back(sf::RectangleShape(sf::Vector2f(760, 50)));
                beta_obj[0].setPosition(sf::Vector2f(570, 875));
                beta_obj[0].setFillColor(sf::Color::Blue);
                texts.push_back(sf::Text());
                texts.push_back(sf::Text());
                for (int i = 0; i < 2; i++)
                {
                    texts[i].setCharacterSize(30);
                    texts[i].setFont(font);
                }
                texts[0].setFillColor(sf::Color::Black);
                texts[1].setFillColor(sf::Color::White);
                texts[0].setString("menu");
                texts[1].setString("6");
                texts[0].setPosition(sf::Vector2f(950, 885));
                texts[1].setPosition(sf::Vector2f(990, 490));
                break;

            }
            change_status = false;
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            pos = sf::Mouse::getPosition(window);
            if (event.type == sf::Event::Closed)
                window.close();

            /*if (event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde))
            {
                std::string entered;
                std::cin >> entered;
            }*/

            if (event.type == sf::Event::MouseButtonPressed)
            {
                switch (state)
                {
                case 0:
                    if (pos.x > 570 && pos.x < 1330 && pos.y > 500 && pos.y < 550) //1
                    {
                        change_status = true;
                        state = 1;
                    }
                    if (pos.x > 570 && pos.x < 1330 && pos.y > 575 && pos.y < 625) //2
                    {
                        change_status = true;
                        state = 2;
                    }
                    if (pos.x > 570 && pos.x < 1330 && pos.y > 650 && pos.y < 700) //3
                    {
                        change_status = true;
                        state = 3;
                    }
                    if (pos.x > 570 && pos.x < 1330 && pos.y > 725 && pos.y < 775) //4
                    {
                        change_status = true;
                        state = 4;
                    }
                    if (pos.x > 570 && pos.x < 1330 && pos.y > 800 && pos.y < 850) //5
                    {
                        change_status = true;
                        state = 5;
                    }
                    if (pos.x > 570 && pos.x < 1330 && pos.y > 875 && pos.y < 925) //6
                    {
                        change_status = true;
                        state = 6;
                    }
                    break;
                case 1:
                    for (int i = 0; i < pola.size(); i++)
                    {
                        if (pola[i].hit(pos))
                        {
                            pola[pole_map - 1].pole.setColor(pola[pole_map-1].color);
                            pole_map = pola[i].nr;
                            pola[i].pole.setColor(sf::Color::Green);
                            break;
                        }
                    }

                        //std::cout <<"pole: " << pola[i].nr << " status: " << pola[i].hit(pos) << std::endl;
                    if (pos.x > 570 && pos.x < 1330 && pos.y > 875 && pos.y < 925) //6
                    {
                        change_status = true;
                        state = 0;
                    }
                    break;
                case 2:
                    if (pos.x > 570 && pos.x < 1330 && pos.y > 875 && pos.y < 925) //6
                    {
                        change_status = true;
                        state = 0;
                    }
                    break;
                case 3:
                    if (pos.x > 570 && pos.x < 1330 && pos.y > 875 && pos.y < 925) //6
                    {
                        change_status = true;
                        state = 0;
                    }
                    break;
                case 4:
                    if (pos.x > 570 && pos.x < 1330 && pos.y > 875 && pos.y < 925) //6
                    {
                        change_status = true;
                        state = 0;
                    }
                    break;
                case 5:
                    if (pos.x > 570 && pos.x < 1330 && pos.y > 875 && pos.y < 925) //6
                    {
                        change_status = true;
                        state = 0;
                    }
                    break;
                case 6:
                    if (pos.x > 570 && pos.x < 1330 && pos.y > 875 && pos.y < 925) //6
                    {
                        change_status = true;
                        state = 0;
                    }
                    break;
                }
            }
        }
        window.clear();
        //odswierzanie

        for (int i = 0; i < obj.size(); i++)
            window.draw(obj[i]);
        
        for (int i = 0; i < pola.size(); i++)
            window.draw(pola[i].pole);
        for (int i = 0; i < beta_obj.size(); i++)
            window.draw(beta_obj[i]);
        for (int i = 0; i < texts.size(); i++)
            window.draw(texts[i]);
        window.display();
    }

    return 0;
}