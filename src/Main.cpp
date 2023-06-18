/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#include "Board.h"
#include "Piece.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>

/* ========================================================================== */
/*                                    Main                                    */
/* ========================================================================== */

extern "C" void AsmTest()
{
    int assembly(int x, int y);
    int i = assembly(6, 4);
    cout << i << endl;
}

int main()
{
    AsmTest();
    return 0;
}

int start()
{
    srand(time(NULL));
    // Parameters
    const int WINDOW_WIDTH  = 640;
    const int WINDOW_HEIGHT = 480;
    const int GRID_COLUMNS  = 18;
    const int GRID_ROWS     = 7;
    const int BLOCK_SIZE    = 32;

    // Main GUI window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                            "SFML works!");

    // Game objects
    Board board(GRID_COLUMNS, GRID_ROWS, BLOCK_SIZE, Vector2f(32, 32));

    // Game loop
    while (window.isOpen())
    {
        sf::Event event;

        // Event queue
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == event.KeyPressed)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Escape: window.close(); break;
                    case sf::Keyboard::W:
                        board.MovePiece(Vector2f(0, -BLOCK_SIZE));
                        break;
                    case sf::Keyboard::R:
                        board.MovePiece(Vector2f(0, BLOCK_SIZE));
                        break;
                    case sf::Keyboard::S:
                        board.MovePiece(Vector2f(BLOCK_SIZE, 0));
                        break;
                    case sf::Keyboard::A:
                        board.MovePiece(Vector2f(-BLOCK_SIZE, 0));
                        break;
                    case sf::Keyboard::Q: board.RotatePiece(90); break;
                    case sf::Keyboard::F: board.RotatePiece(-90); break;
                    case sf::Keyboard::Space:
                        if (board.PushPiece() == EXIT_SUCCESS)
                        {
                            board.CheckLoop();
                            board.SpawnPiece();
                        }
                        break;

                    default: break;
                }
            }
        }

        // Draw
        window.clear();
        board.Draw(window);
        // piece.draw(window);
        window.display();
    }
    return EXIT_SUCCESS;
}