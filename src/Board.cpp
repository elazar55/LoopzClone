#include "Board.h"
#include <iostream>
using namespace std;

Board::Board(size_t gridWidth, size_t gridHeight, Vector2i pos, int sizeX,
    int sizeY) :
    gridWidth(gridWidth),
    gridHeight(gridHeight),
    pos(pos),
    sizeX(sizeX),
    sizeY(sizeY),
    grid(vector2D<Block>(gridHeight, vector<Block>(gridWidth)))
{
    hLines.setPrimitiveType(Lines);
    vLines.setPrimitiveType(Lines);

    for (size_t i = 0; i <= gridHeight; i++)
    {
        int offset = (sizeX / gridWidth) * i;
        hLines.append(Vertex(Vector2f(pos.x, pos.y + offset)));
        hLines.append(Vertex(Vector2f(pos.x + sizeX, pos.y + offset)));
    }

    for (size_t i = 0; i <= gridWidth; i++)
    {
        int offset = (sizeY / gridHeight) * i;
        vLines.append(Vertex(Vector2f(pos.x + offset, pos.y)));
        vLines.append(Vertex(Vector2f(pos.x + offset, pos.y + sizeY)));
    }
}

void Board::PushPiece(Piece& piece)
{
    //
}

void Board::draw(RenderWindow& window)
{
    window.draw(horizontalLines);
    window.draw(verticalLines);
}
