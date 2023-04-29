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
        enum Mino { Single, S, Z, Line, L, J, U, BigZ, NUM_SHAPES };

        Piece(int x, int y, int size, const Mino mino);

        void draw(RenderWindow& window);
        void move(int x, int y);
        void rotate(int degrees);
        vector<Vector2i> getPositions();
        vector<Block> getBlocks();
        void ConstructMino(int x, int y, int size, const Piece::Mino mino);
};

#endif