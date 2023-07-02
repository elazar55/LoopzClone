/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Piece.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdlib.h>

// =============================================================================
//                                 Class Game
// =============================================================================
class Game
{
    public:
        Game();
        ~Game();
        void Draw();
        void CreateGame(int columns, int rows, int block_size);
        void CreateWindow(int width, int height);

    private:
        RenderWindow window_;
        Event        event_;
        Board        board_;
};

#endif // GAME_H
