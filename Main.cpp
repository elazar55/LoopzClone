#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

class Block : public sf::RectangleShape
{
    private:
        bool doors[4];

    public:
        Block() : doors() {}

        Block(sf::Vector2f& size) : doors(), sf::RectangleShape(size) {}

        void rotate(float degrees)
        {
            sf::RectangleShape::rotate(degrees);
            // TODO: Rotate doors
        }
};

// ============================================================
// == Game piece
// ============================================================
class Piece
{
    private:
        std::vector<Block> blocks;

    public:
        enum Shapes { Single, I, L, J, U, NUM_SHAPES };

        Piece(sf::Vector2f&& pos, sf::Vector2f&& size, Shapes shape)
        {
            // ============================================================
            // == Single Shape
            // ============================================================
            blocks.push_back(Block(size));
            sf::RectangleShape* thisBlock = &blocks.back();
            thisBlock->setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
            thisBlock->setPosition(pos);
            thisBlock->setFillColor(sf::Color::Green);
            thisBlock->setOutlineColor(sf::Color::Blue);
            thisBlock->setOutlineThickness(-5.f);

            if (shape == Single) return;

            // ============================================================
            // == I Shape
            // ============================================================
            if (shape >= Shapes::I)
            {
                // Top
                blocks.push_back(Block(size));
                thisBlock = &blocks.back();
                thisBlock->setOrigin(sf::Vector2f(size.x / 2, -size.y / 2));
                thisBlock->setPosition(pos);
                thisBlock->setFillColor(sf::Color::Green);
                thisBlock->setOutlineColor(sf::Color::Blue);
                thisBlock->setOutlineThickness(-5.f);

                // Bottom
                blocks.push_back(Block(size));
                thisBlock = &blocks.back();
                // Compensate y because coordinates are top-left
                thisBlock->setOrigin(sf::Vector2f(size.x / 2, size.y * 1.5));
                thisBlock->setPosition(pos);
                thisBlock->setFillColor(sf::Color::Green);
                thisBlock->setOutlineColor(sf::Color::Blue);
                thisBlock->setOutlineThickness(-5.f);
            }
            // ============================================================
            // == J / L Shape
            // ============================================================
            if (shape == Shapes::L || shape == Shapes::J)
            {
                // Bottom Left
                blocks.push_back(Block(size));
                thisBlock = &blocks.back();
                if (shape == L)
                    thisBlock->setOrigin(
                        sf::Vector2f(size.x / -2, size.y * 1.5));
                else
                    thisBlock->setOrigin(
                        sf::Vector2f(size.x / -2, size.y * 1.5));
                thisBlock->setPosition(pos);
                thisBlock->setFillColor(sf::Color::Green);
                thisBlock->setOutlineColor(sf::Color::Blue);
                thisBlock->setOutlineThickness(-5.f);
            }
        }

        void draw(sf::RenderWindow& window)
        {
            for (auto& i : blocks) { window.draw(i); }
        }

        void move(sf::Vector2f&& direction)
        {
            for (auto& i : blocks) { i.move(direction); }
        }

        void rotate()
        {
            for (auto& i : blocks) { i.rotate(90.f); }
        }

        std::vector<sf::Vector2f> getPositions()
        {
            std::vector<sf::Vector2f> positions;
            for (auto&& i : blocks) positions.push_back(i.getPosition());

            return positions;
        }
};

// ============================================================
// == Main
// ============================================================
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

    Piece piece(sf::Vector2f(32, 32), sf::Vector2f(64, 64), Piece::Shapes::J);
    Block grid[GRID_X][GRID_Y] = {};

    // ============================================================
    // == Debug output
    // ============================================================
    sf::Font font;
    font.loadFromFile("C:\\Windows\\Fonts\\consola.ttf");
    sf::Text text("Hello World!", font);
    text.setCharacterSize(24);
    text.setOutlineThickness(5);
    text.setOutlineColor(sf::Color::Black);
    std::stringstream buffer;

    // ============================================================
    // == Game loop
    // ============================================================
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

        // ============================================================
        // == Set debug output text
        // ============================================================
        buffer     = std::stringstream();
        float PosX = piece.getPositions().front().x;
        float PosY = piece.getPositions().front().y;
        buffer << "X:\t\t" << PosX << std::endl;
        buffer << "Y:\t\t" << PosY << std::endl;
        buffer << "ID X:\t" << (int)(PosX / 64) << std::endl;
        buffer << "ID Y:\t" << (int)(PosY / 64) << std::endl;

        window.clear();
        piece.draw(window);
        text.setString(buffer.str());
        window.draw(text);
        window.display();
    }
    return EXIT_SUCCESS;
}