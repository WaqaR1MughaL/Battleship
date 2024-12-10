#include <SFML/Graphics.hpp>

void drawGridLines(sf::RenderWindow &w, const int& x_offset, const int& y_offset, const int& grid_size, const int& cell_width);
void drawRectangles(sf::RenderWindow &w, const int& x_offset, const int& y_offset, const int& grid_size, const int& cell_width, const char Grid[10][10]);



void drawGridLines(sf::RenderWindow &w, const int& x_offset, const int& y_offset, const int& grid_size, const int& cell_width)
{

    int lineThickness = 2;
    sf::RectangleShape horizontalLine(sf::Vector2f(grid_size * cell_width, lineThickness));
    horizontalLine.setFillColor(sf::Color::Black);

    sf::RectangleShape verticalLine(sf::Vector2f(lineThickness, grid_size * cell_width));
    verticalLine.setFillColor(sf::Color::Black);
    

    for (int i = 0; i <= grid_size; i++)
    {
        
        horizontalLine.setPosition(x_offset, i * cell_width + y_offset - lineThickness);
        w.draw(horizontalLine);

        verticalLine.setPosition(i * cell_width + x_offset - lineThickness, y_offset);
        w.draw(verticalLine);


    }
}

void drawRectangles(sf::RenderWindow &w, const int& x_offset, const int& y_offset, const int& grid_size, const int& cell_width, const char Grid[10][10])
{
    sf::RectangleShape hit(sf::Vector2f(10, 10));
    hit.setSize(sf::Vector2f(cell_width - 5, cell_width- 5));
    hit.setFillColor(sf::Color(255, 0, 0, 100));
    hit.setOutlineThickness(2);
    sf::RectangleShape miss(sf::Vector2f(10, 10));
    miss.setSize(sf::Vector2f(cell_width - 5, cell_width - 5));
    miss.setFillColor(sf::Color(255, 255, 255, 100));
    miss.setOutlineThickness(1);

    for (int r = 0; r < grid_size; r++)
    {
        for (int c = 0; c < grid_size; c++)
        {
            if (Grid[r][c] == 'H')
            {
                // we add 5 because rectangle size is 70 and cell width is 80. So, 80 - 70 = 10. 10/2 = 5 to center the rectangle in the cell
                hit.setPosition(c * cell_width + x_offset + 2.5, r * cell_width + y_offset + 2.5);
                w.draw(hit);
            }
            else if (Grid[r][c] == 'M')
            {
                miss.setPosition(c * cell_width + x_offset + 2.5, r * cell_width + y_offset + 2.5);
                w.draw(miss);
            }
        }
    }
}