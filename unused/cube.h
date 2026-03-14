//
// Created by MiCad0 on 13/03/2026.
//

#ifndef V8ENGINE_CUBE_H
#define V8ENGINE_CUBE_H
#include <array>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <vulkan/vulkan_core.h>
#include "rect.h"

class Cube {
public:
    Cube() {faces.push_back(Rect({ 0.5f, -0.5f,  0.5f}, {-0.5f, -0.5f,  0.5f},
                         { 0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f,  0.5f}));

        faces.push_back(Rect({-0.5f, -0.5f, -0.5f}, { 0.5f, -0.5f, -0.5f},
                             {-0.5f,  0.5f, -0.5f}, { 0.5f,  0.5f, -0.5f}));

        faces.push_back(Rect({-0.5f, -0.5f,  0.5f}, {-0.5f, -0.5f, -0.5f},
                             {-0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f, -0.5f}));

        faces.push_back(Rect({ 0.5f, -0.5f, -0.5f}, { 0.5f, -0.5f,  0.5f},
                             { 0.5f,  0.5f, -0.5f}, { 0.5f,  0.5f,  0.5f}));

        faces.push_back(Rect({ 0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f},
                             { 0.5f, -0.5f,  0.5f}, {-0.5f, -0.5f,  0.5f}));

        faces.push_back(Rect({-0.5f,  0.5f, -0.5f}, { 0.5f,  0.5f, -0.5f},
                             {-0.5f,  0.5f,  0.5f}, { 0.5f,  0.5f,  0.5f}));
    }

    glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::vec3 rotation{0.0f, 0.0f, 0.0f};

    glm::mat4 get_model_matrix() {
        return glm::translate(glm::mat4(1.0f), position);
    }

    std::vector<Vertex> get_vertices() {
        std::vector<Vertex> allVertices;
        std::vector<glm::vec3> faceColors = {
            {1.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 1.0f},
            {1.0f, 1.0f, 0.0f},
            {1.0f, 0.0f, 1.0f},
            {0.0f, 1.0f, 1.0f}
        };

        int faceIndex = 0;
        for (auto& face : faces) {
            auto v = face.get_vertices();

            v[0].color = faceColors[faceIndex];
            v[1].color = faceColors[faceIndex];
            v[2].color = faceColors[faceIndex];
            v[3].color = faceColors[faceIndex];

            allVertices.push_back(v[0]);
            allVertices.push_back(v[1]);
            allVertices.push_back(v[2]);

            allVertices.push_back(v[2]);
            allVertices.push_back(v[1]);
            allVertices.push_back(v[3]);

            faceIndex++;
        }
        return allVertices;
    }

    size_t get_vertex_count() {
        return faces.size() * 6;
    }

private:
    std::vector<Rect> faces;
};


#endif //V8ENGINE_CUBE_H