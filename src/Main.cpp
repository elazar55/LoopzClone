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
int main()
{
    srand(time(NULL));
    // Parameters
    const int WINDOW_WIDTH  = 640;
    const int WINDOW_HEIGHT = 480;
    const int GRID_WIDTH    = 18;
    const int GRID_HEIGHT   = 7;
    const int BLOCK_SIZE    = 32;

    // Main GUI window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                            "SFML works!");

    // Game objects
    Board board(GRID_WIDTH, GRID_HEIGHT, BLOCK_SIZE, Vector2f(32, 32));
    Piece piece(32, 32, BLOCK_SIZE, Piece::Mino::Single);

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
                        piece.move(Vector2f(0, -BLOCK_SIZE));
                        break;
                    case sf::Keyboard::R:
                        piece.move(Vector2f(0, BLOCK_SIZE));
                        break;
                    case sf::Keyboard::S:
                        piece.move(Vector2f(BLOCK_SIZE, 0));
                        break;
                    case sf::Keyboard::A:
                        piece.move(Vector2f(-BLOCK_SIZE, 0));
                        break;
                    case sf::Keyboard::Q: piece.rotate(90); break;
                    case sf::Keyboard::F: piece.rotate(-90); break;
                    case sf::Keyboard::Space:
                        if (board.PushPiece(piece) == EXIT_SUCCESS)
                        {
                            piece = Piece(BLOCK_SIZE * 5, BLOCK_SIZE * 5,
                                          BLOCK_SIZE, Piece::Mino::Random);
                        }
                        break;

                    default: break;
                }
            }
        }

        // Draw
        window.clear();
        board.draw(window);
        piece.draw(window);
        window.display();
    }
    return EXIT_SUCCESS;
}