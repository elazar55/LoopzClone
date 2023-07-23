/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#ifndef PIECE_H
#define PIECE_H
#include "Block.h"
#include <iostream>

using namespace std;
using namespace sf;

#define DOOR_NON    bitset<4>(0)
#define DOOR_TOP    bitset<4>(8)  // 1 0 0 0
#define DOOR_RIGHT  bitset<4>(4)  // 0 1 0 0
#define DOOR_BOTTOM bitset<4>(2)  // 0 0 1 0
#define DOOR_LEFT   bitset<4>(1)  // 0 0 0 1
#define DOOR_HORZ   bitset<4>(5)  // 0 1 0 1
#define DOOR_VERT   bitset<4>(10) // 1 0 1 0

#define BLOCK_CENTER       Vector2f(0, 0)
#define BLOCK_TOP          Vector2f(0, -1)
#define BLOCK_BOTTOM       Vector2f(0, 1)
#define BLOCK_LEFT         Vector2f(-1, 0)
#define BLOCK_RIGHT        Vector2f(1, 0)
#define BLOCK_TOP_RIGHT    Vector2f(1, -1)
#define BLOCK_TOP_LEFT     Vector2f(-1, -1)
#define BLOCK_BOTTOM_LEFT  Vector2f(-1, 1)
#define BLOCK_BOTTOM_RIGHT Vector2f(1, 1)

struct PieceRepo
{
        static vector<vector<Vector2f>>  shapes;
        static vector<vector<bitset<4>>> doors;
};

/* ========================================================================== */
/*                                 Class Piece                                */
/* ========================================================================== */
class Piece
{
    private:
        vector<Block> blocks_;
        int           RandomInt(int max);
        Vector2f      origin_;

    public:
        Piece();
        Piece(float x, float y, float size);
        vector<Block>    Blocks() const;
        vector<Vector2f> Positions() const;
        void             draw(RenderWindow& window);
        void             move(Vector2f direction);
        void             rotate(float degrees);
};

#endif
