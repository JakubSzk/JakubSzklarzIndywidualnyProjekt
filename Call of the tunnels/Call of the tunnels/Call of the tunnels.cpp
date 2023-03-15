#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

int main()
{
    sf::Font font;
    font.loadFromFile("resources/Jack.ttf"); //czcionka

    //wczytywanie tekstur
    /////////////////////////////////////////////////////////////////////////////
    //tworzy zmienne tekstur
    
    /////////////////////////////////////////////////////////////////////////////
    //pobiera z pliku

    /////////////////////////////////////////////////////////////////////////////
    sf::RenderWindow window(sf::VideoMode(1900, 1000), "Call Of The Tunnels"); //tworzy okno
    window.setFramerateLimit(30); //limit klatek (bez tego komputer plonie)
   
    std::vector<sf::RectangleShape> beta_obj;
    std::vector<sf::Text> texts; //vectory zawierajace wczytywane obiekty
    std::vector<sf::Sprite> obj;

    int state = 0;
    bool change_status = true; //zmienne zarzadzajace wczytywaniem zasobow

    sf::Vector2i pos;

    while (window.isOpen())
    {
        if (change_status) //wczytywanie
        {
            beta_obj.clear();
            obj.clear(); //reset
            texts.clear();

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

            case 1:
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
        for (int i = 0; i < beta_obj.size(); i++)
            window.draw(beta_obj[i]);
        for (int i = 0; i < obj.size(); i++)
            window.draw(obj[i]);
        for (int i = 0; i < texts.size(); i++)
            window.draw(texts[i]);
        window.display();
    }

    return 0;
}