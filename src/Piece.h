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
        enum Mino {
            Single,
            S,
            Z,
            Line,
            L,
            J,
            U,
            BigZ,
            Random,
        };

        Piece(float x, float y, float size, Mino mino);

        void             draw(RenderWindow& window);
        void             move(Vector2f direction);
        void             rotate(float degrees);
        vector<Vector2f> Positions() const;
        vector<Block>    Blocks() const;
        void ConstructMino(float x, float y, float size, Piece::Mino mino);
};

#endif