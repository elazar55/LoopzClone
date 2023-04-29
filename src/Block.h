/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#ifndef BLOCK_H
#define BLOCK_H
#include <SFML/Graphics.hpp>
using namespace sf;

/* ========================================================================== */
/*                                 Class Block                                */
/* ========================================================================== */
class Block
{
    private:
        int x;
        int y;
        int xIndex;
        int yIndex;
        bool doors[4];
        sf::RectangleShape shape;

    public:
        Block();
        Block(int x, int y, int size);

        Vector2i getPosition();
        Vector2i getIndices();
        void move(int x, int y);
        void rotate(float degrees, sf::Vector2i& origin);
        void draw(sf::RenderWindow& window);

        template<typename T>
        int Dot(T* a, T* b, size_t length);
};

#endif