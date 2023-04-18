/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#ifndef BLOCK_H
#define BLOCK_H
#include <SFML/Graphics.hpp>

/* ========================================================================== */
/*                                 Class Block                                */
/* ========================================================================== */
class Block
{
    private:
        int x;
        int y;
        bool doors[4];
        sf::RectangleShape shape;

    public:
        Block() = default;
        Block(int x, int y, int size);

        sf::Vector2i getPosition();
        void move(int x, int y);
        void rotate(float degrees, sf::Vector2i& origin);
        void draw(sf::RenderWindow& window);
};

#endif