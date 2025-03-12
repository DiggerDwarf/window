#include <SW/Vertex.hpp>

namespace sw
{

Vertex::Vertex()
    : m_position(fVec3(0, 0, 0)), m_texCoord(fVec2(0, 0)), m_color(Color::White)
{
}

Vertex::Vertex(fVec3 position, Color color, fVec2 texCoord)
    : m_position(position), m_texCoord(texCoord), m_color(color)
{
}

const Color& Vertex::get_color() const
{
    return this->m_color;
}

const fVec3& Vertex::get_position() const
{
    return this->m_position;
}

const fVec2 Vertex::get_position_2D() const
{
    return fVec2(this->m_position.x, this->m_position.y);
}

const fVec2& Vertex::get_texCoord() const
{
    return this->m_texCoord;
}

void Vertex::set_color(const Color& color)
{
    this->m_color = color;
}

void Vertex::set_position(const fVec3& position)
{
    this->m_position = position;
}

void Vertex::set_position_2D(const fVec2& position)
{
    this->m_position = fVec3(position.x, position.y, 0);
}

void Vertex::set_texCoord(const fVec2& texCoord)
{
    this->m_texCoord = texCoord;
}

}   // namespace sw
