#ifndef PIECE_H
#define PIECE_H
#include "Block.h"

//============================================================
// Game Piece "Mino"
//============================================================
class Piece
{
    private:
        //============================================================
        // Members
        //============================================================
        std::vector<Block> blocks;

    public:
        enum Shapes { Single, I, L, J, U, NUM_SHAPES };

        //============================================================
        // Constructor
        //============================================================
        Piece(sf::Vector2f&& pos, sf::Vector2f&& size, Shapes shape);

        //============================================================
        // Functions
        //============================================================
        void draw(sf::RenderWindow& window);
        void move(sf::Vector2f&& direction);
        void rotate();
        std::vector<sf::Vector2f> getPositions();
};

#endif