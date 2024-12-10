#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int gameModeScreen(RenderWindow &window, string &gameMode, Sound &click_sound)
{

	Font font;
	font.loadFromFile("fonts/SuperPixel.ttf");

	Text text1;
	text1.setFont(font);
	text1.setString("PLAYER VS PLAYER");
	text1.setCharacterSize(40);
	text1.setFillColor(Color(211, 17, 46));
	text1.setPosition(1920 / 2, 250);
	text1.setOrigin(text1.getLocalBounds().width/2,text1.getLocalBounds().height/2);

    Text text2;
	text2.setFont(font);
	text2.setString("PLAYER VS COMPUTER");
	text2.setCharacterSize(40);
	text2.setFillColor(Color(211, 17, 46));
	text2.setPosition(1920 / 2, 500);
	text2.setOrigin(text2.getLocalBounds().width / 2, text2.getLocalBounds().height / 2);

    Text text3;
	text3.setFont(font);
	text3.setString("EXIT GAME");
	text3.setCharacterSize(40);
	text3.setFillColor(Color(211, 17, 46));
	text3.setPosition(1920 / 2, 750);
	text3.setOrigin(text3.getLocalBounds().width / 2, text3.getLocalBounds().height / 2);

	Texture Main;
	Main.loadFromFile("images/starting/openingBg.jpg");
	Sprite main_win;
	main_win.setTexture(Main);
	main_win.setScale(1.2007, 1.201);
	main_win.setOrigin(main_win.getLocalBounds().width / 2, main_win.getLocalBounds().height / 2);
	main_win.setPosition(1920 / 2, 1080 / 2);

	Texture Button;
	Button.loadFromFile("images/starting/play_262_70.png");
	
	Sprite button1,button2,button3;
	button1.setTexture(Button);
	button1.setOrigin(button1.getGlobalBounds().width / 2, button1.getGlobalBounds().height / 2);
	button1.setPosition(1920 / 2, 258);
	button1.setScale(2.6, 1.5);

	button2.setTexture(Button);
	button2.setOrigin(button2.getGlobalBounds().width / 2, button2.getGlobalBounds().height / 2);
	button2.setPosition(1920 / 2, 508);
	button2.setScale(2.5, 1.5);

	button3.setTexture(Button);
	button3.setOrigin(button3.getGlobalBounds().width / 2, button3.getGlobalBounds().height / 2);
	button3.setPosition(1920 / 2, 758);
	button3.setScale(1.8, 1.5);



	

	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		Event E1;
		while (window.pollEvent(E1))
		{
			Vector2i m_pos = Mouse::getPosition(window);
			Vector2f m_posf(static_cast<float>(m_pos.x), static_cast<float>(m_pos.y));
			if (E1.type == Event::Closed)
			{
				window.close();
			}
			
			if (button1.getGlobalBounds().contains(m_posf))
			{
				button1.setScale(2.7, 1.6);
				text1.setFillColor(Color::Blue);
				if ((E1.type == Event::MouseButtonPressed) && (E1.mouseButton.button == Mouse::Left))
				{
					cout << "Text Clicked!" << endl;
					gameMode = "player_vs_player";
					click_sound.play();
                    return 0;
				}
			}
			else
			{
				button1.setScale(2.6, 1.5);
				text1.setFillColor(Color(211, 17, 46));
			}
			if (button2.getGlobalBounds().contains(m_posf))
			{
				button2.setScale(2.8, 1.6);
				text2.setFillColor(Color::Blue);
				if ((E1.type == Event::MouseButtonPressed) && (E1.mouseButton.button == Mouse::Left))
				{
					cout << "Text Clicked!" << endl;
					gameMode = "player_vs_computer";
					click_sound.play();
                    return 0;
				}
			}
			else
			{
				button2.setScale(2.7, 1.5);
				text2.setFillColor(Color(211, 17, 46));
			}
			if (button3.getGlobalBounds().contains(m_posf))
			{
				button3.setScale(1.9, 1.6);
				text3.setFillColor(Color::Blue);
				if ((E1.type == Event::MouseButtonPressed) && (E1.mouseButton.button == Mouse::Left))
				{
					cout << "Text Clicked!" << endl;
					click_sound.play();
                    window.close();
					return 0;
				}
			}
			else
			{
				button3.setScale(1.8, 1.5);
				text3.setFillColor(Color(211, 17, 46));
			}

		}

		window.clear(Color::White);
		window.draw(main_win);
		window.draw(button1);
		window.draw(button2);
		window.draw(button3);
		window.draw(text1);
		window.draw(text2);
		window.draw(text3);
		window.display();
	}
    return 0;
}

///////////////////////////////////////////////////////////////////

int startingScreen(RenderWindow &window, string &gameMode, string &player1Name, string &player2Name, Sound &click_sound)
{

    Texture openingBgTexture;
    if (!openingBgTexture.loadFromFile("images/starting/openingBg.jpg"))
    {
        std::cout << "Error loading opening background texture\n";
    }
    Sprite openingBg(openingBgTexture);
    openingBg.setScale(1.2007, 1.201);

    Texture ButtonTexture;
    if (!ButtonTexture.loadFromFile("images/starting/play_262_70.png"))
    {
        std::cout << "Error loading play button texture\n";
    }
    Sprite Button(ButtonTexture);  
    Button.setOrigin(262 / 2, 70 / 2);
    Button.setScale(2, 1.5);
    Button.setPosition(912, 500);

    Text play;
    Font font;
    if (!font.loadFromFile("fonts/SuperPixel.ttf"))
    {
        std::cout << "Error loading font\n";
    }
    play.setFont(font);
    play.setString("PLAY GAME");
    play.setCharacterSize(50);
    play.setFillColor(Color::Red);
    play.setOrigin(350 / 2, 70 / 2);
    play.setPosition(912, 500);

    Text mode;
    mode.setFont(font);
    mode.setString("Select game mode");
    mode.setCharacterSize(50);
    mode.setFillColor(Color(211, 17, 46));
    mode.setOrigin(600 / 2, 70 / 2);
    mode.setPosition(912, 200);

/////////////////////////////////////////////
    Text player1NameText;
    player1NameText.setFont(font);
    player1NameText.setString("ONE: ");
    player1NameText.setCharacterSize(40);
    player1NameText.setFillColor(Color::Red);
    player1NameText.setPosition(610, 340);

    Texture player1NameBoxTexture;
    if (!player1NameBoxTexture.loadFromFile("images/starting/play_262_70.png"))
    {
        std::cout << "Error loading player 1 name box texture\n";
    }
    Sprite player1NameBox(player1NameBoxTexture);
    player1NameBox.setOrigin(262 / 2, 70 / 2);
    player1NameBox.setScale(2, 1.5);
    player1NameBox.setPosition(648, 366);
    
///////////////////////////////////////////////////////////    
    Text player2NameText;
    player2NameText.setFont(font);
    player2NameText.setString("TWO: ");
    player2NameText.setCharacterSize(40);
    player2NameText.setFillColor(Color::Red);
    player2NameText.setPosition(1180, 540);

    Texture player2NameBoxTexture;
    if (!player2NameBoxTexture.loadFromFile("images/starting/play_262_70.png"))
    {
        std::cout << "Error loading player 2 name box texture\n";
    }
    Sprite player2NameBox(player2NameBoxTexture);
    player2NameBox.setOrigin(262 / 2, 70 / 2);
    player2NameBox.setScale(2, 1.5);
    player2NameBox.setPosition(1222, 566);

    bool isButton = true;
    bool isMode = false;
    bool isEnterNames = false;
    bool isName1 = true, isName2 = true;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (isButton && Mouse::getPosition(window).x > 650 && Mouse::getPosition(window).x < 650 + 524 && Mouse::getPosition(window).y > 450 && Mouse::getPosition(window).y < 450 + 105)
            {
                play.setFillColor(Color::Green);
                play.setCharacterSize(55);
                play.setPosition(880, 500);
                Button.setScale(2.1, 1.6);

                if (event.type == Event::MouseButtonPressed)
                {
                        // cout << "Play button clicked" << endl;
                        click_sound.play();
                        isButton = false;
                        isMode = true;                        
                }
            }
            else
            {
                play.setFillColor(Color::Red);
                play.setCharacterSize(50);
                play.setPosition(912, 500);
                Button.setScale(2, 1.5);
            }

            
        
            if (isMode)
            {
                gameModeScreen(window, gameMode, click_sound);
                isMode = false;
                isEnterNames = true;
            }


            if (isEnterNames)
            {
                if (isName1 && event.type == Event::TextEntered)
                {
                    if (event.text.unicode >= 65 && event.text.unicode <= 90 || event.text.unicode >= 97 && event.text.unicode <= 122)
                    {
                        player1Name += event.text.unicode;
                    }
                    if (event.text.unicode == 8) // 8 is the backspace key
                    {
                        player1Name = player1Name.substr(0, player1Name.size() - 1);
                        player1NameText.setPosition(player1NameText.getPosition().x + 20, player1NameText.getPosition().y);
                    }   
                    player1NameText.setString(player1Name);
                    player1NameText.setPosition(player1NameText.getPosition().x - 10, player1NameText.getPosition().y);
                    if (event.text.unicode == '\r') // '\r' is the Enter key
                    {
                        // remove the last character which is the Enter key
                        player1Name = player1Name.substr(0, player1Name.size() - 1);
                        isName1 = false;
                    }
                }
                else if (isName2 && event.type == Event::TextEntered)
                {
                    if (event.text.unicode >= 65 && event.text.unicode <= 90 || event.text.unicode >= 97 && event.text.unicode <= 122)
                    {
                        player2Name += event.text.unicode;
                    }
                    if (event.text.unicode == 8) // 8 is the backspace key
                    {
                        player2Name = player2Name.substr(0, player2Name.size() - 1);
                        player2NameText.setPosition(player2NameText.getPosition().x + 20, player2NameText.getPosition().y);
                    }
                    player2NameText.setString(player2Name);
                    player2NameText.setPosition(player2NameText.getPosition().x - 10, player2NameText.getPosition().y);
                    if (event.text.unicode == '\r') // '\r' is the Enter key
                    {
                        // remove the last character which is the Enter key
                        player2Name = player2Name.substr(0, player2Name.size() - 1);
                        isName2 = false;
                        return 0;
                    }
                }
            }
        }

        window.clear();
        window.draw(openingBg);
        if (isButton)
        {
            window.draw(Button);
            window.draw(play);
        }
        else if (isEnterNames)
        {
            window.draw(player1NameBox);
            window.draw(player1NameText);
            window.draw(player2NameBox);
            window.draw(player2NameText);
        }

        window.display();
    }
    return 0;
}

