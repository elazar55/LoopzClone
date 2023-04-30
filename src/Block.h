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
        bool doors[4];
        RectangleShape shape;

    public:
        Block();
        Block(int x, int y, int size);

        Vector2i getPosition();
        Vector2i getSize();
        void move(int x, int y);
        void rotate(float degrees, Vector2i& origin);
        void draw(RenderWindow& window);

        template<typename T>
        int Dot(T* a, T* b, size_t length);
};

#endif