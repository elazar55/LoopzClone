#ifndef BLOCK_H
#define BLOCK_H
#include <SFML/Graphics.hpp>

//============================================================
// Block
//============================================================
class Block : public sf::RectangleShape
{
    private:
        //============================================================
        // Members
        //============================================================
        bool doors[4];

    public:
        //============================================================
        // Constructor
        //============================================================
        Block();
        Block(sf::Vector2f& size);

        //============================================================
        // Functions
        //============================================================
        void rotate(float degrees);
};

#endif