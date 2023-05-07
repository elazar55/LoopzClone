/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#ifndef BOARD_H
#define BOARD_H
#include "Piece.h"

/* ========================================================================== */
/*                                   Globals                                  */
/* ========================================================================== */
template<typename T>
using vector2D = vector<vector<T>>;

/* ========================================================================== */
/*                                 Class Board                                */
/* ========================================================================== */
class Board
{
    private:
        const int       m_rows;
        const int       m_columns;
        float           m_size;
        Vector2f        m_pos;
        VertexArray     hLines;
        VertexArray     vLines;
        vector2D<Block> grid;

    public:
        Board(size_t rows, size_t columns, float size, Vector2f pos);

        bool PushPiece(Piece& piece);
        void draw(RenderWindow& window);
};

#endif