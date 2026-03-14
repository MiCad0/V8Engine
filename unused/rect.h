//
// Created by MiCad0 on 13/03/2026.
//

#ifndef V8ENGINE_RECT_H
#define V8ENGINE_RECT_H
#include <array>
#include <vector>
#include <glm/glm.hpp>
#include <vulkan/vulkan_core.h>
#include "../triangle.h"



class Rect {
public:
    Rect(): triangles{
        {{-0.5f,  0.5f, 0.0f}, { 0.5f,  0.5f, 0.0f}, {-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}},
        {{ 0.5f,  0.5f, 0.0f}, {-0.5f, -0.5f, 0.0f}, { 0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}}
    } {}
    //Rect(const glm::vec3 a, const glm::vec3 b, const glm::vec3 c, const glm::vec3 d): vertices{{a, {1.0f, 1.0f, 1.0f}}, {b,{1.0f, 1.0f, 1.0f}}, {c,{1.0f, 1.0f, 1.0f}}, {d, {1.0f, 1.0f, 1.0f}}} {}


    std::vector<Vertex> get_vertices() {
        std::vector<Vertex> nb_vertices{};
        for (auto& triangle: triangles) {
            for (auto n{0}; n < triangle.get_vertex_count(); n++) {
                nb_vertices.push_back()
            }
        }
    }

    static std::vector<uint32_t> get_indices(const uint32_t i) {
        if (i == 0) {
            return std::vector<uint32_t>{0,1,2};
        }
        return std::vector<uint32_t>{1,2,3};
    }

    static std::vector<uint32_t> get_all_indices(const uint32_t i) {
        return std::vector<uint32_t>{0,2,1,1,2,3};
    }

private:
    std::vector<Triangle> triangles;
};


#endif //V8ENGINE_RECT_H