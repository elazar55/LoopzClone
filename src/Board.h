#ifndef BOARD_H
#define BOARD_H
#include "Piece.h"

class Board
{
    private:
        // Members
        const size_t WIDTH;
        const size_t HEIGHT;
        std::vector<std::vector<Block>> grid;

    public:
        Board(size_t width, size_t height);

        void PushPiece(Piece& piece);
};

#endif