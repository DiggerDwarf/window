#include <SW/VertexArray.hpp>

namespace sw
{

VertexArray::VertexArray()
{
}

VertexArray::VertexArray(std::initializer_list<Vertex> vertices, std::initializer_list<unsigned> indices)
    : vertices(vertices), indices(indices)
{
}

VertexArray::VertexArray(const Vertex* vertices, unsigned vertexCount, const unsigned* indices, unsigned indexCount)
    : vertices(vertices, vertices + vertexCount), indices(indices, indices + indexCount)
{
}

void VertexArray::addVertex(const Vertex& vertex)
{
    this->vertices.push_back(vertex);
}

void VertexArray::addVertices(const Vertex* vertices, unsigned count)
{
    this->vertices.insert(this->vertices.end(), vertices, vertices + count);
}

void VertexArray::addVertices(std::initializer_list<Vertex> vertices)
{
    this->vertices.insert(this->vertices.end(), vertices);
}

void VertexArray::addIndices(const unsigned* indices, unsigned count)
{
    this->indices.insert(this->indices.end(), indices, indices + count);
}

void VertexArray::addIndices(std::initializer_list<unsigned> indices)
{
    this->indices.insert(this->indices.end(), indices);
}

void VertexArray::mergeWith(const VertexArray& other)
{
    unsigned offset = this->vertices.size();
    this->vertices.insert(this->vertices.end(), other.vertices.begin(), other.vertices.end());
    this->indices.resize(this->indices.size() + other.indices.size());
    for (size_t i = 0; i < other.indices.size(); i++)
        this->indices.push_back(other.indices[i] + offset);
}

}   // namespace sw
