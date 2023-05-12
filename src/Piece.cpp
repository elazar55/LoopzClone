/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#include "Piece.h"
#include <iostream>
using namespace std;
using namespace sf;
// clang-format off

#define DOOR_NON    (const bool[]){0, 0, 0, 0}
#define DOOR_TOP    (const bool[]){1, 0, 0, 0}
#define DOOR_RIGHT  (const bool[]){0, 1, 0, 0}
#define DOOR_BOTTOM (const bool[]){0, 0, 1, 0}
#define DOOR_LEFT   (const bool[]){0, 0, 0, 1}

#define BLOCK_CENTER       Vector2f(x, y)
#define BLOCK_TOP          Vector2f(x, y - size)
#define BLOCK_BOTTOM       Vector2f(x, y + size)
#define BLOCK_LEFT         Vector2f(x - size, y)
#define BLOCK_RIGHT        Vector2f(x + size, y)
#define BLOCK_TOP_RIGHT    Vector2f(x + size, y - size)
#define BLOCK_TOP_LEFT     Vector2f(x - size, y - size)
#define BLOCK_BOTTOM_LEFT  Vector2f(x - size, y + size)
#define BLOCK_BOTTOM_RIGHT Vector2f(x + size, y + size)

// clang-format on

/* ========================================================================== */
/*                                 Constructor                                */
/* ========================================================================== */
Piece::Piece(float x, float y, float size, Mino mino)
{
    ConstructMino(x, y, size, mino);
}

/* ========================================================================== */
/*                                ConstructMino                               */
/* ========================================================================== */
void Piece::ConstructMino(float x, float y, float size, Piece::Mino mino)
{
    // Center
    blocks.push_back(Block(Vector2f(x, y), size));

    if (mino == Random)
    {
        mino = Mino(rand() % Random);
    }

    if (mino == Single)
    {
        blocks.back().setDoors(DOOR_TOP);
    }
    else if (mino == S)
    {
        blocks.push_back(Block(BLOCK_TOP, size));
        blocks.push_back(Block(BLOCK_TOP_RIGHT, size, DOOR_RIGHT));
        blocks.push_back(Block(BLOCK_LEFT, size, DOOR_LEFT));
    }
    else if (mino == Z)
    {
        blocks.push_back(Block(BLOCK_TOP, size));
        blocks.push_back(Block(BLOCK_TOP_LEFT, size, DOOR_LEFT));
        blocks.push_back(Block(BLOCK_RIGHT, size, DOOR_RIGHT));
    }
    else if (mino == Line)
    {
        blocks.push_back(Block(BLOCK_BOTTOM, size, DOOR_BOTTOM));
        blocks.push_back(Block(BLOCK_TOP, size, DOOR_TOP));
    }
    else if (mino == J)
    {
        blocks.push_back(Block(BLOCK_TOP, size, DOOR_TOP));
        blocks.push_back(Block(BLOCK_BOTTOM, size));
        blocks.push_back(Block(BLOCK_BOTTOM_LEFT, size, DOOR_LEFT));
    }
    else if (mino == L)
    {
        blocks.push_back(Block(BLOCK_TOP, size, DOOR_TOP));
        blocks.push_back(Block(BLOCK_BOTTOM, size));
        blocks.push_back(Block(BLOCK_BOTTOM_RIGHT, size, DOOR_RIGHT));
    }
    else if (mino == U)
    {
        blocks.push_back(Block(BLOCK_TOP, size));
        blocks.push_back(Block(BLOCK_BOTTOM, size));
        blocks.push_back(Block(BLOCK_BOTTOM_RIGHT, size, DOOR_RIGHT));
        blocks.push_back(Block(BLOCK_TOP_RIGHT, size, DOOR_RIGHT));
    }
    else if (mino == BigZ)
    {
        blocks.push_back(Block(BLOCK_TOP, size));
        blocks.push_back(Block(BLOCK_BOTTOM, size));
        blocks.push_back(Block(BLOCK_BOTTOM_RIGHT, size, DOOR_RIGHT));
        blocks.push_back(Block(BLOCK_TOP_LEFT, size, DOOR_LEFT));
    }
}

/* ========================================================================== */
/*                                    Draw                                    */
/* ========================================================================== */
void Piece::draw(RenderWindow& window)
{
    // Forwards to individual blocks
    for (auto& i : blocks) i.draw(window);
}

/* ========================================================================== */
/*                                    Move                                    */
/* ========================================================================== */
void Piece::move(Vector2f direction)
{
    // Forwards to individual blocks
    for (auto&& i : blocks) i.move(direction);
}

/* ========================================================================== */
/*                                   Rotate                                   */
/* ========================================================================== */
void Piece::rotate(float degrees)
{
    // Forwards to individual blocks
    Vector2f origin = blocks[0].getPosition();

    for (auto&& i : blocks) i.rotate(degrees, origin);
}

/* ========================================================================== */
/*                                Get Positions                               */
/* ========================================================================== */
vector<Vector2f> Piece::getPositions()
{
    vector<Vector2f> positions;
    for (auto& i : blocks) positions.push_back(i.getPosition());

    return positions;
}

/* ========================================================================== */
/*                                 Get Blocks                                 */
/* ========================================================================== */
vector<Block> Piece::getBlocks()
{
    return blocks;
}
