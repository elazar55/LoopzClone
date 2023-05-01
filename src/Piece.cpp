/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#include "Piece.h"
#include <iostream>
using namespace std;
using namespace sf;

/* ========================================================================== */
/*                                 Constructor                                */
/* ========================================================================== */
Piece::Piece(int x, int y, int size, Mino mino)
{
    ConstructMino(x, y, size, mino);
}

/* ========================================================================== */
/*                                ConstructMino                               */
/* ========================================================================== */
void Piece::ConstructMino(int x, int y, int size, Piece::Mino mino)
{
    if (mino == Random)
    {
        mino = Mino(rand() % Random);
    }
    if (mino == Single)
    {
        blocks.push_back(Block(Vector2f(x, y), size));
    }
    else if (mino == S)
    {
        blocks.push_back(Block(Vector2f(x, y), size));
        blocks.push_back(Block(Vector2f(x, y - size), size));
        blocks.push_back(Block(Vector2f(x + size, y - size), size));
        blocks.push_back(Block(Vector2f(x - size, y), size));
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
void Piece::rotate(int degrees)
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
