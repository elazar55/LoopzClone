/* ========================================================================== */
/*                                   Headers                                  */
/* ========================================================================== */
#include "Block.h"
#include <cassert>
#include <cmath>
#include <float.h>
#include <iostream>
using namespace std;
using namespace sf;

/* ========================================================================== */
/*                             Empty Constructor                            */
/* ========================================================================== */
Block::Block() : position_(Vector2f(FLT_MAX, FLT_MAX)), doors_{false} {}

/* ========================================================================== */
/*                             Custom Constructor                             */
/* ========================================================================== */
Block::Block(Vector2f pos, float size, const bitset<4> doors) :
    position_(pos),
    doors_(doors),
    shape_(Vector2f(size, size))
{
    shape_.setPosition(position_);
    shape_.setOutlineColor(Color::Blue);
    shape_.setOutlineThickness(-5.f);
}

/* ========================================================================== */
/*                                Get Position                                */
/* ========================================================================== */
Vector2f Block::Position() const
{
    return position_;
}

/* ========================================================================== */
/*                                  Get Size                                  */
/* ========================================================================== */
Vector2f Block::Size() const
{
    return Vector2f(shape_.getSize());
}

/* ========================================================================== */
/*                                  Set Doors                                 */
/* ========================================================================== */
void Block::SetDoors(bitset<4> doors)
{
    for (size_t i = 0; i < sizeof(doors_); i++)
    {
        doors_[i] = doors[i];
    }
}

bitset<4> Block::Doors() const
{
    return doors_;
}

/* ========================================================================== */
/*                                    Move                                    */
/* ========================================================================== */
void Block::Move(Vector2f direction)
{
    position_ += direction;
    shape_.setPosition(position_);
}

/* ========================================================================== */
/*                                   Rotate                                   */
/* ========================================================================== */
void Block::Rotate(float degrees, const Vector2f& origin)
{
    const double PI       = 3.141592653589793238;
    double       radians  = degrees * PI / 180.f;
    double       sinTheta = std::round(std::sin(radians));
    double       cosTheta = std::round(std::cos(radians));

    int localx = position_.x - origin.x;
    int localy = position_.y - origin.y;

    position_.x = (localx * cosTheta) + (localy * -sinTheta);
    position_.y = (localx * sinTheta) + (localy * cosTheta);

    position_.x += origin.x;
    position_.y += origin.y;

    shape_.setPosition(position_);

    const bitset<4> matrix[4] = {1, 2, 4, 8};
    bitset<4>       copy(doors_);
    assert(copy == doors_);

    for (size_t i = 0; i < sizeof(doors_); i++)
    {
        int j = i + sinTheta;
        if (j == 4) j = 0;
        else if (j == -1) j = 3;

        copy[i] = Dot<bitset<4>>(doors_, matrix[j], doors_.size());
    }

    doors_ = bitset<4>(copy);
    assert(doors_ == copy);
}

/* ========================================================================== */
/*                                    Draw                                    */
/* ========================================================================== */
void Block::Draw(RenderWindow& window)
{
    window.draw(shape_);
    if ((doors_ & DOOR_TOP) == DOOR_TOP)
    {
        CircleShape door1(5.f);
        Vector2f    Pos((shape_.getSize().x / 2) - 5.f, 0);
        door1.setPosition(position_ + Pos);
        door1.setFillColor(Color::Red);
        window.draw(door1);
    }
    if ((doors_ & DOOR_BOTTOM) == DOOR_BOTTOM)
    {
        CircleShape door1(5.f);
        Vector2f Pos((shape_.getSize().x / 2) - 5.f, shape_.getSize().y - 10.f);
        door1.setPosition(position_ + Pos);
        door1.setFillColor(Color::Red);
        window.draw(door1);
    }
    if ((doors_ & DOOR_LEFT) == DOOR_LEFT)
    {
        CircleShape door1(5.f);
        Vector2f    Pos(0, (shape_.getSize().y / 2) - 5);
        door1.setPosition(position_ + Pos);
        door1.setFillColor(Color::Red);
        window.draw(door1);
    }
    if ((doors_ & DOOR_RIGHT) == DOOR_RIGHT)
    {
        CircleShape door1(5.f);
        Vector2f    Pos(shape_.getSize().x - 10, (shape_.getSize().y / 2) - 5);
        door1.setPosition(position_ + Pos);
        door1.setFillColor(Color::Red);
        window.draw(door1);
    }
}

/* ========================================================================== */
/*                                  Is Empty                                  */
/* ========================================================================== */
bool Block::IsEmpty() const
{
    return position_.x == FLT_MAX ? true : false;
}

/* ========================================================================== */
/*                                  Set Color                                 */
/* ========================================================================== */
void Block::SetColor(sf::Color color)
{
    shape_.setFillColor(color);
}

/* ========================================================================== */
/*                                 Dot Product                                */
/* ========================================================================== */
template<typename T>
int Block::Dot(T v1, T v2, size_t length)
{
    int result{};

    for (size_t i = 0; i < length; i++) result += (v1[i] * v2[i]);

    return result;
}