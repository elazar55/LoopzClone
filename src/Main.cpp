/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#include "Board.h"
#include "Menu.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

// =============================================================================
//                                 Game Start
// =============================================================================
int main()

{
    srand(time(NULL));

    const int   WINDOW_WIDTH  = 640;
    const int   WINDOW_HEIGHT = 480;
    const int   COLUMNS       = 18;
    const int   ROWS          = 7;
    const int   BLOCK_SIZE    = 32;
    const float CENTER        = (WINDOW_WIDTH - (BLOCK_SIZE * COLUMNS)) / 2;

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
    Event        event;
    Board        board(ROWS, COLUMNS, BLOCK_SIZE, Vector2f(CENTER, CENTER));
    board.SpawnPiece(BLOCK_SIZE * 9, BLOCK_SIZE * 4, BLOCK_SIZE);
    Menu mainMenu;
    mainMenu.AddMenuItem("New Game");

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                return EXIT_SUCCESS;
            }
            if (event.type == event.KeyPressed)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Escape: window.close(); break;
                    default: break;
                }
            }
            board.Input(event);
        }
        window.clear();
        board.Draw(window);
        window.display();
    }
    return EXIT_SUCCESS;
}
