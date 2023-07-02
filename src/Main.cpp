/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#include "Board.h"
#include "Piece.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdlib.h>

// =============================================================================
//                                    Draw
// =============================================================================
void Draw(RenderWindow& window, Board& board)
{
    window.clear();
    board.Draw(window);
    window.display();
}

// =============================================================================
//                                    Input
// =============================================================================
void Input(RenderWindow& window, Board& board)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) window.close();
        if (event.type == event.KeyPressed)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::Escape: window.close(); break;
                case sf::Keyboard::W: board.MovePiece(Vector2f(0, -32)); break;
                case sf::Keyboard::R: board.MovePiece(Vector2f(0, 32)); break;
                case sf::Keyboard::S: board.MovePiece(Vector2f(32, 0)); break;
                case sf::Keyboard::A: board.MovePiece(Vector2f(-32, 0)); break;
                case sf::Keyboard::Q: board.RotatePiece(90); break;
                case sf::Keyboard::F: board.RotatePiece(-90); break;
                case sf::Keyboard::P: board.Clear(); break;
                case sf::Keyboard::Space:
                    if (board.PushPiece() == EXIT_SUCCESS)
                    {
                        vector<Vector2i>* indices(board.CheckLoop());
                        if (indices != nullptr)
                        {
                            board.Clear(*indices);
                            delete indices;
                        }
                        board.SpawnPiece();
                    }
                    break;
                default: break;
            }
        }
    }
}

void InputMap()
{
    map<Keyboard::Key, void (*)()> key_map;
}

// =============================================================================
//                                 Game Start
// =============================================================================
int start()
{
    const int WINDOW_WIDTH  = 640;
    const int WINDOW_HEIGHT = 480;
    const int COLUMNS       = 18;
    const int ROWS          = 7;
    const int BLOCK_SIZE    = 32;

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
    Board        board(COLUMNS, ROWS, BLOCK_SIZE, Vector2f(32, 32));
    srand(time(NULL));

    while (window.isOpen())
    {
        Input(window, board);
        Draw(window, board);
    }
    return EXIT_SUCCESS;
}

/* ========================================================================== */
/*                                    Main                                    */
/* ========================================================================== */
int main()
{
    start();
    return 0;
}
