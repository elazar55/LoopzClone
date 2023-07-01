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
Piece::Piece(float x, float y, float size)
{
    vector<Block> temp;
    // 0
    temp.push_back(Block(BLOCK_CENTER, size, DOOR_TOP | DOOR_BOTTOM));
    ShapeRepo_.push_back(temp);
    temp.clear();
    // 1
    temp.push_back(Block(BLOCK_CENTER, size, DOOR_TOP | DOOR_LEFT));
    ShapeRepo_.push_back(temp);
    temp.clear();
    // 2
    temp.push_back(Block(BLOCK_CENTER, size, DOOR_TOP | DOOR_RIGHT));
    ShapeRepo_.push_back(temp);
    temp.clear();
    // 3
    temp.push_back(Block(BLOCK_CENTER, size, DOOR_LEFT | DOOR_TOP));
    temp.push_back(Block(BLOCK_TOP, size, DOOR_BOTTOM | DOOR_RIGHT));
    temp.push_back(Block(BLOCK_TOP_RIGHT, size, DOOR_LEFT | DOOR_RIGHT));
    temp.push_back(Block(BLOCK_LEFT, size, DOOR_LEFT | DOOR_RIGHT));
    ShapeRepo_.push_back(temp);
    temp.clear();
    // 4
    temp.push_back(Block(BLOCK_CENTER, size, DOOR_RIGHT | DOOR_TOP));
    temp.push_back(Block(BLOCK_TOP, size, DOOR_BOTTOM | DOOR_LEFT));
    temp.push_back(Block(BLOCK_TOP_LEFT, size, DOOR_RIGHT | DOOR_LEFT));
    temp.push_back(Block(BLOCK_RIGHT, size, DOOR_LEFT | DOOR_RIGHT));
    ShapeRepo_.push_back(temp);
    temp.clear();
    // 5
    temp.push_back(Block(BLOCK_CENTER, size, DOOR_BOTTOM | DOOR_TOP));
    temp.push_back(Block(BLOCK_BOTTOM, size, DOOR_BOTTOM | DOOR_TOP));
    temp.push_back(Block(BLOCK_TOP, size, DOOR_BOTTOM | DOOR_TOP));
    ShapeRepo_.push_back(temp);
    temp.clear();
    // 6
    temp.push_back(Block(BLOCK_CENTER, size, DOOR_TOP | DOOR_BOTTOM));
    temp.push_back(Block(BLOCK_TOP, size, DOOR_TOP | DOOR_BOTTOM));
    temp.push_back(Block(BLOCK_BOTTOM, size, DOOR_TOP | DOOR_LEFT));
    temp.push_back(Block(BLOCK_BOTTOM_LEFT, size, DOOR_LEFT | DOOR_RIGHT));
    ShapeRepo_.push_back(temp);
    temp.clear();
    // 7
    temp.push_back(Block(BLOCK_CENTER, size, DOOR_TOP | DOOR_BOTTOM));
    temp.push_back(Block(BLOCK_TOP, size, DOOR_TOP | DOOR_BOTTOM));
    temp.push_back(Block(BLOCK_BOTTOM, size, DOOR_TOP | DOOR_RIGHT));
    temp.push_back(Block(BLOCK_BOTTOM_RIGHT, size, DOOR_LEFT | DOOR_RIGHT));
    ShapeRepo_.push_back(temp);
    temp.clear();
    // 8
    temp.push_back(Block(BLOCK_CENTER, size, DOOR_TOP | DOOR_BOTTOM));
    temp.push_back(Block(BLOCK_TOP, size, DOOR_BOTTOM | DOOR_RIGHT));
    temp.push_back(Block(BLOCK_BOTTOM, size, DOOR_TOP | DOOR_RIGHT));
    temp.push_back(Block(BLOCK_BOTTOM_RIGHT, size, DOOR_LEFT | DOOR_RIGHT));
    temp.push_back(Block(BLOCK_TOP_RIGHT, size, DOOR_LEFT | DOOR_RIGHT));
    ShapeRepo_.push_back(temp);
    temp.clear();
    // 9
    temp.push_back(Block(BLOCK_CENTER, size, DOOR_TOP | DOOR_BOTTOM));
    temp.push_back(Block(BLOCK_TOP, size, DOOR_BOTTOM | DOOR_LEFT));
    temp.push_back(Block(BLOCK_BOTTOM, size, DOOR_TOP | DOOR_RIGHT));
    temp.push_back(Block(BLOCK_BOTTOM_RIGHT, size, DOOR_LEFT | DOOR_RIGHT));
    temp.push_back(Block(BLOCK_TOP_LEFT, size, DOOR_LEFT | DOOR_RIGHT));
    ShapeRepo_.push_back(temp);
    // temp.clear();

    blocks_ = ShapeRepo_[RandomInt(ShapeRepo_.size())];
}

// -----------------------------------------------------------------------------
//                                 Random Int
// -----------------------------------------------------------------------------
int Piece::RandomInt(int max)
{
    return rand() % max;
}

/* ========================================================================== */
/*                                    Draw                                    */
/* ========================================================================== */
void Piece::draw(RenderWindow& window)
{
    for (auto& i : blocks_) i.Draw(window);
}

/* ========================================================================== */
/*                                    Move                                    */
/* ========================================================================== */
void Piece::move(Vector2f direction)
{
    for (auto&& i : blocks_) i.Move(direction);
}

/* ========================================================================== */
/*                                   Rotate                                   */
/* ========================================================================== */
void Piece::rotate(float degrees)
{
    Vector2f origin = blocks_[0].Position();

    for (auto&& i : blocks_) i.Rotate(degrees, origin);
}

/* ========================================================================== */
/*                                Get Positions                               */
/* ========================================================================== */
vector<Vector2f> Piece::Positions() const
{
    vector<Vector2f> positions;
    for (auto& i : blocks_) positions.push_back(i.Position());

    return positions;
}

/* ========================================================================== */
/*                                 Get Blocks                                 */
/* ========================================================================== */
vector<Block> Piece::Blocks() const
{
    return blocks_;
}
