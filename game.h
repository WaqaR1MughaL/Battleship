#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;
using namespace sf;

struct Ship
{
    char type;
    char orientation;
    int spaces;
    int row;
    int col;
};


void determineSpaces(const char& type, int& spaces);
void storeTypeInPlayerGrid(const char& type, const char& orientation, const int& spaces, int& row, int& col, char grid[10][10]);
bool isCellOccupied(const int& row, const int& col, const char& orientation, const int& spaces, char grid[10][10]);
void generateComputerGridRandomly(Ship& Aircraftcarrier, Ship& Battleship, Ship& Cruiser, Ship& Destroyer, Ship& Submarine, char grid[10][10]);
void processClick(const int& mouseX, const int& mouseY, int& attacked_row, int& attacked_col, const int& cell_width, const int& x_offset, const int& y_offset, const char Grid[10][10]);
void saveAttackInGrid(char Grid[10][10], const int& row, const int& col, Sound& shoot_sound, Sound& splash_sound, Sound& explosion_sound);
bool isSwitchPlayer(bool& isPlayer1, bool& isPlayer2, const char Grid[10][10], const int& row, const int& col);
void trackTargetedShipHealth(int& aircraftCarrierSpaces, int& battleshipSpaces, int& cruiserSpaces, int& destroyerSpaces, int& submarineSpaces, const int& attacked_row, const int& attacked_col, const char Grid[10][10]);
bool isWon(const int& aircraftCarrierSpaces, const int& battleshipSpaces, const int& cruiserSpaces, const int& destroyerSpaces, const int& submarineSpaces);





void determineSpaces(const char& type, int& spaces)
{
    switch (type)
    {
        case 'A': spaces = 5; break;
        case 'B': spaces = 4; break;
        case 'C': spaces = 3; break;
        case 'D': spaces = 2; break;
        case 'S': spaces = 3; break;
    
    }
}
    

void storeTypeInPlayerGrid(const char& type, const char& orientation, const int& spaces, int& row, int& col, char grid[10][10])
{
    if(orientation == 'H')
    {
        for (int i = 0; i < spaces; i++)
        {
            grid[row][col+i] = type;
        }
    }
    else if(orientation == 'V')
    {
        for (int i = 0; i < spaces; i++)
        {
            grid[row+i][col] = type;
        }
    }
}

// check if there is already a ship in the cell
bool isCellOccupied(const int& row, const int& col, const char& orientation, const int& spaces, char grid[10][10])
{
    int grid_size = 10;    
    if( ( grid_size - col < spaces && orientation == 'H' ) || ( grid_size - row < spaces && orientation == 'V' ) )
    {
        return true;
    }
    
    if (orientation == 'H')
    {
        for (int i = 0; i < spaces; i++)
        {
            if (grid[row][col + i] != '0')
            {
                return true;
            }
        }
    }
    else if (orientation == 'V')
    {
        for (int i = 0; i < spaces; i++)
        {
            if (grid[row + i][col] != '0')
            {
                return true;
            }
        }
    }
    return false;
}

void generateComputerGridRandomly(Ship& Aircraftcarrier, Ship& Battleship, Ship& Cruiser, Ship& Destroyer, Ship& Submarine, char grid[10][10])
{
    // Generate the grid randomly
    srand(time(0));
    int row;
    int col;
    char orientation[2] = {'H', 'V'};


    Aircraftcarrier.orientation = orientation[rand() % 2];
    Aircraftcarrier.spaces = 5;
    do{
        row = rand() % 10;
        col = rand() % 10;
    } while (isCellOccupied(row, col, Aircraftcarrier.orientation, Aircraftcarrier.spaces, grid));
    Aircraftcarrier.type = 'A';
    Aircraftcarrier.row = row;
    Aircraftcarrier.col = col;
    storeTypeInPlayerGrid(Aircraftcarrier.type, Aircraftcarrier.orientation, Aircraftcarrier.spaces, Aircraftcarrier.row, Aircraftcarrier.col, grid);

    Battleship.orientation = orientation[rand() % 2];
    Battleship.spaces = 4;
    do{
        row = rand() % 10;
        col = rand() % 10;
    } while (isCellOccupied(row, col, Battleship.orientation, Battleship.spaces, grid));
    Battleship.type = 'B';
    Battleship.row = row;
    Battleship.col = col;
    storeTypeInPlayerGrid(Battleship.type, Battleship.orientation, Battleship.spaces, Battleship.row, Battleship.col, grid);

    Cruiser.orientation = orientation[rand() % 2];
    Cruiser.spaces = 3;
    do{
        row = rand() % 10;
        col = rand() % 10;
    } while (isCellOccupied(row, col, Cruiser.orientation, Cruiser.spaces, grid));
    Cruiser.type = 'C';
    Cruiser.row = row;
    Cruiser.col = col;
    storeTypeInPlayerGrid(Cruiser.type, Cruiser.orientation, Cruiser.spaces, Cruiser.row, Cruiser.col, grid);

    Destroyer.orientation = orientation[rand() % 2];
    Destroyer.spaces = 2;
    do{
        row = rand() % 10;
        col = rand() % 10;
    } while (isCellOccupied(row, col, Destroyer.orientation, Destroyer.spaces, grid));
    Destroyer.type = 'D';
    Destroyer.row = row;
    Destroyer.col = col;
    storeTypeInPlayerGrid(Destroyer.type, Destroyer.orientation, Destroyer.spaces, Destroyer.row, Destroyer.col, grid);

    Submarine.orientation = orientation[rand() % 2];
    Submarine.spaces = 3;
    do{
        row = rand() % 10;
        col = rand() % 10;
    } while (isCellOccupied(row, col, Submarine.orientation, Submarine.spaces, grid));
    Submarine.type = 'S';
    Submarine.row = row;
    Submarine.col = col;
    storeTypeInPlayerGrid(Submarine.type, Submarine.orientation, Submarine.spaces, Submarine.row, Submarine.col, grid);
}


// attacking the opponent's grid and updating the grid
void saveAttackInGrid(char Grid[10][10] ,const int& row, const int& col, Sound& shoot_sound, Sound& splash_sound, Sound& explosion_sound)
{

    shoot_sound.play();
    sf::sleep(sf::milliseconds(500)); 
    if (Grid[row][col] != '0' && Grid[row][col] != 'H' && Grid[row][col] != 'M')
    {
        explosion_sound.play();
        sf::sleep(sf::milliseconds(1000));
        Grid[row][col] = 'H';
    }
    else if (Grid[row][col] == '0')
    {
        splash_sound.play();
        sf::sleep(sf::milliseconds(1000));
        Grid[row][col] = 'M';
    }
    

}

bool  isSwitchPlayer(bool& isPlayer1, bool& isPlayer2, const char Grid[10][10], const int& row, const int& col)
{
    //if the grid value is 0 or A or B or C or D or S, then switch the player
    //if the grid value is other than 0, A, B, C, D, S, then do not switch the player
    if (Grid[row][col] != 'H' && Grid[row][col] != 'M')
    {
        bool temp = isPlayer1;
        isPlayer1 = isPlayer2;  
        isPlayer2 = temp;
        return true;
    }
    return false;
}

// Process the mouse click. Only for the opponent's grid. Because the player click on the opponent's grid to attack. So we have to calculate the cell that was clicked and update the text to display the click coordinates and the opponent's grid value where the mouse was clicked
void processClick(const int& mouseX, const int& mouseY, int& attacked_row, int& attacked_col, const int& cell_width, const int& x_offset, const int& y_offset, const char Grid[10][10])
{

    //x gives the column number and y gives the row number because on the screen, the x-axis is the horizontal axis and the y-axis is the vertical axis.
    //mouseX gives the x-coordinate of the mouse click and mouseY gives the y-coordinate of the mouse click
    //therefore when we divide 
    attacked_col = (mouseX - x_offset) / cell_width;
    attacked_row = (mouseY - y_offset) / cell_width;
    //cout << "Attacked row: " << attacked_row << " Attacked col: " << attacked_col << endl;
}

//this functions will track the ship witch is targeted through grid cell value and update the ship health (spaces) accordingly
void trackTargetedShipHealth(int& aircraftCarrierSpaces, int& battleshipSpaces, int& cruiserSpaces, int& destroyerSpaces, int& submarineSpaces, const int& attacked_row, const int& attacked_col, const char Grid[10][10])
{
    if (Grid[attacked_row][attacked_col] == 'A')
    {
       aircraftCarrierSpaces--; 
    }
    else if (Grid[attacked_row][attacked_col] == 'B')
    {
        battleshipSpaces--;
    }
    else if (Grid[attacked_row][attacked_col] == 'C')
    {
        cruiserSpaces--;
    }
    else if (Grid[attacked_row][attacked_col] == 'D')
    {
        destroyerSpaces--;
    }
    else if (Grid[attacked_row][attacked_col] == 'S')
    {
        submarineSpaces--;
    }
}

bool isWon(const int& aircraftCarrierSpaces, const int& battleshipSpaces, const int& cruiserSpaces, const int& destroyerSpaces, const int& submarineSpaces)
{
    if (aircraftCarrierSpaces == 0 && battleshipSpaces == 0 && cruiserSpaces == 0 && destroyerSpaces == 0 && submarineSpaces == 0)
    {
        return true;
    }
    return false;
}
