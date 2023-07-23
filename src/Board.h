/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#ifndef BOARD_H
#define BOARD_H
#include "Piece.h"

template<typename T>
using vector2D = vector<vector<T>>;

/* ========================================================================== */
/*                                 Class Board                                */
/* ========================================================================== */
class Board
{
    private:
        int             columns_;
        int             rows_;
        Vector2f        position_;
        VertexArray     gridlines_h_;
        VertexArray     gridlines_v_;
        vector2D<Block> grid_;
        Piece           piece_;

        Vector2i BlockIndex(Vector2f block_pos, Vector2f block_size) const;
        bool     InBounds(Vector2i index) const;

    public:
        Board();
        Board(size_t rows, size_t columns, float size, Vector2f pos);

        bool              PushPiece();
        void              MovePiece(Vector2f direction);
        void              RotatePiece(float angle);
        void              Draw(RenderWindow& window);
        void              SpawnPiece(float x, float y, float size);
        void              Clear(vector<Vector2i> indices);
        void              Clear();
        void              Input(Event& event);
        vector<Vector2i>* CheckLoop();
        void              MakeGrid(uint8_t rows, uint8_t columns);
};

#endif
