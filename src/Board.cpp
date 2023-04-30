/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#include "Board.h"
#include <iostream>
using namespace std;

/* ========================================================================== */
/*                                 Constructor                                */
/* ========================================================================== */
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

/* ========================================================================== */
/*                                 Push Piece                                 */
/* ========================================================================== */
void Board::PushPiece(Piece& piece)
{
    for (auto&& i : piece.getBlocks())
    {
        int xIndex = i.getPosition().x / i.getSize().x;
        int yIndex = i.getPosition().y / i.getSize().y;

        grid[yIndex][xIndex] =
            Block(i.getPosition().x, i.getPosition().y, i.getSize().x);

        cout << "X Index: " << xIndex << " Y Index: " << yIndex << endl;
    }
    // TODO: Compensate for grid location
    // TODO: Refactor Block parameters
}

/* ========================================================================== */
/*                                    Draw                                    */
/* ========================================================================== */
void Board::draw(RenderWindow& window)
{
    window.draw(hLines);
    window.draw(vLines);

    for (size_t y = 0; y < grid.size(); y++)
    {
        for (size_t x = 0; x < grid.back().size(); x++)
        {
            if (grid[y][x].getPosition().x != INT_MAX) grid[y][x].draw(window);
        }
    }
}
