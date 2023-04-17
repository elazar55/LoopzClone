//============================================================
// Headers
//============================================================
#include "Board.h"
#include "Piece.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

//============================================================
// Main
//============================================================
int main()
{
    // Parameters
    const int WINDOW_WIDTH  = 640;
    const int WINDOW_HEIGHT = 480;
    // const int GRID_WIDTH    = 18;
    // const int GRID_HEIGHT   = 7;
    const int BLOCK_SIZE = 64;

    // Main GUI window
    sf::RenderWindow window(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");

    // Game objects
    Piece piece(0, 0, BLOCK_SIZE, Piece::Mino::L);

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
                    case sf::Keyboard::W: piece.move(0, -BLOCK_SIZE); break;
                    case sf::Keyboard::R: piece.move(0, BLOCK_SIZE); break;
                    case sf::Keyboard::S: piece.move(BLOCK_SIZE, 0); break;
                    case sf::Keyboard::A: piece.move(-BLOCK_SIZE, 0); break;
                    case sf::Keyboard::Q: piece.rotate(90); break;
                    case sf::Keyboard::F: piece.rotate(-90); break;

                    default: break;
                }
            }
        }

        // Draw
        window.clear();
        piece.draw(window);
        window.display();
    }
    return EXIT_SUCCESS;
}