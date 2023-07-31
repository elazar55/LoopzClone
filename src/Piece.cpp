/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#include "Piece.h"
#include <iostream>
using namespace std;
using namespace sf;

// =============================================================================
//                                 Piece Repo
// =============================================================================
vector<vector<Vector2f>> PieceRepo::shapes{
    { BLOCK_CENTER }, // Single v1
    { BLOCK_CENTER }, // Single v2
    { BLOCK_CENTER }, // Single v3
    { BLOCK_CENTER, BLOCK_TOP, BLOCK_BOTTOM }, // Line
    { BLOCK_CENTER, BLOCK_BOTTOM_LEFT, BLOCK_BOTTOM, BLOCK_RIGHT }, // S
    { BLOCK_CENTER, BLOCK_BOTTOM_RIGHT, BLOCK_BOTTOM, BLOCK_LEFT }, // Z
    { BLOCK_CENTER, BLOCK_TOP, BLOCK_BOTTOM, BLOCK_BOTTOM_RIGHT }, // L
    { BLOCK_CENTER, BLOCK_TOP, BLOCK_BOTTOM, BLOCK_BOTTOM_LEFT }, // J
    { BLOCK_BOTTOM, BLOCK_TOP_LEFT, BLOCK_BOTTOM_LEFT, BLOCK_BOTTOM_RIGHT, // U
      BLOCK_RIGHT, BLOCK_TOP_RIGHT, BLOCK_LEFT },
    { BLOCK_CENTER, BLOCK_TOP_LEFT, BLOCK_TOP, BLOCK_BOTTOM, // Big Z
      BLOCK_BOTTOM_RIGHT }
};
vector<vector<bitset<4>>> PieceRepo::doors{
    { DOOR_VERT }, // Single v1
    { DOOR_TOP | DOOR_LEFT }, // Single v2
    { DOOR_TOP | DOOR_RIGHT }, // Single v3
    { DOOR_VERT, DOOR_VERT, DOOR_VERT }, // Line
    { DOOR_BOTTOM | DOOR_RIGHT, DOOR_HORZ, DOOR_LEFT | DOOR_TOP, // S
      DOOR_HORZ },
    { DOOR_BOTTOM | DOOR_LEFT, DOOR_HORZ, DOOR_RIGHT | DOOR_TOP, // Z
      DOOR_HORZ },
    { DOOR_VERT, DOOR_VERT, DOOR_TOP | DOOR_RIGHT, DOOR_HORZ }, // L
    { DOOR_VERT, DOOR_VERT, DOOR_TOP | DOOR_LEFT, DOOR_HORZ }, // J
    { DOOR_TOP | DOOR_RIGHT, DOOR_VERT, DOOR_VERT, DOOR_HORZ,   // U
      DOOR_LEFT | DOOR_TOP, DOOR_VERT, DOOR_VERT, DOOR_VERT },
    { DOOR_VERT, DOOR_HORZ, DOOR_LEFT | DOOR_BOTTOM, // Big Z
      DOOR_TOP | DOOR_RIGHT, DOOR_HORZ }
};

// =============================================================================
//                                Constructors
// =============================================================================
Piece::Piece() {}

// =============================================================================
//
// =============================================================================
Piece::Piece(float x, float y, float size) : origin_(Vector2f(0, 0))
{
    int pieceIndex = RandomInt(PieceRepo::shapes.size());
    for (size_t i = 0; i < PieceRepo::shapes[pieceIndex].size(); i++)
    {
        blocks_.push_back(Block(PieceRepo::shapes[pieceIndex][i], size,
                                PieceRepo::doors[pieceIndex][i]));
    }
    move(Vector2f(x, y));
}

// =============================================================================
//                                 Random Int
// =============================================================================
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
    origin_ += direction;
}

/* ========================================================================== */
/*                                   Rotate                                   */
/* ========================================================================== */
void Piece::rotate(float degrees)
{
    for (auto&& i : blocks_) i.Rotate(degrees, origin_);
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
