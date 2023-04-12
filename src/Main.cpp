//============================================================
// Headers
//============================================================
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
    const size_t GRID_X     = 18;
    const size_t GRID_Y     = 7;

    // Main GUI window
    sf::RenderWindow window(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");

    // Game Objects
    Piece piece(sf::Vector2f(32, 32), sf::Vector2f(64, 64), Piece::Shapes::J);
    Block grid[GRID_X][GRID_Y] = {};

    // Debug text
    sf::Font font;
    font.loadFromFile("C:\\Windows\\Fonts\\consola.ttf");
    sf::Text text("Hello World!", font);
    text.setCharacterSize(24);
    text.setOutlineThickness(5);
    text.setOutlineColor(sf::Color::Black);
    std::stringstream buffer;

    //============================================================
    // Game loop
    //============================================================
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Key::W:
                        piece.move(sf::Vector2f(0, -64));
                        break;
                    case sf::Keyboard::Key::R:
                        piece.move(sf::Vector2f(0, 64));
                        break;
                    case sf::Keyboard::Key::A:
                        piece.move(sf::Vector2f(-64, 0));
                        break;
                    case sf::Keyboard::Key::S:
                        piece.move(sf::Vector2f(64, 0));
                        break;
                    case sf::Keyboard::Key::Q: piece.rotate(); break;
                    case sf::Keyboard::Key::Escape: window.close(); break;
                    default: break;
                }
            }
        }

        // Set debug text
        buffer     = std::stringstream();
        float PosX = piece.getPositions().front().x;
        float PosY = piece.getPositions().front().y;
        buffer << "X:\t\t" << PosX << std::endl;
        buffer << "Y:\t\t" << PosY << std::endl;
        buffer << "ID X:\t" << (int)(PosX / 64) << std::endl;
        buffer << "ID Y:\t" << (int)(PosY / 64) << std::endl;

        // Draw
        window.clear();
        piece.draw(window);
        text.setString(buffer.str());
        window.draw(text);
        window.display();
    }
    return EXIT_SUCCESS;
}