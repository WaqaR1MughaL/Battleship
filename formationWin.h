#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void setShipWhenMousePressed(Sprite &sprite, Ship &ship, int& cell_width, int& x_offset, int& y_offset, int& row, int& col)
{
    if ( ship.orientation == 'V')
    {
        sprite.setPosition(col * cell_width + x_offset + cell_width/2, row * cell_width + y_offset);
    }
    else
        sprite.setPosition(col * cell_width + x_offset, row * cell_width + y_offset + cell_width/2);

    ship.col = col;
    ship.row = row;
}


void rotateSpriteAndSetPosition(Sprite &sprite,  Ship &ship, int& mouseX, int& mouseY, int& cell_width, int& x_offset, int& y_offset, int& row, int& col)
{
    if (ship.orientation == 'V')
    {
        sprite.setRotation(0);

    }
    else
    {
        sprite.setRotation(-90);

    }
}

void drawUnplacedShip(RenderWindow &win, Sprite &sprite)
{
    sprite.setPosition(sf::Mouse::getPosition(win).x, sf::Mouse::getPosition(win).y);
    win.draw(sprite);
}

int if_R_pressed(RenderWindow &formWin, Ship &ship, Sprite &sprite, int& mouseX, int& mouseY, int& cell_width, int& x_offset, int& y_offset, int& row, int& col)
{
        if (ship.orientation == 'V')
        {
            ship.orientation = 'H';
            rotateSpriteAndSetPosition(sprite, ship, mouseX, mouseY, cell_width, x_offset, y_offset, row, col);
            return true;

        }
        else
        {
            ship.orientation = 'V';
            rotateSpriteAndSetPosition(sprite, ship, mouseX, mouseY, cell_width, x_offset, y_offset, row, col);
            return true;
        }
    return false;
}


void formationWindow(char grid[10][10], RenderWindow &formWin, Ship& Aircraftcarrier, Ship& Battleship, Ship& Cruiser, Ship& Destroyer, Ship& Submarine)
{
 
    int window_width = 1920;
    int window_height = 1080;
    
    int grid_size = 10;
    int cell_width = 80;
    int x_offset = ( window_width - grid_size * cell_width ) / 2;
    int y_offset = ( window_height - grid_size * cell_width ) / 2;

    int row;
    int col;

    bool isAircraftCarrierPlaced = false;
    bool isBattleshipPlaced = false;
    bool isCruiserPlaced = false;
    bool isDestroyerPlaced = false;
    bool isSubmarinePlaced = false;
    bool isRotate = false;
    bool isFormationComplete = false;

    // origanally the ships sprites are vertical
    Aircraftcarrier.orientation = 'V';
    Battleship.orientation = 'V';
    Cruiser.orientation = 'V';
    Destroyer.orientation = 'V';
    Submarine.orientation = 'V';


    Texture bgTexture;
    bgTexture.loadFromFile("images/background.png");
    Sprite bg(bgTexture);
    bg.setScale(3.334, 3.334);

        //  declaring the textures for the ships
    sf::Texture aircraftCarrierTexture;
    sf::Texture battleshipTexture;
    sf::Texture cruiserTexture;
    sf::Texture destroyerTexture;
    sf::Texture submarineTexture;

    // load the textures for the ships
    aircraftCarrierTexture.loadFromFile("images/A.png");
    battleshipTexture.loadFromFile("images/B.png");
    cruiserTexture.loadFromFile("images/C.png");
    destroyerTexture.loadFromFile("images/D.png");
    submarineTexture.loadFromFile("images/S.png");

    // declaring the player 1 ships sprites
    sf::Sprite A;
    sf::Sprite B;
    sf::Sprite C;
    sf::Sprite D;
    sf::Sprite S;

    //adding texture to player 1 ships sprites
    A.setTexture(aircraftCarrierTexture);
    A.setOrigin(40, 0);
    B.setTexture(battleshipTexture);
    B.setOrigin(40, 0);
    C.setTexture(cruiserTexture);
    C.setOrigin(40, 0);
    D.setTexture(destroyerTexture);
    D.setOrigin(40, 0);
    S.setTexture(submarineTexture);
    S.setOrigin(40, 0);

    while (formWin.isOpen() && !isFormationComplete)
    {

        Event event;

        formWin.clear();
        formWin.draw(bg);

        drawGridLines(formWin, x_offset, y_offset, grid_size, cell_width);

        if (isAircraftCarrierPlaced)
            formWin.draw(A);
        if (isBattleshipPlaced)
            formWin.draw(B);
        if (isCruiserPlaced)
            formWin.draw(C);
        if (isDestroyerPlaced)
            formWin.draw(D);
        if (isSubmarinePlaced)
            formWin.draw(S);    


        if (!isAircraftCarrierPlaced)
        {
            drawUnplacedShip(formWin, A);
        }
        else if (!isBattleshipPlaced)
        {
            drawUnplacedShip(formWin, B);
        }
        else if (!isCruiserPlaced)
        {
            drawUnplacedShip(formWin, C);
        }
        else if (!isDestroyerPlaced)
        {
            drawUnplacedShip(formWin, D);
        }
        else if (!isSubmarinePlaced)
        {
            drawUnplacedShip(formWin, S);
        }
        else
        {
            isFormationComplete = true;
        }

        while (formWin.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                formWin.close();
            }

            if (event.type == Event::MouseButtonPressed)
            {        
                if (event.mouseButton.button == Mouse::Left)
                {
                    if (event.mouseButton.x > x_offset && event.mouseButton.x < x_offset + grid_size * cell_width)
                    {
                        if (event.mouseButton.y > y_offset && event.mouseButton.y < y_offset + grid_size * cell_width)
                        {
                            processClick(event.mouseButton.x, event.mouseButton.y, row, col, cell_width, x_offset, y_offset, grid);
                            // cout << "Mouse X: " << event.mouseButton.x << " Mouse Y: " << event.mouseButton.y << endl;
                            // cout << "Row: " << row << " Col: " << col << endl;
                        }
                    }

                    if (!isAircraftCarrierPlaced)
                    {
                        if (!isCellOccupied(row, col, Aircraftcarrier.orientation, 5, grid))
                        {
                            storeTypeInPlayerGrid('A', Aircraftcarrier.orientation, 5, row, col, grid);

                            setShipWhenMousePressed(A, Aircraftcarrier , cell_width, x_offset, y_offset, row, col);
                            isAircraftCarrierPlaced = true;
                            // cout << "Aircraft carrier placed" << endl;
                        }    
                    }
                    else if (!isBattleshipPlaced)
                    {
                        if (!isCellOccupied(row, col, Battleship.orientation, 4, grid))
                        {    
                            storeTypeInPlayerGrid('B', Battleship.orientation, 4, row, col, grid);
                            setShipWhenMousePressed(B, Battleship, cell_width, x_offset, y_offset, row, col);
                            isBattleshipPlaced = true;
                            // cout << "Battleship placed" << endl;
                        }    
                    }
                    else if (!isCruiserPlaced)
                    {
                        if (!isCellOccupied(row, col, Cruiser.orientation, 3, grid))
                        {
                            storeTypeInPlayerGrid('C', Cruiser.orientation, 3, row, col, grid);;
                            setShipWhenMousePressed(C, Cruiser, cell_width, x_offset, y_offset, row, col);
                            isCruiserPlaced = true;
                            // cout << "Cruiser placed" << endl;
                        }
                      }
                    else if (!isDestroyerPlaced)
                    {
                        if (!isCellOccupied(row, col, Destroyer.orientation, 2, grid))
                        {
                            storeTypeInPlayerGrid('D', Destroyer.orientation, 2, row, col, grid);
                           setShipWhenMousePressed(D, Destroyer, cell_width, x_offset, y_offset, row, col);
                            isDestroyerPlaced = true;
//                            cout << "Destroyer placed" << endl;
                        }
                    }
                    else if (!isSubmarinePlaced)
                    {
                        if (!isCellOccupied(row, col, Submarine.orientation, 3, grid))
                        {
                            storeTypeInPlayerGrid('S', Submarine.orientation, 3, row, col, grid);
                            setShipWhenMousePressed(S, Submarine, cell_width, x_offset, y_offset, row, col);
                            isSubmarinePlaced = true;
                            // cout << "Submarine placed" << endl;
                        }
                    }
                }
            }

            if (event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::R))
            {
                if (!isAircraftCarrierPlaced)
                    if_R_pressed(formWin, Aircraftcarrier, A, event.mouseButton.x, event.mouseButton.y, cell_width, x_offset, y_offset, row, col);
                else if (!isBattleshipPlaced)
                    if_R_pressed(formWin, Battleship, B, event.mouseButton.x, event.mouseButton.y, cell_width, x_offset, y_offset, row, col);
                else if (!isCruiserPlaced)
                    if_R_pressed(formWin, Cruiser, C, event.mouseButton.x, event.mouseButton.y, cell_width, x_offset, y_offset, row, col);
                else if (!isDestroyerPlaced)
                    if_R_pressed(formWin, Destroyer, D, event.mouseButton.x, event.mouseButton.y, cell_width, x_offset, y_offset, row, col);
                else if (!isSubmarinePlaced)
                    if_R_pressed(formWin, Submarine, S, event.mouseButton.x, event.mouseButton.y, cell_width, x_offset, y_offset, row, col);
            }
        }
    formWin.display();
    }
}
