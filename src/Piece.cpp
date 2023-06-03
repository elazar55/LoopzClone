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
        blocks.push_back(Block(BLOCK_CENTER, size, DOOR_TOP | DOOR_BOTTOM));
    }
    else if (mino == S)
    {
        blocks.push_back(Block(BLOCK_CENTER, size, DOOR_LEFT | DOOR_TOP));
        blocks.push_back(Block(BLOCK_TOP, size, DOOR_BOTTOM | DOOR_RIGHT));
        blocks.push_back(Block(BLOCK_TOP_RIGHT, size, DOOR_LEFT | DOOR_RIGHT));
        blocks.push_back(Block(BLOCK_LEFT, size, DOOR_LEFT | DOOR_RIGHT));
    }
    else if (mino == Z)
    {
        blocks.push_back(Block(BLOCK_CENTER, size, DOOR_RIGHT | DOOR_TOP));
        blocks.push_back(Block(BLOCK_TOP, size, DOOR_BOTTOM | DOOR_LEFT));
        blocks.push_back(Block(BLOCK_TOP_LEFT, size, DOOR_RIGHT | DOOR_LEFT));
        blocks.push_back(Block(BLOCK_RIGHT, size, DOOR_LEFT | DOOR_RIGHT));
    }
    else if (mino == Line)
    {
        blocks.push_back(Block(BLOCK_CENTER, size, DOOR_BOTTOM | DOOR_TOP));
        blocks.push_back(Block(BLOCK_BOTTOM, size, DOOR_BOTTOM | DOOR_TOP));
        blocks.push_back(Block(BLOCK_TOP, size, DOOR_BOTTOM | DOOR_TOP));
    }
    else if (mino == J)
    {
        blocks.push_back(Block(BLOCK_CENTER, size, DOOR_TOP | DOOR_BOTTOM));
        blocks.push_back(Block(BLOCK_TOP, size, DOOR_TOP | DOOR_BOTTOM));
        blocks.push_back(Block(BLOCK_BOTTOM, size, DOOR_TOP | DOOR_LEFT));
        blocks.push_back(
            Block(BLOCK_BOTTOM_LEFT, size, DOOR_LEFT | DOOR_RIGHT));
    }
    else if (mino == L)
    {
        blocks.push_back(Block(BLOCK_CENTER, size, DOOR_TOP | DOOR_BOTTOM));
        blocks.push_back(Block(BLOCK_TOP, size, DOOR_TOP | DOOR_BOTTOM));
        blocks.push_back(Block(BLOCK_BOTTOM, size, DOOR_TOP | DOOR_RIGHT));
        blocks.push_back(
            Block(BLOCK_BOTTOM_RIGHT, size, DOOR_LEFT | DOOR_RIGHT));
    }
    else if (mino == U)
    {
        blocks.push_back(Block(BLOCK_CENTER, size, DOOR_TOP | DOOR_BOTTOM));
        blocks.push_back(Block(BLOCK_TOP, size, DOOR_BOTTOM | DOOR_RIGHT));
        blocks.push_back(Block(BLOCK_BOTTOM, size, DOOR_TOP | DOOR_RIGHT));
        blocks.push_back(
            Block(BLOCK_BOTTOM_RIGHT, size, DOOR_LEFT | DOOR_RIGHT));
        blocks.push_back(Block(BLOCK_TOP_RIGHT, size, DOOR_LEFT | DOOR_RIGHT));
    }
    else if (mino == BigZ)
    {
        blocks.push_back(Block(BLOCK_CENTER, size, DOOR_TOP | DOOR_BOTTOM));
        blocks.push_back(Block(BLOCK_TOP, size, DOOR_BOTTOM | DOOR_LEFT));
        blocks.push_back(Block(BLOCK_BOTTOM, size, DOOR_TOP | DOOR_RIGHT));
        blocks.push_back(
            Block(BLOCK_BOTTOM_RIGHT, size, DOOR_LEFT | DOOR_RIGHT));
        blocks.push_back(Block(BLOCK_TOP_LEFT, size, DOOR_LEFT | DOOR_RIGHT));
    }
}

/* ========================================================================== */
/*                                    Draw                                    */
/* ========================================================================== */
void Piece::draw(RenderWindow& window)
{
    for (auto& i : blocks) i.Draw(window);
}

/* ========================================================================== */
/*                                    Move                                    */
/* ========================================================================== */
void Piece::move(Vector2f direction)
{
    for (auto&& i : blocks) i.Move(direction);
}

/* ========================================================================== */
/*                                   Rotate                                   */
/* ========================================================================== */
void Piece::rotate(float degrees)
{
    Vector2f origin = blocks[0].Position();

    for (auto&& i : blocks) i.Rotate(degrees, origin);
}

/* ========================================================================== */
/*                                Get Positions                               */
/* ========================================================================== */
vector<Vector2f> Piece::Positions() const
{
    vector<Vector2f> positions;
    for (auto& i : blocks) positions.push_back(i.Position());

    return positions;
}

/* ========================================================================== */
/*                                 Get Blocks                                 */
/* ========================================================================== */
vector<Block> Piece::Blocks() const
{
    return blocks;
}
