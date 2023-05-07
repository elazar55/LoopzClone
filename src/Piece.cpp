/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#include "Piece.h"
#include <iostream>
using namespace std;
using namespace sf;
// clang-format off

#define NONE {0, 0, 0, 0}
#define TOP {1, 0, 0, 0}
#define RIGHT {0, 1, 0, 0}
#define BOTTOM {0, 0, 1, 0}
#define LEFT {0, 0, 0, 1}

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
    if (mino == Random)
    {
        mino = Mino(rand() % Random);
    }
    if (mino == Single)
    {
        blocks.push_back(
            Block(Vector2f(x, y), size, (const bool[4]){0, 0, 0, 1}));
    }
    else if (mino == S)
    {
        blocks.push_back(Block(Vector2f(x, y), size));               // Center
        blocks.push_back(Block(Vector2f(x, y - size), size));        // Top
        blocks.push_back(Block(Vector2f(x + size, y - size), size)); // TopRight
        blocks.push_back(Block(Vector2f(x - size, y), size)); // Bottom Left
    }
    else if (mino == Z)
    {
        blocks.push_back(Block(Vector2f(x, y), size));
        blocks.push_back(Block(Vector2f(x, y - size), size));
        blocks.push_back(Block(Vector2f(x - size, y - size), size));
        blocks.push_back(Block(Vector2f(x + size, y), size));
    }
    else if (mino == Line)
    {
        blocks.push_back(Block(Vector2f(x, y), size));
        blocks.push_back(Block(Vector2f(x, y + size), size));
        blocks.push_back(Block(Vector2f(x, y - size), size));
    }
    else if (mino == J)
    {
        ConstructMino(x, y, size, Line);
        blocks.push_back(Block(Vector2f(x + size, y + size), size));
    }
    else if (mino == L)
    {
        ConstructMino(x, y, size, Line);
        blocks.push_back(Block(Vector2f(x - size, y + size), size));
    }
    else if (mino == U)
    {
        ConstructMino(x, y, size, J);
        blocks.push_back(Block(Vector2f(x + size, y - size), size));
    }
    else if (mino == BigZ)
    {
        ConstructMino(x, y, size, J);
        blocks.push_back(Block(Vector2f(x - size, y - size), size));
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
