#ifndef BOARD_H
#define BOARD_H
#include "Piece.h"

template<typename T>
using vector2D = vector<vector<T>>;

class Board
{
    private:
        const int gridWidth;
        const int gridHeight;
        Vector2i pos;
        const int sizeX;
        const int sizeY;
        VertexArray hLines;
        VertexArray vLines;
        vector2D<Block> grid;

    public:
        Board(size_t gridWidth, size_t gridHeight, Vector2i position, int sizeX,
              int sizeY);

        void PushPiece(Piece& piece);
        void draw(RenderWindow& window);
};

#endif