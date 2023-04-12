#include "Piece.h"

//============================================================
// Constructors
//============================================================
Piece::Piece(sf::Vector2f&& pos, sf::Vector2f&& size, Shapes shape)
{
    blocks.push_back(Block(size));
    sf::RectangleShape* thisBlock = &blocks.back();
    thisBlock->setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
    thisBlock->setPosition(pos);
    thisBlock->setFillColor(sf::Color::Green);
    thisBlock->setOutlineColor(sf::Color::Blue);
    thisBlock->setOutlineThickness(-5.f);
    if (shape == Single) return;

    // I Shape
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
    // J / L Shape
    if (shape == Shapes::L || shape == Shapes::J)
    {
        // Bottom Left
        blocks.push_back(Block(size));
        thisBlock = &blocks.back();
        if (shape == L)
            thisBlock->setOrigin(sf::Vector2f(size.x / -2, size.y * 1.5));
        else thisBlock->setOrigin(sf::Vector2f(size.x / -2, size.y * 1.5));
        thisBlock->setPosition(pos);
        thisBlock->setFillColor(sf::Color::Green);
        thisBlock->setOutlineColor(sf::Color::Blue);
        thisBlock->setOutlineThickness(-5.f);
    }
}

//============================================================
// Functions
//============================================================
void Piece::draw(sf::RenderWindow& window)
{
    for (auto& i : blocks) { window.draw(i); }
}

void Piece::move(sf::Vector2f&& direction)
{
    for (auto& i : blocks) { i.move(direction); }
}

void Piece::rotate()
{
    for (auto& i : blocks) { i.rotate(90.f); }
}

std::vector<sf::Vector2f> Piece::getPositions()
{
    std::vector<sf::Vector2f> positions;
    for (auto&& i : blocks) positions.push_back(i.getPosition());

    return positions;
}