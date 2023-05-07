/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#include "Board.h"
#include <iostream>
using namespace std;

/* ========================================================================== */
/*                                 Constructor                                */
/* ========================================================================== */
Board::Board(size_t rows, size_t columns, float size, Vector2f pos) :
    m_rows(rows),
    m_columns(columns),
    m_size(size),
    m_pos(pos),
    grid(vector2D<Block>(columns, vector<Block>(rows)))
{
    hLines.setPrimitiveType(Lines);
    vLines.setPrimitiveType(Lines);

    for (size_t i = 0; i <= columns; i++)
    {
        float offset = size * i;
        float width  = rows * size;

        Vector2f start(pos.x, pos.y + offset);
        Vector2f end(pos.x + width, pos.y + offset);

        hLines.append(start);
        hLines.append(end);
    }

    for (size_t i = 0; i <= rows; i++)
    {
        float offset = size * i;
        float height = columns * size;

        Vector2f start(pos.x + offset, pos.y);
        Vector2f end(pos.x + offset, pos.y + height);

        vLines.append(start);
        vLines.append(end);
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
        float xIndex = (i.getPosition().x - m_pos.x) / i.getSize().x;
        float yIndex = (i.getPosition().y - m_pos.y) / i.getSize().y;

        if (xIndex < 0 || yIndex < 0 || xIndex > m_rows - 1 ||
            yIndex > m_columns - 1)
        {
            return EXIT_FAILURE;
        }
    }
    // They're in bounds
    for (auto&& i : piece.getBlocks())
    {
        float xIndex = (i.getPosition().x - m_pos.x) / i.getSize().x;
        float yIndex = (i.getPosition().y - m_pos.y) / i.getSize().y;
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
