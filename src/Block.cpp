#include "Block.h"

//============================================================
// Constructors
//============================================================
Block::Block() : doors() {}

Block::Block(sf::Vector2f& size) : sf::RectangleShape(size), doors() {}

//============================================================
// Functions
//============================================================
void Block::rotate(float degrees)
{
    sf::RectangleShape::rotate(degrees);
    // TODO: Rotate doors
}