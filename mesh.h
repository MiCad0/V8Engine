//
// Created by micad0 on 14/03/2026.
//

#ifndef V8ENGINE_MESH_H
#define V8ENGINE_MESH_H

#include <vector>
#include <glm/vec3.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "triangle.h"

class Mesh {
public:
    Mesh() = default;

    void add_triangle(const Triangle& t) {
        triangles.push_back(t);
    }

    glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::vec3 rotation{0.0f, 0.0f, 0.0f};

    [[nodiscard]] glm::mat4 get_model_matrix() const {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), position);

        model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

        return model;
    }

    std::vector<Vertex> get_vertices() {
        std::vector<Vertex> all_vertices;
        all_vertices.reserve(triangles.size() * 3);

        for (auto& t : triangles) {
            auto v = t.get_vertices();
            all_vertices.insert(all_vertices.end(), v.begin(), v.end());
        }
        return all_vertices;
    }

    [[nodiscard]] size_t get_vertex_count() const {
        return triangles.size() * 3;
    }

private:
    std::vector<Triangle> triangles;
};

#endif //V8ENGINE_MESH_H