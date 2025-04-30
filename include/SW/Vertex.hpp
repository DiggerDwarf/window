#ifndef __Vertex_hpp_INCLUDED
#define __Vertex_hpp_INCLUDED

#include <SW/Config.hpp>

#include <SW/Vector.hpp>
#include <SW/Color.hpp>

namespace sw
{

class SW_API Vertex
{
    fVec3 m_position;
    fVec2 m_texCoord;
    Color m_color;

public:

    Vertex();
    Vertex(const fVec3& position);
    Vertex(float x, float y, float z);
    Vertex(const fVec3& position, Color color, const fVec2& texCoord = fVec2(0));

    const Color& get_color() const;
    const fVec3& get_position() const;
    const fVec2 get_position_2D() const;
    const fVec2& get_texCoord() const;

    void set_color(const Color& color);
    void set_position(const fVec3& position);
    void set_position_2D(const fVec2& position);
    void set_texCoord(const fVec2& texCoord);
};

}   // namespace sw

#endif // __Vertex_hpp_INCLUDED
