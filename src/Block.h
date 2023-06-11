/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#ifndef BLOCK_H
#define BLOCK_H
#include <bitset>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

#define DOOR_NON    bitset<4>(0)
#define DOOR_TOP    bitset<4>(8) // 1 0 0 0
#define DOOR_RIGHT  bitset<4>(4) // 0 1 0 0
#define DOOR_BOTTOM bitset<4>(2) // 0 0 1 0
#define DOOR_LEFT   bitset<4>(1) // 0 0 0 1

#define BLOCK_CENTER       Vector2f(x, y)
#define BLOCK_TOP          Vector2f(x, y - size)
#define BLOCK_BOTTOM       Vector2f(x, y + size)
#define BLOCK_LEFT         Vector2f(x - size, y)
#define BLOCK_RIGHT        Vector2f(x + size, y)
#define BLOCK_TOP_RIGHT    Vector2f(x + size, y - size)
#define BLOCK_TOP_LEFT     Vector2f(x - size, y - size)
#define BLOCK_BOTTOM_LEFT  Vector2f(x - size, y + size)
#define BLOCK_BOTTOM_RIGHT Vector2f(x + size, y + size)

/* ========================================================================== */
/*                                 Class Block                                */
/* ========================================================================== */
class Block
{
    private:
        Vector2f       position_;
        bitset<4>      doors_;
        RectangleShape shape_;

    public:
        enum Door
        {
            TOP_INDEX,
            RIGHT_INDEX,
            BOTTOM_INDEX,
            LEFT_INDEX,
        };

        Block();
        Block(Vector2f pos, float size, const bitset<4> doors = bitset<4>(0));

        Vector2f  Position() const;
        Vector2f  Size() const;
        void      SetDoors(bitset<4> doors);
        bitset<4> Doors() const;
        void      Move(Vector2f direction);
        void      Rotate(float degrees, const Vector2f& origin);
        void      Draw(RenderWindow& window);
        bool      IsEmpty() const;
        void      SetColor(sf::Color color);

        template<typename T>
        int Dot(T a, T b, size_t length);
};

#endif