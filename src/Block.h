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
        Vector2f       m_pos;
        bool           m_doors[4];
        RectangleShape shape;

    public:
        Block();
        Block(Vector2f pos, float size, const bool doors[4] = {0});

        Vector2f getPosition();
        Vector2f getSize();
        void     move(Vector2f direction);
        void     rotate(float degrees, Vector2f& origin);
        void     draw(RenderWindow& window);

        template<typename T>
        int Dot(T* a, T* b, size_t length);
};

#endif