/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#ifndef BLOCK_H
#define BLOCK_H
#include <bitset>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

/* ========================================================================== */
/*                                 Class Block                                */
/* ========================================================================== */
class Block
{
    private:
        Vector2f       m_pos;
        bitset<4>      m_doors;
        RectangleShape shape;

    public:
        Block();
        Block(Vector2f pos, float size, const bitset<4> doors = bitset<4>(0));

        Vector2f getPosition();
        Vector2f getSize();
        void     setDoors(const bitset<4> doors);
        void     move(Vector2f direction);
        void     rotate(float degrees, Vector2f& origin);
        void     draw(RenderWindow& window);

        template<typename T, typename U>
        int Dot(T a, U b, size_t length);
};

#endif