#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void loadingPage(RenderWindow &window)
{

    Texture bgtexture;
    bgtexture.loadFromFile("images/loading.png");    
    Sprite bg(bgtexture);
    
    Text countdown;
    Font font;
    font.loadFromFile("fonts/RebellionSquad.ttf");
    countdown.setFont(font);
    countdown.setCharacterSize(40);
    countdown.setFillColor(Color(227, 103, 7));
    countdown.setPosition(604, 770);

    
    RectangleShape boundary(Vector2f(658, 38));
    boundary.setFillColor(Color::White);
    boundary.setPosition(604, 826);

    RectangleShape loadingBar[100];
    for (int i = 0; i < 100; i++)
    {
        loadingBar[i].setSize(Vector2f(i*6.5, 30));
        loadingBar[i].setFillColor(Color(227, 103, 7));
        loadingBar[i].setPosition(610, 830);
    }
    int i = 0;
    window.setFramerateLimit(60);
    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(bg);
        if (i/2 < 100)
        {
            countdown.setString("Loading.........." + to_string(i/2) + "%");
            window.draw(countdown);
            window.draw(boundary);
            window.draw(loadingBar[i/2]);
            i++;
        }
        else
        {
            break;
        }
        window.display();
    }

}