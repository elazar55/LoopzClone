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
        const int       columns_;
        const int       rows_;
        float           size_;
        Vector2f        position_;
        VertexArray     gridlines_h_;
        VertexArray     gridlines_v_;
        vector2D<Block> grid_;
        Piece           piece_;

        Vector2i BlockIndex(Vector2f block_pos, Vector2f block_size) const;
        bool     InBounds(Vector2i index) const;

    public:
        Board(size_t rows, size_t columns, float size, Vector2f pos);

        bool PushPiece();
        void MovePiece(Vector2f direction);
        void RotatePiece(float angle);
        void Draw(RenderWindow& window);
        void SpawnPiece();
        bool CheckLoop();
};

#endif