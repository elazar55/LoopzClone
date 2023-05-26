/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#include "Board.h"
#include <float.h>
#include <iostream>
using namespace std;

Vector2f Board::BlockIndex(Vector2f position, Vector2f size) const
{
    float xIndex = (position.x - m_pos.x) / size.x;
    float yIndex = (position.y - m_pos.y) / size.y;

    return Vector2f(xIndex, yIndex);
}

/* ========================================================================== */
/*                                 Constructor                                */
/* ========================================================================== */
Board::Board(size_t rows, size_t columns, float size, Vector2f pos) :
    m_rows(rows),
    m_columns(columns),
    m_size(size),
    m_pos(pos),
    grid(vector2D<Block>(columns, vector<Block>(rows))),
    piece_(128, 128, 32, Piece::Mino::Random)
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
bool Board::PushPiece()
{
    // Checks if blocks are in bounds
    for (auto&& i : piece_.Blocks())
    {
        float xIndex = (i.Position().x - m_pos.x) / i.Size().x;
        float yIndex = (i.Position().y - m_pos.y) / i.Size().y;

        if (xIndex < 0 || yIndex < 0 || xIndex > m_rows - 1 ||
            yIndex > m_columns - 1)
        {
            return EXIT_FAILURE;
        }
        else if (!grid[(int)yIndex][(int)xIndex].IsEmpty())
        {
            return EXIT_FAILURE;
        }
    }
    // They're in bounds
    for (auto&& i : piece_.Blocks())
    {
        float xIndex = (i.Position().x - m_pos.x) / i.Size().x;
        float yIndex = (i.Position().y - m_pos.y) / i.Size().y;
        grid[(int)yIndex][(int)xIndex] = i;
    }

    return EXIT_SUCCESS;
    // TODO: Compensate for grid location
    // TODO: Refactor Block parameters
}

/* ========================================================================== */
/*                                 Move Piece                                 */
/* ========================================================================== */
void Board::MovePiece(Vector2f direction)
{
    for (auto&& b : piece_.Blocks())
    {
        Vector2f newIndex = BlockIndex(b.Position() + direction, b.Size());

        if (newIndex.x >= m_rows || newIndex.y >= m_columns || newIndex.x < 0 ||
            newIndex.y < 0)
        {
            return;
        }
    }
    piece_.move(direction);
}

/* ========================================================================== */
/*                                Rotate Piece                                */
/* ========================================================================== */
void Board::RotatePiece(float angle)
{
    piece_.rotate(angle);
}

/* ========================================================================== */
/*                                    Draw                                    */
/* ========================================================================== */
void Board::draw(RenderWindow& window)
{
    window.draw(hLines);
    window.draw(vLines);
    piece_.draw(window);

    for (size_t y = 0; y < grid.size(); y++)
    {
        for (size_t x = 0; x < grid.back().size(); x++)
        {
            if (!grid[y][x].IsEmpty())
            {
                grid[y][x].Draw(window);
            }
        }
    }
}

/* ========================================================================== */
/*                                 Spawn Piece                                */
/* ========================================================================== */
void Board::SpawnPiece()
{
    piece_ = Piece(128, 128, 32, Piece::Mino::Random);
}
