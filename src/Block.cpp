#include "Block.h"
#include <cmath>
#include <stdlib.h>

Block::Block(int x, int y, int size) :
    x(x), y(y), shape(sf::Vector2f(size, size))
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
    // TODO: Rotate doors
}

void Block::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}