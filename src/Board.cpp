/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#include "Board.h"
#include <iostream>
using namespace std;

/* ========================================================================== */
/*                                 Constructor                                */
/* ========================================================================== */
Board::Board(size_t gridWidth, size_t gridHeight, Vector2f pos, int sizeX,
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
bool Board::PushPiece(Piece& piece)
{
    // Checks if blocks are in bounds
    for (auto&& i : piece.getBlocks())
    {
        float xIndex = (i.getPosition().x - pos.x) / i.getSize().x;
        float yIndex = (i.getPosition().y - pos.y) / i.getSize().y;

        if (xIndex < 0 || yIndex < 0 || xIndex > gridWidth - 1 ||
            yIndex > gridHeight - 1)
        {
            return EXIT_FAILURE;
        }
    }
    // They're in bounds
    for (auto&& i : piece.getBlocks())
    {
        float xIndex = (i.getPosition().x - pos.x) / i.getSize().x;
        float yIndex = (i.getPosition().y - pos.y) / i.getSize().y;

        cout << "X Index: " << xIndex << " Y Index: " << yIndex << endl;
        grid[(int)yIndex][(int)xIndex] = i;
    }

    return EXIT_SUCCESS;
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
