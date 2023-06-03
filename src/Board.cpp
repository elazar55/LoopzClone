/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#include "Board.h"
#include <float.h>
#include <iostream>
using namespace std;

/* ========================================================================== */
/*                                 Block Index                                */
/* ========================================================================== */
Vector2i Board::BlockIndex(Vector2f block_pos, Vector2f block_size) const
{
    float index_x = (block_pos.x - position_.x) / block_size.x;
    float index_y = (block_pos.y - position_.y) / block_size.y;

    return Vector2i(index_x, index_y);
}

/* ========================================================================== */
/*                                  In Bounds                                 */
/* ========================================================================== */
bool Board::InBounds(Vector2i index) const
{
    if (index.x >= rows_ || index.y >= columns_ || index.x < 0 || index.y < 0)
        return false;

    return true;
}

/* ========================================================================== */
/*                                 Constructor                                */
/* ========================================================================== */
Board::Board(size_t rows, size_t columns, float size, Vector2f pos) :
    rows_(rows),
    columns_(columns),
    size_(size),
    position_(pos),
    grid_(vector2D<Block>(rows, vector<Block>(columns))),
    piece_(128, 128, 32, Piece::Mino::Random)
{
    gridlines_h_.setPrimitiveType(Lines);
    gridlines_v_.setPrimitiveType(Lines);

    for (size_t i = 0; i <= columns; i++)
    {
        float offset = size * i;
        float width  = rows * size;

        Vector2f start(pos.x, pos.y + offset);
        Vector2f end(pos.x + width, pos.y + offset);

        gridlines_h_.append(start);
        gridlines_h_.append(end);
    }

    for (size_t i = 0; i <= rows; i++)
    {
        float offset = size * i;
        float height = columns * size;

        Vector2f start(pos.x + offset, pos.y);
        Vector2f end(pos.x + offset, pos.y + height);

        gridlines_v_.append(start);
        gridlines_v_.append(end);
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
        Vector2i index = BlockIndex(i.Position(), i.Size());

        if (!InBounds(index))
        {
            return EXIT_FAILURE;
        }
        else if (!grid_[index.x][index.y].IsEmpty())
        {
            return EXIT_FAILURE;
        }
    }
    // They're in bounds
    for (auto&& i : piece_.Blocks())
    {
        auto index = BlockIndex(i.Position(), i.Size());

        grid_[index.x][index.y] = i;
    }

    return EXIT_SUCCESS;
}

/* ========================================================================== */
/*                                 Move Piece                                 */
/* ========================================================================== */
void Board::MovePiece(Vector2f direction)
{
    for (auto&& b : piece_.Blocks())
    {
        Vector2i new_index = BlockIndex(b.Position() + direction, b.Size());

        if (!InBounds(new_index))
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
void Board::Draw(RenderWindow& window)
{
    window.draw(gridlines_h_);
    window.draw(gridlines_v_);
    piece_.draw(window);

    for (size_t x = 0; x < grid_.size(); x++)
    {
        for (size_t y = 0; y < grid_.back().size(); y++)
        {
            if (!grid_[x][y].IsEmpty())
            {
                grid_[x][y].Draw(window);
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

/* ========================================================================== */
/*                                 Check Loop                                 */
/* ========================================================================== */
void Board::CheckLoop()
{
    const Vector2i& start      = BlockIndex(piece_.Blocks().back().Position(),
                                            piece_.Blocks().back().Size());
    Vector2i        next_index = start;
    bitset<4U>      direction{0};

    cout << "----------------------" << endl;
    for (int i = 0; i < 9; i++)
    {
        cout << "Direction: ";
        if ((direction & DOOR_TOP) == DOOR_TOP) cout << "Up";
        if ((direction & DOOR_RIGHT) == DOOR_RIGHT) cout << "Right";
        if ((direction & DOOR_BOTTOM) == DOOR_BOTTOM) cout << "Down";
        if ((direction & DOOR_LEFT) == DOOR_LEFT) cout << "Left";
        cout << "\tNow: ";

        if (!InBounds(next_index) ||
            grid_[next_index.x][next_index.y].IsEmpty())
        {
            cout << endl << "----------------------" << endl;
            return;
        }
        grid_[next_index.x][next_index.y].SetColor(sf::Color::Green);

        if (((grid_[next_index.x][next_index.y].Doors() & DOOR_TOP) ==
             DOOR_TOP) &&
            direction != DOOR_BOTTOM)
        {
            cout << "Up" << endl;
            direction = DOOR_TOP;
            next_index.y--;
        }
        else if (((grid_[next_index.x][next_index.y].Doors() & DOOR_RIGHT) ==
                  DOOR_RIGHT) &&
                 direction != DOOR_LEFT)
        {
            cout << "Right" << endl;
            direction = DOOR_RIGHT;
            next_index.x++;
        }
        else if (((grid_[next_index.x][next_index.y].Doors() & DOOR_BOTTOM) ==
                  DOOR_BOTTOM) &&
                 direction != DOOR_TOP)
        {
            cout << "Down" << endl;
            direction = DOOR_BOTTOM;
            next_index.y++;
        }
        else if (((grid_[next_index.x][next_index.y].Doors() & DOOR_LEFT) ==
                  DOOR_LEFT) &&
                 direction != DOOR_RIGHT)
        {
            cout << "Left" << endl;
            direction = DOOR_LEFT;
            next_index.x--;
        }
    }
}
