#include "Board.h"
#include <iostream>
using namespace std;

Board::Board(size_t gridWidth, size_t gridHeight, Vector2i position, int sizeX,
    int sizeY) :
    gridWidth(gridWidth),
    gridHeight(gridHeight),
    position(position),
    sizeX(sizeX),
    sizeY(sizeY),
    grid(vector<vector<Block>>(gridHeight, vector<Block>(gridWidth)))
{
    horizontalLines.setPrimitiveType(Lines);
    verticalLines.setPrimitiveType(Lines);

    for (size_t i = 0; i <= gridHeight; i++)
    {
        int spacing = (sizeX / gridWidth) * i;
        horizontalLines.append(
            Vertex(Vector2f(position.x, position.y + spacing)));
        horizontalLines.append(
            Vertex(Vector2f(position.x + sizeX, position.y + spacing)));
    }

    for (size_t i = 0; i <= gridWidth; i++)
    {
        int spacing = (sizeY / gridHeight) * i;
        verticalLines.append(
            Vertex(Vector2f(position.x + spacing, position.y)));
        verticalLines.append(
            Vertex(Vector2f(position.x + spacing, position.y + sizeY)));
    } // TODO: Refactor
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
