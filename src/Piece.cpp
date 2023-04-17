#include "Piece.h"

Piece::Piece(int x, int y, int size, Mino mino)
{
    blocks.push_back(Block(x, y, size));
    if (mino == Single) return;

    if (mino >= I)
    {
        blocks.push_back(Block(x, y + size, size));
        blocks.push_back(Block(x, y - size, size));

        if (mino == J) blocks.push_back(Block(x - size, y + size, size));
        else if (mino == L) blocks.push_back(Block(x + size, y + size, size));
    }
}

void Piece::draw(sf::RenderWindow& window)
{ // Forwards to individual blocks
    for (auto& i : blocks)
    {
        i.draw(window);
    }
}

void Piece::move(int x, int y)
{ // Forwards to individual blocks
    for (auto&& i : blocks)
    {
        i.move(x, y);
    }
}

void Piece::rotate(int degrees)
{ // Forwards to individual blocks
    sf::Vector2i origin = blocks[0].getPosition();

    for (auto&& i : blocks) i.rotate(degrees, origin);
}