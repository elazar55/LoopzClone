#ifndef BLOCK_H
#define BLOCK_H

//////////////////////////////////////////////////////////////
// Headers
//////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>

//////////////////////////////////////////////////////////////
// Individual Block
//////////////////////////////////////////////////////////////
class Block : public sf::RectangleShape
{
    private:
        bool doors[4];

    public:
        Block();

        Block(sf::Vector2f& size) : doors(), sf::RectangleShape(size) {}

        void rotate(float degrees)
        {
            sf::RectangleShape::rotate(degrees);
            // TODO: Rotate doors
        }
};

#endif // BLOCK_H
