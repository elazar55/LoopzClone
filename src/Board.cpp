#include "Board.h"

Board::Board(size_t width, size_t height) :
    WIDTH(width), HEIGHT(height),
    grid(std::vector<std::vector<Block>>(height, std::vector<Block>(width)))
{
}

void Board::PushPiece(Piece& piece) {}
