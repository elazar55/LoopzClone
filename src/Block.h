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
            LEFT_INDEX,
            BOTTOM_INDEX,
            RIGHT_INDEX,
            TOP_INDEX,
        };

        // ========================== Constructors =============================
        Block();
        Block(Vector2f pos, float size, const bitset<4> doors = bitset<4>(0));

        // =========================== Inspectors ==============================
        Vector2f  Position() const;
        bool      IsEmpty() const;
        bitset<4> Doors() const;
        Vector2f  Size() const;

        // ============================ Mutators ===============================
        void SetDoors(bitset<4> doors);
        void Move(Vector2f direction);
        void Rotate(float degrees, const Vector2f& origin);
        void Draw(RenderWindow& window);
        void SetColor(sf::Color color);
        template<typename T>
        int Dot(T a, T b, size_t length);
};

#endif
