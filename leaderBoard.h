#include <fstream>
#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

string names[50];
int scores[50];
int entries = 0;

void saveScoreInFile(const int& score, const std::string& nameText)
{
    std::ofstream file;
    file.open("leaderboard.txt", std::ios::app);
    file << nameText << "," << score << std::endl;
    file.close();
}


void loadLeaderBoard()
{
    entries = 0;
    std::ifstream file;
    file.open("leaderboard.txt");
    if (!file)
    {
        std::cout << "Error opening file" << std::endl;
    }
    else
    {
        string entry;
        while (getline(file, entry))
        {
            std::istringstream iss(entry);
            if (getline(iss, names[entries], ','))
            {
                iss >> scores[entries];
            }
            entries++;
        }
    }
    file.close();
}

void sortHighestScores()
{
    for (int i = 0; i < entries; i++)
    {
        for (int j = 0; j < entries; j++)
        {
            if (scores[i] > scores[j])
            {
                int tempScore = scores[i];
                scores[i] = scores[j];
                scores[j] = tempScore;

                string tempNameText = names[i];
                names[i] = names[j];
                names[j] = tempNameText;
            }
        }
    }
}


void leaderboard(RenderWindow& window)
{

    loadLeaderBoard();
    sortHighestScores();

    Texture frameTexture;
    frameTexture.loadFromFile("images/leaderboard/frame.png");
    Sprite frame;
    frame.setTexture(frameTexture);
    frame.setPosition(580,50);  

    Texture entryBoxTexture;
    entryBoxTexture.loadFromFile("images/leaderboard/box.png");
    Sprite entryBox[4];
    for (int i = 0; i < 4; i++)
    {
        entryBox[i].setTexture(entryBoxTexture);
        entryBox[i].setScale(1.4, 0.4);   // 236*2 = 472
        entryBox[i].setPosition(680, 200 + i * 100);  // 700 - 472 = 228/2 = 114 + 580 = 694
    }

    Texture scoreBoxTexture;
    scoreBoxTexture.loadFromFile("images/leaderboard/box2.png");
    Sprite scoreBox[4];
    for (int i = 0; i < 4; i++)
    {
        scoreBox[i].setTexture(scoreBoxTexture);
        scoreBox[i].setScale(0.4, 0.5);   // 236*2 = 472
        scoreBox[i].setPosition(1055, 275 + i * 100);  // 700 - 472 = 228/2 = 114 + 580 = 694
    }
    scoreBox[0].setScale(0.5, 0.5);
    scoreBox[0].setPosition(1045, 275);

    Text nameText[4];
    Font font;
    font.loadFromFile("fonts/RebellionSquad.ttf");
    for (int i = 0; i < 4; i++)
    {
        nameText[i].setFont(font);
        nameText[i].setCharacterSize(30);
        nameText[i].setFillColor(Color::Red);
        nameText[i].setString(to_string(i+1) + ".   " + names[i]);
        nameText[i].setPosition(700, 375 + i * 100);
    }
    nameText[3].setString("PLAYER NAMES:");
    nameText[3].setPosition(700, 275);


    Text scoreText[4];
    for (int i = 0; i < 4; i++)
    {
        scoreText[i].setFont(font);
        scoreText[i].setCharacterSize(25);
        scoreText[i].setFillColor(Color::White);
        scoreText[i].setString(to_string(scores[i]));
        scoreText[i].setPosition(1080, 375 + i * 100);
    }
    scoreText[3].setString("SCORES");
    scoreText[3].setPosition(1060, 275);


    while (window.isOpen())
    {
        
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();


        }

        window.clear(Color(22, 72, 124));
        window.draw(frame);

        
        for (int i = 0; i < 4; i++)
        {
            window.draw(entryBox[i]);
            window.draw(scoreBox[i]);
        }

        for (int i = 0; i < 4; i++)
        {
            window.draw(nameText[i]);
            window.draw(scoreText[i]);
        }
        
        window.display();
    }
}