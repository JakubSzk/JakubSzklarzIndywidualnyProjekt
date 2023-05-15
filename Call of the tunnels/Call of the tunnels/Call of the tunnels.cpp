#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
sf::Texture polebeta;
sf::Texture pole_blok; 
int pol_tab[6]={0,0,0,0,0,0}; //tablica na pola sasiednie
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////(gracz)


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////(end gracz)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////(pole)
class Pole
{
public:
    sf::Color color = sf::Color::Black;
    sf::Texture* point = &polebeta;
    int x = 0;
    int y = 0;
    int nr = 0;
    bool inside_bool = false;
    sf::Sprite pole;
    Pole(int b, int c, sf::Texture* a) : point(a), x(b), y(c) { pole.setTexture(*point); pole.setPosition(sf::Vector2f(x, y)); pole.setColor(sf::Color::Black); }
    Pole(int b, int c) : x(b), y(c) { pole.setTexture(*point); pole.setPosition(sf::Vector2f(x, y)); pole.setColor(sf::Color::Black); }
    void change(sf::Texture* a);
    void lock();
    void unlock();
    void load();
    bool hit(sf::Vector2i pos);
    void pola_obok();
    bool locked = false;
private:
    std::vector<std::string> outside;
    std::vector<std::string> inside;
    
    //std::vector<std::string> passable;
};

void Pole::pola_obok()
{
    for (int i = 0; i < 6; i++)
        pol_tab[i] = 0;
    switch (nr)
    {
    case 1:
        pol_tab[0] = 6;
        pol_tab[1] = 10;
        return;
        break;
    case 2:
    case 3:
    case 4:
        pol_tab[3] = nr+4;
        pol_tab[4] = nr+9;
        pol_tab[5] = nr+5;
        return;
        break;
    case 5:
        pol_tab[3] = nr + 4;
        pol_tab[4] = nr + 9;
        return;
        break;
    case 6:
    case 7:
    case 8:
    case 9:
        pol_tab[0] = nr + -5;
        pol_tab[2] = nr + -4;
        pol_tab[3] = nr + 4;
        pol_tab[4] = nr + 9;
        pol_tab[5] = nr + 5;
        return;
        break;
    case 10:
    case 19:
        pol_tab[1] = nr + -9;
        pol_tab[2] = nr + -4;
        pol_tab[4] = nr + 9;
        pol_tab[5] = nr + 5;
        return;
        break;
    case 14:
    case 23:
        pol_tab[0] = nr + -5;
        pol_tab[1] = nr + -9;
        pol_tab[3] = nr + 4;
        pol_tab[4] = nr + 9;
        return;
        break;
    case 29:
    case 30:
    case 31:
        pol_tab[0] = nr + -5;
        pol_tab[1] = nr + -9;
        pol_tab[2] = nr + -4;
        pol_tab[3] = nr + 4;
        pol_tab[5] = nr + 5;
        return;
        break;
    case 33:
    case 34:
    case 35:
    case 36:
        pol_tab[0] = nr + -5;
        pol_tab[1] = nr + -9;
        pol_tab[2] = nr + -4;
        return;
        break;
    case 28:
        pol_tab[1] = nr + -9;
        pol_tab[2] = nr + -4;
        pol_tab[5] = nr + 5;
        return;
        break;
    case 32:
        pol_tab[0] = nr + -5;
        pol_tab[1] = nr + -9;
        pol_tab[3] = nr + 4;
        return;
        break;
    }
    pol_tab[0] = nr + -5;
    pol_tab[1] = nr + -9;
    pol_tab[2] = nr + -4;
    pol_tab[3] = nr + 4;
    pol_tab[4] = nr + 9;
    pol_tab[5] = nr + 5;
}

void Pole::load()
{
    std::string name;
    std::fstream plik;
    name = "resources/pola/" + std::to_string(nr) + "i.txt";
    plik.open(name.c_str(), std::ios::in);
    while (std::getline(plik, name))
        inside.push_back(name);
    plik.close();
    name = "resources/pola/" + std::to_string(nr) + "o.txt";
    plik.open(name.c_str(), std::ios::in);
    while (std::getline(plik, name))
        outside.push_back(name);
    plik.close();

    switch (nr)
    {
    case 1:
    case 6:
    case 11:
    case 16:
    case 12:
    case 8:
    case 17:
    case 21:
    case 13:
    case 9:
    case 5:
    case 28:
        inside_bool = true;
        break;
    }
}

void Pole::lock()
{
    change(&pole_blok);
    locked = true;
}

void Pole::unlock()
{
    locked = false;
    pole.setTexture(polebeta);
    pole.setColor(sf::Color::Black);
    color = sf::Color::Black;
}

bool Pole::hit(sf::Vector2i pos) //funkcja sprawdzajaca hitboxy hexagonow
{
    if (locked)
        return false;
    if (pole.getColor() != sf::Color::Cyan)
        return false;
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
    virtual ~Item() = default;

    virtual void animacja(int nr_klatki) = 0;
    virtual void load() = 0;
};
//Klasa dla broni mele
class Mele :public Item
{
private:
    sf::Texture tekstura_eq;
    sf::Texture tekstura_postac;
    sf::Texture tekstura_attack;
    //Staty staty;
    std::string name;
public:
    Mele(std::string name) : name(name) {};
    
    virtual void animacja(int nr_klatki) override
    {
        std::cout << "a";
    }
    //funkcja do inicjacji itemu nie ma potrzeby wywolywac jesli tekstury nie beda potrzebne
    virtual void load() override
    {
        std::cout << "a";
    }
};
//Klasa dla przedmiotow broni zasiegowej
class Range :public Item
{
private:
    sf::Texture tekstura_eq;
    sf::Texture tekstura_postac;
    sf::Texture tekstura_attack;
    Staty staty;
    std::string name;
public:
    Range(std::string name) : name(name) {};
    //funkcja do animacji nalezy wywolac w petli podajac numer klatki
    //bedzie wywolywac co sie dzieje na kazdej klatce - przekroczenie zaplanowanych klatek nie jest problemem
    virtual void animacja(int nr_klatki) override
    {
        std::cout << "a";
    }
    //funkcja do inicjacji itemu nie ma potrzeby wywolywac jesli tekstury nie beda potrzebne
    virtual void load() override
    {
        std::cout << "a";
    }
};
//Klasa dla przedmiotow magicznych
class Magic :public Item
{
private:
    sf::Texture tekstura_eq;
    sf::Texture tekstura_wear;
    sf::Texture tekstura_attack;
    Staty staty;
    std::string name;
public:
    Magic(std::string name) : name(name) {};
    //funkcja do animacji nalezy wywolac w petli podajac numer klatki
    //bedzie wywolywac co sie dzieje na kazdej klatce - przekroczenie zaplanowanych klatek nie jest problemem
    virtual void animacja(int nr_klatki) override
    {
        std::cout << "a";
        //funkcja do inicjacji itemu nie ma potrzeby wywolywac jesli tekstury nie beda potrzebne
    }
    virtual void load() override
    {
        std::cout << "a";
    }
};
//Klasa dla przedmiotow noszonych na piersi
class Armor :public Item
{
private:
    sf::Texture tekstura_eq;
    sf::Texture tekstura_wear;
    sf::Texture tekstura_attack;
    Staty staty;
    std::string name;
public:
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////(end item)

//funkcja wykrywajaca ktore pole w ekwiupunku zostalo klikniete
//jesli nie trafi (zadne pole nie klikniete) zwroci 0, wiec mozna zastosowac if
int detekcja_nr_pola_w_ekwipunku(sf::Vector2i pos, int ilosc_itemow)
{
    pos.x -= 625;
    pos.y -= 45;
    float porown = float(int(pos.x / 115));
    if (porown + 1 > 6)
        return 0;
    if (!(pos.x <= (porown * 115 + 80)))
        return 0;
    int zwrotna = int(porown);
    porown = float(int(pos.y / 115));
    if (porown + 1 > 7)
        return 0;
    if (!(pos.x <= (porown * 115 + 80)))
        return 0;
    return (zwrotna + (int(porown) * 6) <= ilosc_itemow) ? (zwrotna + (int(porown) * 6)) : 0;
}
class Gracz
{
public:
    void load();
    int pole_map = 1;
    bool inside = false;
    ~Gracz()
    {
        for (int i = itemki_w_eq.size(); i <= 0 ; i--)
        {
            delete itemki_w_eq[i];
        }
    }
    //Staty stats;
private:
    std::vector<std::string> wczytane;
    std::vector<Item*> itemki_w_eq;
};

void Gracz::load()
{
    std::string name;
    std::fstream plik;
    name = "resources/gracz/load.txt";
    plik.open(name.c_str(), std::ios::in);
    while (std::getline(plik, name))
        wczytane.push_back(name);
    plik.close();
    if (wczytane[0] == "inside")
        inside = true;

    //////////////////////////////////////////////////

    std::vector<std::string> itemki;
    name = "resources/gracz/eq.txt";
    plik.open(name.c_str(), std::ios::in);
    while (std::getline(plik, name))
        itemki.push_back(name);
    plik.close();
    for (int i = 0; i < itemki.size(); i += 2)
    { 
        if (itemki[i + 1] == "mele")
        {
            itemki_w_eq.push_back(new Mele(itemki[i]));
        }
    }

}
int main()
{
    sf::Font font;
    font.loadFromFile("resources/Jack.ttf"); //czcionka
    //Mele x("abc");
    //Item* ptr;
    //ptr = &Mele("abc");
    //wczytywanie tekstur
    /////////////////////////////////////////////////////////////////////////////
    //tworzy zmienne tekstur
    sf::Texture map_back;
    sf::Texture eq_back;
    /////////////////////////////////////////////////////////////////////////////
    //pobiera z pliku
    pole_blok.loadFromFile("resources/poleblok.png");
    polebeta.loadFromFile("resources/betapolee.png");
    map_back.loadFromFile("resources/mapa.png");
    eq_back.loadFromFile("resources/ekwipunek.png");
    /////////////////////////////////////////////////////////////////////////////
    sf::RenderWindow window(sf::VideoMode(1900, 1000), "Call Of The Tunnels"); //tworzy okno
    window.setFramerateLimit(15); //limit klatek (bez tego komputer plonie)
    Gracz gracz;
    gracz.load();
   
    std::vector<sf::RectangleShape> beta_obj;
    std::vector<sf::Text> texts; //vectory zawierajace wczytywane obiekty
    std::vector<sf::Sprite> obj;
    std::vector<Pole> pola;
    int state = 0;
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

            
            if (state == 0)//menu
            {
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
            }
            else if (state == 1) //mapa
            {
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
                            pola.back().load();
                            xowe += 240;
                        }
                        yowe += 60;
                        xowe = 500;
                        for (int j = 0; j < 4; j++)
                        {
                            pola.push_back(Pole(xowe, yowe));
                            pola.back().nr = pola.size();
                            pola.back().load();
                            xowe += 240;
                        }
                        yowe += 60;
                    }
                    pola[17].lock();
                    std::cout << "happen";
                }
                obj.push_back(sf::Sprite());
                obj.back().setTexture(map_back);
                obj.back().setPosition(sf::Vector2f(0, 0));
                pola[gracz.pole_map - 1].pole.setColor(sf::Color::Cyan);

            }
            else if (state == 2)
            {
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

            }
            else if (state == 3)
            {
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
            }
            else if (state == 4)
            {
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

            }
            else if (state == 5)
            {
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
            }
            else if (state == 6)
            {

            
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
                std::cout << entered;
            }*/

            if (event.type == sf::Event::MouseButtonPressed)
            {
                
                if (state == 0)
                {
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
                }
                else if (state == 1)
                {
                    for (int i = 0; i < pola.size(); i++)
                    {
                        if (pola[i].hit(pos))
                        {
                            if (pola[i].inside_bool == gracz.inside || !(gracz.inside))
                            {
                                for (int j = 0; j < 6; j++)
                                {
                                    if (pol_tab[j] != 0)
                                    {
                                        if (pola[pol_tab[j] - 1].inside_bool == gracz.inside || !(gracz.inside))
                                        {
                                            pola[pol_tab[j] - 1].pole.setColor(pola[pol_tab[j] - 1].color);
                                        }
                                    }
                                }
                                pola[gracz.pole_map - 1].pole.setColor(pola[gracz.pole_map - 1].color);
                                gracz.pole_map = pola[i].nr;
                                pola[i].pole.setColor(sf::Color::Green);
                                pola[i].pola_obok();
                                for (int j = 0; j < 6; j++)
                                {
                                    if (pol_tab[j] != 0)
                                    {
                                        if ((pola[pol_tab[j] - 1].inside_bool == gracz.inside || !(gracz.inside)) && !pola[pol_tab[j] - 1].locked)
                                        {
                                            pola[pol_tab[j] - 1].pole.setColor(sf::Color::Cyan);
                                        }
                                    }
                                }
                            }
                            break;
                        }
                    }

                    //std::cout <<"pole: " << pola[i].nr << " status: " << pola[i].hit(pos) << std::endl;
                    if (pos.x > 570 && pos.x < 1330 && pos.y > 875 && pos.y < 925) //6
                    {
                        change_status = true;
                        state = 0;
                    }
                }
                else if (state == 2)
                {
                    if (pos.x > 570 && pos.x < 1330 && pos.y > 875 && pos.y < 925) //6
                    {
                        change_status = true;
                        state = 0;
                    }
                }
                else if (state == 3)
                {
                    if (pos.x > 570 && pos.x < 1330 && pos.y > 875 && pos.y < 925) //6
                    {
                        change_status = true;
                        state = 0;
                    }
                }
                else if (state == 4)
                {
                    if (pos.x > 570 && pos.x < 1330 && pos.y > 875 && pos.y < 925) //6
                    {
                        change_status = true;
                        state = 0;
                    }
                }
                else if (state == 5)
                {
                    if (pos.x > 570 && pos.x < 1330 && pos.y > 875 && pos.y < 925) //6
                    {
                        change_status = true;
                        state = 0;
                    }
                }
                else if (state == 6)
                {
                    if (pos.x > 570 && pos.x < 1330 && pos.y > 875 && pos.y < 925) //6
                    {
                        change_status = true;
                        state = 0;
                    }
                    
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