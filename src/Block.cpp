/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#include "Block.h"
#include <cmath>
#include <stdlib.h>

/* ========================================================================== */
/*                                 Constructor                                */
/* ========================================================================== */
Block::Block(int x, int y, int size) :
    x(x), y(y), doors{true}, shape(sf::Vector2f(size, size))
{
    shape.setPosition(sf::Vector2f(x, y));
    shape.setFillColor(sf::Color::Green);
    shape.setOutlineColor(sf::Color::Blue);
    shape.setOutlineThickness(-5.f);
}

sf::Vector2i Block::getPosition()
{
    return sf::Vector2i(x, y);
}

void Block::move(int x, int y)
{
    this->x += x;
    this->y += y;
    shape.setPosition(sf::Vector2f(this->x, this->y));
}

/* ========================================================================== */
/*                                   Rotate                                   */
/* ========================================================================== */
void Block::rotate(float degrees, sf::Vector2i& origin)
{
    const double PI = 3.13159265358979323;
    double radians  = degrees * PI / 180.f;
    double sinTheta = std::round(std::sin(radians));
    double cosTheta = std::round(std::cos(radians));

    int localx = x - origin.x;
    int localy = y - origin.y;

    x = (localx * cosTheta) + (localy * -sinTheta);
    y = (localx * sinTheta) + (localy * cosTheta);

    x += origin.x;
    y += origin.y;

    shape.setPosition(sf::Vector2f(x, y));

    bool copy[4];
    for (size_t i = 0; i < sizeof(doors); i++) copy[i] = doors[i];

    bool matrix[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    };

    for (size_t i = 0; i < sizeof(doors); i++)
    {
        int j = i + sinTheta;
        if (j == 4) j = 0;
        if (j == -1) j = 3;

        doors[i] = (copy[0] * matrix[0][j]) + (copy[1] * matrix[1][j]) +
                   (copy[2] * matrix[2][j]) + (copy[3] * matrix[3][j]);
    }
}

/* ========================================================================== */
/*                                    Draw                                    */
/* ========================================================================== */
void Block::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}