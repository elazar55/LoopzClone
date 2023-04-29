#ifndef BOARD_H
#define BOARD_H
#include "Piece.h"

class Board
{
    private:
        // Members
        const int gridWidth;
        const int gridHeight;
        Vector2i position;
        const int sizeX;
        const int sizeY;
        VertexArray horizontalLines;
        VertexArray verticalLines;
        vector<vector<Block>> grid;

    public:
        Board(size_t gridWidth, size_t gridHeight, Vector2i position, int sizeX,
            int sizeY);

        void PushPiece(Piece& piece);
        void draw(RenderWindow& window);
};

#endif