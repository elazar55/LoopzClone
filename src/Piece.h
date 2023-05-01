/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#ifndef PIECE_H
#define PIECE_H
#include "Block.h"
using namespace std;
using namespace sf;

/* ========================================================================== */
/*                                 Class Piece                                */
/* ========================================================================== */
class Piece
{
    private:
        vector<Block> blocks;

    public:
        enum Mino { Single, S, Z, Line, L, J, U, BigZ, Random, NUM_SHAPES };

        Piece(int x, int y, int size, Mino mino);

        void draw(RenderWindow& window);
        void move(Vector2f direction);
        void rotate(int degrees);
        vector<Vector2f> getPositions();
        vector<Block> getBlocks();
        void ConstructMino(int x, int y, int size, Piece::Mino mino);
};

#endif