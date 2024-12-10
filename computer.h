#include <iostream>
#include <SFML/Audio.hpp>
#include <ctime>

using namespace std;
using namespace sf;


bool isCellAttacked(const char Grid[10][10], const int& row, const int& col)
{
    if (Grid[row][col] == 'H' || Grid[row][col] == 'M')
    {
        return true;
    }
    return false;
}


bool isHit(const char Grid[10][10], const int& row, const int& col)
{
    if (Grid[row][col] == 'H')
    {
        return true;
    }
    return false;
}


int rand_row, rand_col;
int sur_row, sur_col;
int line_row, line_col;
bool isRand = true, isSurr = false, isLine = false;
bool isUp = true, isDown = true, isLeft = true, isRight = true;
bool isHorizontal = true, isVertical = true;



int computerAttack(char playerGrid[10][10], int& aircraftCarrierSpaces, int& battleshipSpaces, int& cruiserSpaces, int& destroyerSpaces, int& submarineSpaces, Sound& shoot_sound, Sound& splash_sound, Sound& explosion_sound)
{
    srand(time(0));
    if (isRand)
    {
        isSurr = false, isLine = false;
        isUp = true, isDown = true, isLeft = true, isRight = true;
        isHorizontal = true, isVertical = true;

        do
        {
            rand_row = rand() % 10;
            rand_col = rand() % 10;
            // cout << "Random:  " << rand_row << " " << rand_col << playerGrid[rand_row][rand_col] << endl;

        } while (isCellAttacked(playerGrid, rand_row, rand_col));

        trackTargetedShipHealth(aircraftCarrierSpaces, battleshipSpaces, cruiserSpaces, destroyerSpaces, submarineSpaces, rand_row, rand_col, playerGrid);    
        saveAttackInGrid(playerGrid, rand_row, rand_col, shoot_sound, splash_sound, explosion_sound);


        if (isHit(playerGrid, rand_row, rand_col))
        {

            isRand = false;
            isSurr = true;
            isRight = true, isLeft = true, isUp = true, isDown = true;
            sur_row = rand_row;
            sur_col = rand_col;
        }

        return 0;

    }
    else if (isSurr)
    {
        if (isUp)
        {
            if (sur_row == 0)
            {
                isUp = false;
            }
            else
            {
                if (!isCellAttacked(playerGrid, sur_row - 1, sur_col))
                {
                    // cout << "Up: " << sur_row - 1 << " " << sur_col << endl;

                    trackTargetedShipHealth(aircraftCarrierSpaces, battleshipSpaces, cruiserSpaces, destroyerSpaces, submarineSpaces, sur_row-1, sur_col, playerGrid);    
                    saveAttackInGrid(playerGrid, sur_row - 1, sur_col, shoot_sound, splash_sound, explosion_sound);

                    if (isHit(playerGrid, sur_row - 1, sur_col))
                    {
                        isVertical = true;
                        isHorizontal = false;
                        isLine = true;
                        line_row = sur_row - 1;
                        line_col = sur_col;
                        isSurr = false;

                    }
                    else
                    {
                        isUp = false;
                    }
                    return 0;
                }
                else
                {
                    isUp = false;
                }
            }

        }
        if (isDown)
        {
            if (sur_row == 9)
            {
                isDown = false;
            }
            else
            {
                if (!isCellAttacked(playerGrid, sur_row + 1, sur_col))
                {
                    // cout << "Down: " << sur_row + 1 << " " << sur_col << endl;
                    trackTargetedShipHealth(aircraftCarrierSpaces, battleshipSpaces, cruiserSpaces, destroyerSpaces, submarineSpaces, sur_row + 1, sur_col, playerGrid);
                    saveAttackInGrid(playerGrid, sur_row + 1, sur_col, shoot_sound, splash_sound, explosion_sound);

                    if (isHit(playerGrid, sur_row + 1, sur_col))
                    {
                        isVertical = true;
                        line_row = sur_row + 1;
                        line_col = sur_col;
                        isHorizontal = false;
                        isLine = true;
                        isSurr = false;

                    }
                    else
                    {
                        isDown = false;
                        isVertical = false;
                    }
                    return 0;
                }
                else
                {
                    isDown = false;
                }
            }
        }
        if (isLeft)
        {
            if (sur_col == 0)
            {
                isLeft = false;
            }
            else
            {
                if (!isCellAttacked(playerGrid, sur_row, sur_col - 1))
                {
                    // cout << "Left: " << sur_row << " " << sur_col - 1 << endl;

                    trackTargetedShipHealth(aircraftCarrierSpaces, battleshipSpaces, cruiserSpaces, destroyerSpaces, submarineSpaces, sur_row, sur_col - 1, playerGrid);
                    saveAttackInGrid(playerGrid, sur_row, sur_col - 1, shoot_sound, splash_sound, explosion_sound);

                    if (isHit(playerGrid, sur_row, sur_col - 1))
                    {
                        isHorizontal = true;
                        line_row = sur_row;
                        line_col = sur_col - 1;
                        isVertical = false;
                        isLine = true;
                        isSurr = false;

                    }
                    else
                    {
                        isLeft = false;
                    }
                    return 0;
                }
                else
                {
                    isLeft = false;
                }
            }
        }
        if (isRight)
        {
            if (sur_col == 9)
            {
                isRight = false;
            }
            else
            {
                if (!isCellAttacked(playerGrid, sur_row, sur_col + 1))
                {
                    // cout << "Right: " << sur_row << " " << sur_col + 1 << endl;
                    trackTargetedShipHealth(aircraftCarrierSpaces, battleshipSpaces, cruiserSpaces, destroyerSpaces, submarineSpaces, sur_row, sur_col+1, playerGrid);
                    saveAttackInGrid(playerGrid, sur_row, sur_col + 1, shoot_sound, splash_sound, explosion_sound);

                    if (isHit(playerGrid, sur_row, sur_col + 1))
                    {
                        isHorizontal = true;
                        line_row = sur_row;
                        line_col = sur_col + 1;
                        isVertical = false;
                        isLine = true;
                        isSurr = false;

                    }
                    else
                    {
                        isRight = false;
                        isHorizontal = false;
                    }
                    return 0;
                }
                else
                {
                    isRight = false;
                }
            }
        }

        if (!isUp && !isDown && !isLeft && !isRight)
        {
            isSurr = false;
            isUp = true, isDown = true, isLeft = true, isRight = true;
            isRand = true;
            // cout << "Surrounding is false" << endl;
            computerAttack(playerGrid, aircraftCarrierSpaces, battleshipSpaces, cruiserSpaces, destroyerSpaces, submarineSpaces, shoot_sound, splash_sound, explosion_sound);
            return 0;
        }
    }
    else if (isLine)
    {
        if (isVertical)
        {
            if (isUp)
            {
                if (line_row == 0)
                {
                    isUp = false;
                    line_row = sur_row;

                }
                else
                {
                    if (!isCellAttacked(playerGrid, line_row - 1, line_col))
                    {
                        // cout << "Up: " << line_row - 1 << " " << line_col << endl;
                        trackTargetedShipHealth(aircraftCarrierSpaces, battleshipSpaces, cruiserSpaces, destroyerSpaces, submarineSpaces, line_row-1, line_col, playerGrid);
                        saveAttackInGrid(playerGrid, line_row - 1, line_col, shoot_sound, splash_sound, explosion_sound);

                        if (isHit(playerGrid, line_row - 1, line_col))
                        {
                            line_row = line_row - 1;
                        }
                        else
                        {
                            isUp = false;
                            line_row = sur_row;
                        }
                        return 0;
                    }
                    else
                    {
                        isUp = false;
                        line_row = sur_row;
                    }

                }
                
            }
            if (isDown)
            {
                if (line_row == 9)
                {
                    isDown = false;
                    isRand = true;
                    computerAttack(playerGrid, aircraftCarrierSpaces, battleshipSpaces, cruiserSpaces, destroyerSpaces, submarineSpaces, shoot_sound, splash_sound, explosion_sound);
                    return 0;
                }
                else
                {
                    if (!isCellAttacked(playerGrid, line_row + 1, line_col))
                    {
                        // cout << "Down: " << line_row + 1 << " " << line_col << endl;
                        trackTargetedShipHealth(aircraftCarrierSpaces, battleshipSpaces, cruiserSpaces, destroyerSpaces, submarineSpaces, line_row + 1, line_col, playerGrid);
                        saveAttackInGrid(playerGrid, line_row + 1, line_col, shoot_sound, splash_sound, explosion_sound);

                        if (isHit(playerGrid, line_row + 1, line_col))
                        {
                            line_row = line_row + 1;
                        }
                        else
                        {
                            isDown = false;
                            isRand = true;
                        }
                        return 0;
                    }
                    else
                    {
                        isDown = false;
                        isRand = true;
                        computerAttack(playerGrid, aircraftCarrierSpaces, battleshipSpaces, cruiserSpaces, destroyerSpaces, submarineSpaces, shoot_sound, splash_sound, explosion_sound);
                        return 0;
                    }
                }
                
            }

        }
        if (isHorizontal)
        {
            if (isLeft)
            {
                if (line_col == 0)
                {
                    isLeft = false;
                    line_col = sur_col;
                }
                else
                {
                    if (!isCellAttacked(playerGrid, line_row, line_col - 1))
                    {
                        // cout << "Left: " << line_row << " " << line_col - 1 << endl;

                        trackTargetedShipHealth(aircraftCarrierSpaces, battleshipSpaces, cruiserSpaces, destroyerSpaces, submarineSpaces, line_row, line_col - 1, playerGrid);
                        saveAttackInGrid(playerGrid, line_row, line_col - 1, shoot_sound, splash_sound, explosion_sound);

                        if (isHit(playerGrid, line_row, line_col - 1))
                        {
                            line_col = line_col - 1;
                        }
                        else
                        {
                            isLeft = false;
                            line_col = sur_col;
                        }
                        return 0;
                    }
                    else
                    {
                        isLeft = false;
                        line_col = sur_col;
                    }
                }
                
            }
            if (isRight)
            {
                if (line_col == 9)
                {
                    isRight = false;
                    isRand = true;
                    computerAttack(playerGrid, aircraftCarrierSpaces, battleshipSpaces, cruiserSpaces, destroyerSpaces, submarineSpaces, shoot_sound, splash_sound, explosion_sound);
                    return 0;
                }
                else
                {
                    if (!isCellAttacked(playerGrid, line_row, line_col + 1))
                    {
                        // cout << "Right: " << line_row << " " << line_col + 1 << endl;
                        trackTargetedShipHealth(aircraftCarrierSpaces, battleshipSpaces, cruiserSpaces, destroyerSpaces, submarineSpaces, line_row, line_col+1, playerGrid);
                        saveAttackInGrid(playerGrid, line_row, line_col + 1, shoot_sound, splash_sound, explosion_sound);
                        
                        if (isHit(playerGrid, line_row, line_col + 1))
                        {
                            line_col = line_col + 1;
                        }
                        else
                        {
                            isRight = false;
                            isRand = true;
                        }
                        return 0;
                    }
                    else
                    {
                        isRight = false;
                        isRand = true;
                        computerAttack(playerGrid, aircraftCarrierSpaces, battleshipSpaces, cruiserSpaces, destroyerSpaces, submarineSpaces, shoot_sound, splash_sound, explosion_sound);
                        return 0;
                    }
                }
            }
        }

    }  
    return 0;  
}
