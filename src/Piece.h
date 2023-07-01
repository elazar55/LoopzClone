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
        vector<Block>         blocks_;
        vector<vector<Block>> ShapeRepo_;
        int                   RandomInt(int max);

    public:
        Piece(float x, float y, float size);
        vector<Block>    Blocks() const;
        vector<Vector2f> Positions() const;
        void             draw(RenderWindow& window);
        void             move(Vector2f direction);
        void             rotate(float degrees);
};

#endif
