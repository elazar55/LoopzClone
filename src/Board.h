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
        Piece           piece_;

        Vector2f BlockIndex(Vector2f position, Vector2f size) const;

    public:
        Board(size_t rows, size_t columns, float size, Vector2f pos);

        bool PushPiece();
        void MovePiece(Vector2f direction);
        void RotatePiece(float angle);
        void draw(RenderWindow& window);
        void SpawnPiece();
};

#endif