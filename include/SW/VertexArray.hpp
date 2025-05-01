#ifndef __VertexArray_hpp_INCLUDED
#define __VertexArray_hpp_INCLUDED

#include <SW/Config.hpp>
#include <SW/Vertex.hpp>

#include <initializer_list>
#include <vector>

namespace sw
{

class SW_API VertexArray
{
public:
    std::vector<Vertex>     vertices;
    std::vector<unsigned>   indices;
public:
    VertexArray();
    VertexArray(std::initializer_list<Vertex> vertices, std::initializer_list<unsigned> indices);
    VertexArray(const Vertex* vertices, unsigned vertexCount, const unsigned* indices, unsigned indexCount);

    void addVertex(const Vertex& vertex);
    void addVertices(const Vertex* vertices, unsigned count);
    void addVertices(std::initializer_list<Vertex> vertices);
    void addIndices(const unsigned* indices, unsigned count);
    void addIndices(std::initializer_list<unsigned> indices);

    void mergeWith(const VertexArray& other);
};

}   // namespace sw


#endif // __VertexArray_hpp_INCLUDED
