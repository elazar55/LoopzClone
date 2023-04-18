/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#ifndef PIECE_H
#define PIECE_H
#include "Block.h"

/* ========================================================================== */
/*                                 Class Piece                                */
/* ========================================================================== */
class Piece
{
    private:
        std::vector<Block> blocks;

    public:
        enum Mino { Single, S, Z, Line, L, J, U, BigZ, NUM_SHAPES };

        Piece(int x, int y, int size, const Mino mino);

        void draw(sf::RenderWindow& window);
        void move(int x, int y);
        void rotate(int degrees);
        void ConstructMino(int x, int y, int size, const Piece::Mino mino);
};

#endif