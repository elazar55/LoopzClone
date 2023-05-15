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
Block::Block() : m_pos(Vector2f(FLT_MAX, FLT_MAX)), m_doors{false} {}

/* ========================================================================== */
/*                             Custom Constructor                             */
/* ========================================================================== */
Block::Block(Vector2f pos, float size, const bitset<4> doors) :
    m_pos(pos),
    m_doors(doors),
    shape(Vector2f(size, size))
{
    shape.setPosition(m_pos);
    shape.setOutlineColor(Color::Blue);
    shape.setOutlineThickness(-5.f);
}

/* ========================================================================== */
/*                                Get Position                                */
/* ========================================================================== */
Vector2f Block::getPosition()
{
    return m_pos;
}

/* ========================================================================== */
/*                                  Get Size                                  */
/* ========================================================================== */
Vector2f Block::getSize()
{
    return Vector2f(shape.getSize());
}

/* ========================================================================== */
/*                                  Set Doors                                 */
/* ========================================================================== */
void Block::setDoors(const bitset<4> doors)
{
    for (size_t i = 0; i < sizeof(m_doors); i++)
    {
        m_doors[i] = doors[i];
    }
}

/* ========================================================================== */
/*                                    Move                                    */
/* ========================================================================== */
void Block::move(Vector2f direction)
{
    m_pos += direction;
    shape.setPosition(m_pos);
}

/* ========================================================================== */
/*                                   Rotate                                   */
/* ========================================================================== */
void Block::rotate(float degrees, Vector2f& origin)
{
    const double PI       = 3.141592653589793238;
    double       radians  = degrees * PI / 180.f;
    double       sinTheta = std::round(std::sin(radians));
    double       cosTheta = std::round(std::cos(radians));

    int localx = m_pos.x - origin.x;
    int localy = m_pos.y - origin.y;

    m_pos.x = (localx * cosTheta) + (localy * -sinTheta);
    m_pos.y = (localx * sinTheta) + (localy * cosTheta);

    m_pos.x += origin.x;
    m_pos.y += origin.y;

    shape.setPosition(m_pos);

    // Rotate doors now
    bool matrix[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    };
    static_assert(sizeof(m_doors) == sizeof(matrix[0]));

    bool copy[4];
    for (int i = 0; i < 4; i++) copy[i] = m_doors[i];

    for (size_t i = 0; i < sizeof(m_doors); i++)
    {
        int j = i + sinTheta;
        if (j == 4) j = 0;
        else if (j == -1) j = 3;

        copy[i] = Dot<bitset<4>, bool[4]>(m_doors, matrix[j], m_doors.size());
    }

    for (size_t i = 0; i < sizeof(m_doors); i++)
    {
        m_doors[i] = copy[i];
    }

    cout << m_doors << endl;
}

/* ========================================================================== */
/*                                    Draw                                    */
/* ========================================================================== */
void Block::draw(RenderWindow& window)
{
    Uint32 color = 0xFFFFFFFF;
    if (m_doors[0]) color = 0xff1100FF;
    if (m_doors[1]) color = 0xb1ff00FF;
    if (m_doors[2]) color = 0xffd966FF;
    if (m_doors[3]) color = 0x9fc5e8FF;
    shape.setFillColor(Color(color));
    window.draw(shape);
}

/* ========================================================================== */
/*                                 Dot Product                                */
/* ========================================================================== */
template<typename T, typename U>
int Block::Dot(T v1, U v2, size_t length)
{
    int result{};

    for (size_t i = 0; i < length; i++) result += (v1[i] * v2[i]);

    return result;
}