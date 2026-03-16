//
// Created by micad0 on 14/03/2026.
//

#ifndef V8ENGINE_MESH_H
#define V8ENGINE_MESH_H

#include <vector>
#include "triangle.h"

class Mesh {
public:
    Mesh() = default;

    [[nodiscard]] const std::vector<Vertex>& get_vertices() const { return vertices; }
    [[nodiscard]] const std::vector<uint32_t>& get_opaque_indices() const { return opaqueIndices; }
    [[nodiscard]] const std::vector<uint32_t>& get_transparent_indices() const { return transparentIndices; }

    [[nodiscard]] size_t get_vertex_count() const { return vertices.size(); }
    [[nodiscard]] size_t get_opaque_index_count() const { return opaqueIndices.size(); }
    [[nodiscard]] size_t get_transparent_index_count() const { return transparentIndices.size(); }

    [[nodiscard]] glm::mat4 get_model_matrix() const { return modelMatrix; }
    void set_model_matrix(const glm::mat4& matrix) { modelMatrix = matrix; }

    void set_vertices(const std::vector<Vertex>& new_vertices) { vertices = new_vertices; }
    void set_opaque_indices(const std::vector<uint32_t>& new_indices) { opaqueIndices = new_indices; }
    void set_transparent_indices(const std::vector<uint32_t>& new_indices) { transparentIndices = new_indices; }

private:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> opaqueIndices;
    std::vector<uint32_t> transparentIndices;
    glm::mat4 modelMatrix{1.0f};
};

#endif //V8ENGINE_MESH_H