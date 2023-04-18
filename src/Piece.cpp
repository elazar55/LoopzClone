/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#include "Piece.h"

/* ========================================================================== */
/*                                 Constructor                                */
/* ========================================================================== */
Piece::Piece(int x, int y, int size, const Mino mino)
{
    ConstructMino(x, y, size, mino);
}

/* ========================================================================== */
/*                                ConstructMino                               */
/* ========================================================================== */
void Piece::ConstructMino(int x, int y, int size, const Piece::Mino mino)
{
    if (mino == Piece::Single)
    {
        blocks.push_back(Block(x, y, size));
    }
    else if (mino == S)
    {
        blocks.push_back(Block(x, y - size, size));
        blocks.push_back(Block(x + size, y - size, size));
        blocks.push_back(Block(x - size, y, size));
    }
    else if (mino == Z)
    {
        blocks.push_back(Block(x, y - size, size));
        blocks.push_back(Block(x - size, y - size, size));
        blocks.push_back(Block(x + size, y, size));
    }
    else if (mino == Piece::Line)
    {
        blocks.push_back(Block(x, y, size));
        blocks.push_back(Block(x, y + size, size));
        blocks.push_back(Block(x, y - size, size));
    }
    else if (mino == Piece::J)
    {
        ConstructMino(x, y, size, Piece::Line);
        blocks.push_back(Block(x + size, y + size, size));
    }
    else if (mino == Piece::L)
    {
        ConstructMino(x, y, size, Piece::Line);
        blocks.push_back(Block(x - size, y + size, size));
    }
    else if (mino == Piece::U)
    {
        ConstructMino(x, y, size, Piece::J);
        blocks.push_back(Block(x + size, y - size, size));
    }
    else if (mino == Piece::BigZ)
    {
        ConstructMino(x, y, size, Piece::J);
        blocks.push_back(Block(x - size, y - size, size));
    }
}

void Piece::draw(sf::RenderWindow& window)
{
    // Forwards to individual blocks
    for (auto& i : blocks) i.draw(window);
}

void Piece::move(int x, int y)
{
    // Forwards to individual blocks
    for (auto&& i : blocks) i.move(x, y);
}

void Piece::rotate(int degrees)
{
    // Forwards to individual blocks
    sf::Vector2i origin = blocks[0].getPosition();

    for (auto&& i : blocks) i.rotate(degrees, origin);
}
