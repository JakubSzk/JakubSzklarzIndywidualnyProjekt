#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
sf::Texture polebeta;
sf::Texture pole_blok; 
int pol_tab[6]={0,0,0,0,0,0}; //tablica na pola sasiednie
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
    virtual std::string get_type() = 0;
    virtual void animacja(int nr_klatki) = 0;
    virtual void load() = 0;
    virtual sf::Texture* tekstura_w_eq() = 0;
    virtual sf::Texture* tekstura_w_postac() = 0;
    virtual sf::Texture* tekstura_w_attack() = 0;
    virtual void initiate_wear() = 0;
};
//Klasa dla broni mele
class Mele :public Item
{
private:
    sf::Texture tekstura_eq;
    sf::Texture tekstura_postac;
    sf::Texture tekstura_attack;
    Staty staty;
    std::string name;
    bool wear = false;
    std::string type = "bron";
public:
    Mele(std::string name) : name(name) {};
    virtual std::string get_type() override { return type; }
    virtual void animacja(int nr_klatki) override
    {
        std::cout << "a";
    }
    //funkcja do inicjacji itemu nie ma potrzeby wywolywac jesli tekstury nie beda potrzebne
    virtual void load() override
    {
        std::fstream plik;
        plik.open(("resources/itemy/" + name + "/" + name + ".txt").c_str(), std::ios::in);
        int dostat[10] = {0,0,0,0,0,0,0,0,0,0};
        std::string linia;
        int count = 0;
        while (getline(plik, linia))
        {
            dostat[count] = std::stoi(linia);
            count++;
        }
        staty = Staty(name, dostat[0], dostat[1], dostat[2], dostat[3], dostat[4], dostat[5], dostat[6], dostat[7], dostat[8], dostat[9]);
        plik.close();
        tekstura_eq.loadFromFile(("resources/itemy/" + name + "/" + name + " eq.png"));
    }
    virtual void initiate_wear() override
    {
        if (!wear)
            tekstura_postac.loadFromFile(("resources/itemy/" + name + "/" + name + " hold.png"));
        wear = true;
    }
    virtual sf::Texture* tekstura_w_eq() override { return &tekstura_eq; }
    virtual sf::Texture* tekstura_w_postac() override { return &tekstura_postac; }
    virtual sf::Texture* tekstura_w_attack() override { return &tekstura_attack; }
};
/*
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
};*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////(end item)

class Hitbox
{
public:
    virtual ~Hitbox() = default;
    virtual bool hit(int x, int y) = 0;
    virtual char get_type() = 0;
};

class Rect :public Hitbox
{
public:
    Rect(int a, int b, int posx, int posy, char type) :a(a), b(b), posx(posx), posy(posy), type(type) {};
    Rect() { a = 0, b = 0, posx = 0, posy = 0, type = 0; };
    virtual bool hit(int x, int y) override
    {
        // std::cout << x << " > " << posx << " " << x << " < " << posx + a << " " << y << " > " << posy << " " << y << " < " << posy + b << "\n";
        return (x > posx && x < posx + a && y > posy && y < posy + b) ? true : false;
    }
    virtual char get_type() override { return type; }
private:
    int a;
    int b;
    int posx;
    int posy;
    char type;
};

class Circle :public Hitbox
{
public:
    Circle(int r, int posx, int posy, char type) :r(r), posx(posx), posy(posy), type(type) {};
    Circle() { r = 0, posx = 0, posy = 0, type = 0; };
    virtual bool hit(int x, int y) override
    {
        return (((x * x) - (2 * posx * x) + (posx * posx) + (y * y) - (2 * posy * y) + (posy * posy)) <= (r * r)) ? true : false;
    }
    virtual char get_type() override { return type; }
private:
    int r;
    int posx;
    int posy;
    char type;
};

//funkcja wykrywajaca ktore pole w ekwiupunku zostalo klikniete
//jesli nie trafi (zadne pole nie klikniete) zwroci 0, wiec mozna zastosowac if
int detekcja_nr_pola_w_ekwipunku(sf::Vector2i pos, int ilosc_itemow)
{
    pos.x -= 620;
    pos.y -= 80;
    //std::cout << pos.x << "a " << pos.y << "\n";
    float porown = float(int(pos.x / 115));
    porown += 1;
    if (porown > 6 || porown < 0)
        return 0;
    if (!(pos.x <= ((porown - 1) * 115 + 80)))
        return 0;
    int zwrotna = int(porown);
    //std::cout << zwrotna << " zwrotna\n";
    porown = float(int(pos.y / 115));
    if (porown + 1 > 7)
        return 0;
    if (!(pos.y <= (porown * 115 + 80)))
        return 0;
    std::cout << (zwrotna + (int(porown) * 6)) << "\n";
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
        for (int i = itemki_w_eq.size()-1; i >= 0 ; i--)
        {
            delete itemki_w_eq[i];
        }
        for (int i = 9; i >= 0; i--)
        {
            if (zalozone[i])
                delete zalozone[i];
        }
        for (int i = hitboxy.size() - 1; i >= 0; i--)
        {
            delete hitboxy[i];
        }
    }
    int ilosc_itemkow_eq() { return itemki_w_eq.size(); }
    //Staty stats;
    std::vector<Item*> itemki_w_eq;
    int nr_klikniety = 0;
    int wear_int(int nr_na_ktory);
    void wear(int nr_na_ktory);
    // 0 - chelm
    // 1 - napiersnik
    // 2 - spodnie
    // 3 - buty
    // 4 - bron
    // 5 - supp
    // 6 - plecak1
    // 7 - plecak2
    // 8 - plecak3
    // 9 - plecak4
    Item* zalozone[10] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
    int posx = 0, posy = 0, nr = 0, movx = 0, movy = 0;
    std::vector<Hitbox*> hitboxy;
    std::string current_map = "mapa";
private:
    
    
    std::vector<std::string> wczytane;

};

void Gracz::wear(int nr_na_ktory)
{
    if (zalozone[nr_na_ktory])
        itemki_w_eq.push_back(zalozone[nr_na_ktory]);
    zalozone[nr_na_ktory] = itemki_w_eq[nr_klikniety - 1];
    //itemki_w_eq.erase(itemki_w_eq.begin() + nr_klikniety - 1);
    itemki_w_eq[nr_klikniety - 1] = itemki_w_eq.back();
    itemki_w_eq.erase(itemki_w_eq.end() - 1);
}

int Gracz::wear_int(int nr_na_ktory)
{
    switch (nr_na_ktory)
    {
    case 0:
        if (itemki_w_eq[nr_klikniety - 1]->get_type() != "chelm")
            return -1;
        break;
    case 1:
        if (itemki_w_eq[nr_klikniety - 1]->get_type() != "napiersnik")
            return -1;
        break;
    case 2:
        if (itemki_w_eq[nr_klikniety - 1]->get_type() != "spodnie")
            return -1;
        break;
    case 3:
        if (itemki_w_eq[nr_klikniety - 1]->get_type() != "buty")
            return -1;
        break;
    case 4:
        if (itemki_w_eq[nr_klikniety - 1]->get_type() != "bron")
            return -1;
        break;
    case 5:
        if (itemki_w_eq[nr_klikniety - 1]->get_type() != "support")
            return -1;
        break;
    }
    
    return nr_na_ktory;
}


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
            itemki_w_eq.back()->load();
        }
    }

}



void move(sf::Sprite* sprite, int* x, int* y, int* mx, int* my, std::vector<Hitbox*> hitboxy)
{
    if (*mx == 0 && *my == 0)
        return;
    for (int i = 0; i < hitboxy.size(); i++)
    {
        //std::cout << "tried\n";
        if ((hitboxy[i]->hit(*x + (*mx / 2) + 945, *y + (*my / 2) + 495) || hitboxy[i]->hit(*x + (*mx / 2) + 955, *y + (*my / 2) + 505)))
        {

            if (hitboxy[i]->get_type() == 87)
            {
                *mx /= 2;
                *my /= 2;
                //std::cout << "true\n";
                move(sprite, x, y, mx, my, hitboxy);
                return;
            }
            if (hitboxy[i]->get_type() == 68)
            {
                *mx = 0;
                *my = 0;
                *x = 0;
                *y = 0;
                return;
            }
        }
    }
    *x += *mx / 2;
    *mx /= 2;
    *y += *my / 2;
    *my /= 2;
    sprite->setTextureRect(sf::IntRect(*x, *y, 1900, 1000));
}

sf::Vector2f pozycja_eq(int nr)
{
    if (nr % 6)
        return sf::Vector2f(((nr % 6) - 1) * 115 + 620, ((nr - (nr % 6)) / 6) * 115 + 80);
    return sf::Vector2f(1195, (nr / 6 - 1) * 115 + 80);
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
    sf::Texture itemback;
    sf::Texture map;
    /////////////////////////////////////////////////////////////////////////////
    //pobiera z pliku
    pole_blok.loadFromFile("resources/poleblok.png");
    polebeta.loadFromFile("resources/betapolee.png");
    map_back.loadFromFile("resources/mapa.png");
    eq_back.loadFromFile("resources/ekwipunek.png");
    itemback.loadFromFile("resources/backgrounditem.png");
    /////////////////////////////////////////////////////////////////////////////
    sf::RenderWindow window(sf::VideoMode(1900, 1000), "Call Of The Tunnels"); //tworzy okno
    window.setFramerateLimit(30); //limit klatek (bez tego komputer plonie)
    Gracz gracz;
    gracz.load();
    sf::CircleShape dot(5);
    dot.setPosition(945, 495);
    dot.setFillColor(sf::Color::Red);

    //int posx = 0, posy = 0, nr = 0, movx = 0, movy = 0;
    std::vector<sf::RectangleShape> beta_obj;
    std::vector<sf::Text> texts; //vectory zawierajace wczytywane obiekty
    std::vector<sf::Sprite> obj;
    std::vector<Pole> pola;
    int state = 0;
    bool change_status = true; //zmienne zarzadzajace wczytywaniem zasobow
    bool odswmap = false;
    bool item_clicked = false;
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
            else if (state == 2) //eq
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

                obj.push_back(sf::Sprite());
                obj.back().setTexture(itemback);
                obj.back().setPosition(sf::Vector2f(1920, 1080));
                obj.back().setColor(sf::Color::Green);

                for (int i = 0; i < 16; i++)
                    obj.push_back(sf::Sprite());
                obj[2].setPosition(sf::Vector2f(1622, 40));
                obj[3].setPosition(sf::Vector2f(1621, 292));
                obj[4].setPosition(sf::Vector2f(1612, 565));
                obj[5].setPosition(sf::Vector2f(1609, 893));
                obj[6].setPosition(sf::Vector2f(1775, 565));
                obj[7].setPosition(sf::Vector2f(1435, 562)); //pozycje eq rozmieszczone w nierownych miejscach
                obj[8].setPosition(sf::Vector2f(1468, 8));
                obj[9].setPosition(sf::Vector2f(1759, 11));
                obj[10].setPosition(sf::Vector2f(1468, 119));
                obj[11].setPosition(sf::Vector2f(1757, 117));

                obj[12].setPosition(sf::Vector2f(146, 0));
                obj[13].setPosition(sf::Vector2f(27, 183));
                obj[14].setPosition(sf::Vector2f(100, 488)); //pozycje eq na postaci
                obj[15].setPosition(sf::Vector2f(64, 804));
                obj[16].setPosition(sf::Vector2f(24, 194));
                obj[17].setPosition(sf::Vector2f(322, 564));

                for (int i = 0; i < gracz.ilosc_itemkow_eq(); i++)
                {
                    obj.push_back(sf::Sprite());
                    obj.back().setTexture(*gracz.itemki_w_eq[i]->tekstura_w_eq());
                    obj.back().setPosition(pozycja_eq(i + 1));
                }
                for (int i = 0; i < 10; i++)
                {
                    if (gracz.zalozone[i])
                        obj[2 + i].setTexture(*gracz.zalozone[i]->tekstura_w_eq());
                }
                for (int i = 0; i < 6; i++)
                {
                    if (gracz.zalozone[i])
                        obj[12 + i].setTexture(*gracz.zalozone[i]->tekstura_w_postac());
                }
            }
            else if (state == 3) //mapa podst
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

                obj.push_back(sf::Sprite());
                map.loadFromFile(("resources/mapy/" + gracz.current_map + "/" + gracz.current_map + ".png").c_str());
                obj[0].setTexture(map);
                obj[0].setTextureRect(sf::IntRect(0, 0, 1900, 1000));
                gracz.posx = 0, gracz.posy = 0, gracz.nr = 0, gracz.movx = 0, gracz.movy = 0;

                std::fstream plik;
                std::vector<std::string> podzielone;
                std::string holder, linia;
                plik.open(("resources/mapy/"+gracz.current_map+"/"+gracz.current_map+".txt").c_str(), std::ios::in);
                while (std::getline(plik, linia))
                {
                    for (int i = 0; i <= linia.size(); i++)
                    {
                        if (i == linia.size() || linia[i] == 32)
                        {
                            podzielone.push_back(holder);
                            //std::cout << holder << "\n";
                            holder = "";
                            continue;
                        }
                        holder += linia[i];
                    }
                }
                int iterator = 0;

                while (iterator < podzielone.size())
                {
                    if (podzielone[iterator] == "R")
                    {
                        gracz.hitboxy.push_back(new Rect(std::stoi(podzielone[iterator + 1]), std::stoi(podzielone[iterator + 2]), std::stoi(podzielone[iterator + 3]), std::stoi(podzielone[iterator + 4]), podzielone[iterator + 5][0]));
                        iterator += 6;
                        continue;
                    }
                    if (podzielone[iterator] == "C")
                    {
                        gracz.hitboxy.push_back(new Circle(std::stoi(podzielone[iterator + 1]), std::stoi(podzielone[iterator + 2]), std::stoi(podzielone[iterator + 3]), podzielone[iterator + 4][0]));
                        iterator += 5;
                        continue;
                    }
                }
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
        if (state == 3 && (gracz.movx || gracz.movy))
        {
            move(&obj[0], &gracz.posx, &gracz.posy, &gracz.movx, &gracz.movy, gracz.hitboxy);
        }
        if (state == 3)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    gracz.movy -= 15;
                else
                    gracz.movy -= 5;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    gracz.movy += 15;
                else
                    gracz.movy += 5;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    gracz.movx += 15;
                else
                    gracz.movx += 5;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    gracz.movx -= 15;
                else
                    gracz.movx -= 5;
            }
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
                else if (state == 2) //eq
                {
                    if (pos.x > 570 && pos.x < 1330 && pos.y > 875 && pos.y < 925) //6
                    {
                        change_status = true;
                        state = 0;
                    }
                    if (detekcja_nr_pola_w_ekwipunku(pos, gracz.ilosc_itemkow_eq()))
                    {
                        item_clicked = true;
                        gracz.nr_klikniety = detekcja_nr_pola_w_ekwipunku(pos, gracz.ilosc_itemkow_eq());
                        obj[1].setPosition(pozycja_eq(detekcja_nr_pola_w_ekwipunku(pos, gracz.ilosc_itemkow_eq())));
                    }
                    if (item_clicked)
                    {
                        int hold = -1;
                        item_clicked = false;
                        if (pos.x >= 1622 && pos.y >= 40 && pos.x <= 1702 && pos.y <= 120) //chelm
                            hold = gracz.wear_int(0);
                        else if (pos.x >= 1621 && pos.y >= 292 && pos.x <= 1701 && pos.y <= 372) //napiersnik
                            hold = gracz.wear_int(1);
                        else if (pos.x >= 1612 && pos.y >= 565 && pos.x <= 1692 && pos.y <= 645) //spodnie
                            hold = gracz.wear_int(2);
                        else if (pos.x >= 1609 && pos.y >= 893 && pos.x <= 1689 && pos.y <= 973) //buty
                            hold = gracz.wear_int(3);
                        else if (pos.x >= 1775 && pos.y >= 565 && pos.x <= 1855 && pos.y <= 645) //bron
                            hold = gracz.wear_int(4);
                        else if (pos.x >= 1435 && pos.y >= 562 && pos.x <= 1515 && pos.y <= 642) //support
                            hold = gracz.wear_int(5);
                        else if (pos.x >= 1468 && pos.y >= 8 && pos.x <= 1548 && pos.y <= 88) //plecak1
                            hold = gracz.wear_int(6);
                        else if (pos.x >= 1759 && pos.y >= 11 && pos.x <= 1839 && pos.y <= 91) //plecak2
                            hold = gracz.wear_int(7);
                        else if (pos.x >= 1468 && pos.y >= 119 && pos.x <= 1548 && pos.y <= 199) //plecak3
                            hold = gracz.wear_int(8);
                        else if (pos.x >= 1757 && pos.y >= 117 && pos.x <= 1837 && pos.y <= 197) //plecak4
                            hold = gracz.wear_int(9);
                        else
                        {
                            item_clicked = true;
                            continue;
                        }
                        obj[1].setPosition(sf::Vector2f(1920, 1080));
                        //obj.erase(obj.begin() +( 11 + gracz.nr_klikniety));
                        //if(12 + gracz.nr_klikniety != obj.size() - 1)
                        if (hold != -1)
                        {
                            obj[18 + gracz.nr_klikniety - 1].setTexture(*obj[obj.size() - 1].getTexture()); //= obj[obj.size()-1];
                            if (gracz.zalozone[hold])
                                obj.back().setTexture(*gracz.zalozone[hold]->tekstura_w_eq());
                            else
                                obj.erase(obj.end() - 1);
                            gracz.wear(hold);
                            gracz.zalozone[hold]->initiate_wear();
                            for (int i = 0; i < gracz.ilosc_itemkow_eq(); i++)
                            {
                                
                                obj[18 + i].setTexture(*gracz.itemki_w_eq[i]->tekstura_w_eq());
                                
                            }
                            for (int i = 0; i < 10; i++)
                            {
                                if (gracz.zalozone[i])
                                    obj[2 + i].setTexture(*gracz.zalozone[i]->tekstura_w_eq());
                            }
                            for (int i = 0; i < 6; i++)
                            {
                                if (gracz.zalozone[i])
                                    obj[12 + i].setTexture(*gracz.zalozone[i]->tekstura_w_postac());
                            }
                        }
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
        //odswiezanie

        for (int i = 0; i < obj.size(); i++)
        {
            if (state == 2 && i >= 2 && i <= 11)
            {
                //if (!gracz.zalozone[i - 2])
                    //continue;
            }
            window.draw(obj[i]);
        }
        for (int i = 0; i < pola.size(); i++)
            window.draw(pola[i].pole);
        for (int i = 0; i < beta_obj.size(); i++)
            window.draw(beta_obj[i]);
        for (int i = 0; i < texts.size(); i++)
            window.draw(texts[i]);
        if (state == 3)
            window.draw(dot);
        window.display();
    }
    
    return 0;
}