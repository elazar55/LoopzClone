#ifndef PIECE_H
#define PIECE_H
#include "Block.h"

class Piece
{
    private:
        std::vector<Block> blocks;

    public:
        enum Mino { Single, I, L, J, U, NUM_SHAPES };

        Piece(int x, int y, int size, Mino mino);

        void draw(sf::RenderWindow& window);
        void move(int x, int y);
        void rotate(int degrees);
};

#endif