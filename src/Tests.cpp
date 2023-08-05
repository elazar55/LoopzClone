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
//                                 Input Test
// =============================================================================
void ComputedGotoTest(RenderWindow& window, Board& board)
{
    Clock     clock;
    sf::Event event;
    void*     table[Keyboard::KeyCount];
    std::fill(table, table + Keyboard::KeyCount, &&base);

    table[Keyboard::Key::Escape] = &&Escape;
    table[Keyboard::Key::Space]  = &&Space;
    table[Keyboard::Key::W]      = &&W;
    table[Keyboard::Key::R]      = &&R;
    table[Keyboard::Key::S]      = &&S;
    table[Keyboard::Key::A]      = &&A;
    table[Keyboard::Key::Q]      = &&Q;
    table[Keyboard::Key::F]      = &&F;
    table[Keyboard::Key::P]      = &&P;

    while (window.pollEvent(event))
    {
        clock.restart();
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == event.KeyPressed)
            goto* table[event.key.code];
        break;

    Escape:
        window.close();
        goto base;
    Space:
        if (board.PushPiece() == EXIT_SUCCESS)
        {
            vector<Vector2i>* indices(board.CheckLoop());
            if (indices != nullptr)
            {
                board.Clear(*indices);
                delete indices;
            }
            board.SpawnPiece(128, 128, 32);
        }
        goto base;
    W:
        board.MovePiece(Vector2f(0, -32));
        goto base;
    R:
        board.MovePiece(Vector2f(0, 32));
        goto base;
    S:
        board.MovePiece(Vector2f(32, 0));
        goto base;
    A:
        board.MovePiece(Vector2f(-32, 0));
        goto base;
    Q:
        board.RotatePiece(90);
        goto base;
    F:
        board.RotatePiece(-90);
        goto base;
    P:
        board.Clear();
        goto base;
    base:
        cout << clock.restart().asMicroseconds() << "ns\n";
    }
}

// =============================================================================
//                                  ASM Test
// =============================================================================
// extern "C" void AsmTest()
// {
//     int assembly(int x, int y);
//     int i = assembly(6, 4);
//     cout << i << endl;
// }

// =============================================================================
//                                Callback Test
// =============================================================================
template<typename T, typename... Args>
void CallbackTest(void (T::*func)(Args...), T& object, Args... args)
{
    (object.*func)(args...);
}

// =============================================================================
//                            In-Register Shuffles
// =============================================================================
void popcnt()
{
    char counts[256]{};

    for (int m = 0; m < 256; m++)
        for (int i = 0; i < 8; i++)
            counts[m] += (m >> i & 1);
}
