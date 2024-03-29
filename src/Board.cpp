/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#include "Board.h"
#include <float.h>
#include <iostream>
using namespace std;

/* ========================================================================== */
/*                                 Constructor                                */
/* ========================================================================== */
Board::Board(size_t rows, size_t columns, float size, Vector2f pos) :
    columns_(columns),
    rows_(rows),
    position_(pos),
    grid_(vector2D<Block>(columns, vector<Block>(rows)))
{
    gridlines_h_.setPrimitiveType(Lines);
    gridlines_v_.setPrimitiveType(Lines);

    // ------------------------ Horizontal Gridlines ---------------------------
    for (size_t i = 0; i <= rows; i++)
    {
        float offset = size * i;
        float width  = columns * size;

        Vector2f start(pos.x, pos.y + offset);
        Vector2f end(pos.x + width, pos.y + offset);

        gridlines_h_.append(start);
        gridlines_h_.append(end);
    }

    // ------------------------- Vertical Gridlines ----------------------------
    for (size_t i = 0; i <= columns; i++)
    {
        float offset = size * i;
        float height = rows * size;

        Vector2f start(pos.x + offset, pos.y);
        Vector2f end(pos.x + offset, pos.y + height);

        gridlines_v_.append(start);
        gridlines_v_.append(end);
    }
}

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
    if (index.x >= columns_ || index.y >= rows_ || index.x < 0 || index.y < 0)
        return false;

    return true;
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

        if (index.x + 1 == columns_ && i.Doors()[2]) // Right
            return EXIT_FAILURE;

        else if (index.y + 1 == rows_ && i.Doors()[1]) // Bottom
            return EXIT_FAILURE;

        else if (index.x == 0 && i.Doors()[0]) // Left
            return EXIT_FAILURE;

        else if (index.y == 0 && i.Doors()[3]) // Top
            return EXIT_FAILURE;

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

    for (auto&& i : piece_.Blocks())
    {
        if (i.Position().x <= 0)
        {
            piece_.move(Vector2f(i.Size().x, 0));
            break;
        }
        else if (BlockIndex(i.Position(), i.Size()).x >= columns_)
        {
            piece_.move(Vector2f(-i.Size().x, 0));
            break;
        }
        else if (BlockIndex(i.Position(), i.Size()).y >= rows_)
        {
            piece_.move(Vector2f(0, -i.Size().y));
            break;
        }
        else if (i.Position().y <= 0)
        {
            piece_.move(Vector2f(0, i.Size().y));
            break;
        }
    }
}

/* ========================================================================== */
/*                                    Draw                                    */
/* ========================================================================== */
void Board::Draw(RenderWindow& window)
{
    window.draw(gridlines_h_);
    window.draw(gridlines_v_);

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
    piece_.draw(window);
}

/* ========================================================================== */
/*                                 Spawn Piece                                */
/* ========================================================================== */
void Board::SpawnPiece(float x, float y, float size)
{
    // TODO: Piece position
    piece_ = Piece(x, y, size);
}

/* ========================================================================== */
/*                                    Clear                                   */
/* ========================================================================== */
void Board::Clear()
{
    grid_ = (vector2D<Block>(columns_, vector<Block>(rows_)));
}

// =============================================================================
//                                    Input
// =============================================================================
void Board::Input(Event& event)
{
    if (event.type == event.KeyPressed)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::W: MovePiece(Vector2f(0, -32)); break;
            case sf::Keyboard::R: MovePiece(Vector2f(0, 32)); break;
            case sf::Keyboard::S: MovePiece(Vector2f(32, 0)); break;
            case sf::Keyboard::A: MovePiece(Vector2f(-32, 0)); break;
            case sf::Keyboard::Q: RotatePiece(90); break;
            case sf::Keyboard::F: RotatePiece(-90); break;
            case sf::Keyboard::P: Clear(); break;
            case sf::Keyboard::Space:
                if (PushPiece() == EXIT_SUCCESS)
                {
                    vector<Vector2i>* indices(CheckLoop());
                    if (indices != nullptr)
                    {
                        Clear(*indices);
                        delete indices;
                    }
                    SpawnPiece(128, 128, 32);
                }
                break;
            default: break;
        }
    }
}

void Board::Clear(vector<Vector2i> indices)
{
    for (auto&& i : indices)
    {
        grid_[i.x][i.y] = Block();
    }
}

/* ========================================================================== */
/*                                 Check Loop                                 */
/* ========================================================================== */
vector<Vector2i>* Board::CheckLoop()
{
    const Vector2i&  start   = BlockIndex(piece_.Blocks().back().Position(),
                                          piece_.Blocks().back().Size());
    int              columns = grid_.size();
    int              rows    = grid_.back().size();
    Vector2i         index   = start;
    bitset<4U>       direction{ 0 };
    vector<Vector2i> checkedIndices;

    grid_[index.x][index.y].SetColor(Color::Cyan);

    do
    {
        Block& block = grid_[index.x][index.y];
        checkedIndices.push_back(index);
        if (direction.any()) block.SetColor(sf::Color::Green);

        /* =========================== Checks top =========================== */
        if (block.Doors()[Block::Door::TOP_INDEX] && direction != DOOR_BOTTOM &&
            index.y > 0)
        {
            Block& adjacent = grid_[index.x][index.y - 1];
            if (adjacent.Doors()[Block::Door::BOTTOM_INDEX])
            {
                direction = DOOR_TOP;
                index.y--;
                continue;
            }
        }

        /* ========================== Checks right ========================== */
        if (block.Doors()[Block::Door::RIGHT_INDEX] && direction != DOOR_LEFT &&
            index.x < columns - 1)
        {
            Block& adjacent = grid_[index.x + 1][index.y];
            if (adjacent.Doors()[Block::Door::LEFT_INDEX])
            {
                direction = DOOR_RIGHT;
                index.x++;
                continue;
            }
        }

        /* ========================== Checks bottom ========================= */
        if (block.Doors()[Block::Door::BOTTOM_INDEX] && direction != DOOR_TOP &&
            index.y < rows - 1)
        {
            Block& adjacent = grid_[index.x][index.y + 1];
            if (adjacent.Doors()[Block::Door::TOP_INDEX])
            {
                direction = DOOR_BOTTOM;
                index.y++;
                continue;
            }
        }

        /* =========================== Checks left ========================== */
        if (block.Doors()[Block::Door::LEFT_INDEX] && direction != DOOR_RIGHT &&
            index.x > 0)
        {
            Block& adjacent = grid_[index.x - 1][index.y];
            if (adjacent.Doors()[Block::Door::RIGHT_INDEX])
            {
                direction = DOOR_LEFT;
                index.x--;
                continue;
            }
        }

        /* ====================== Stop, out of options ====================== */
        return nullptr;
    }
    while ((index != start));

    /* =========================== Loop successful ========================== */
    return new vector<Vector2i>(checkedIndices);
}

void Board::MakeGrid(uint8_t rows, uint8_t columns)
{
}
