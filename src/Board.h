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
        const int gridWidth;
        const int gridHeight;
        Vector2f pos;
        const int sizeX;
        const int sizeY;
        VertexArray hLines;
        VertexArray vLines;
        vector2D<Block> grid;

    public:
        Board(size_t gridWidth, size_t gridHeight, Vector2f position, int sizeX,
              int sizeY); // TODO: Refactor size to be a Vector2i

        bool PushPiece(Piece& piece);
        void draw(RenderWindow& window);
};

#endif