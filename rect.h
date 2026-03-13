//
// Created by MiCad0 on 13/03/2026.
//

#ifndef V8ENGINE_RECT_H
#define V8ENGINE_RECT_H
#include <array>
#include <vector>
#include <glm/glm.hpp>
#include <vulkan/vulkan_core.h>


struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        return attributeDescriptions;
    }
};

class rect {
public:
    rect(): vertices{
        {{-0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}},
        {{ 0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}},
        {{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}},
        {{ 0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}}
    } {}
    rect(const glm::vec3 a, const glm::vec3 b, const glm::vec3 c, const glm::vec3 d): vertices{{a, {1.0f, 1.0f, 1.0f}}, {b,{1.0f, 1.0f, 1.0f}}, {c,{1.0f, 1.0f, 1.0f}}, {d, {1.0f, 1.0f, 1.0f}}} {}

    void move_to(const glm::vec3 dest) {
        const auto dir = dest - vertices[0].pos;
        for (auto& v : vertices) {
            v.pos += dir;
        }
    }

    void move_for(const glm::vec3 dir) {
        for (auto& v : vertices) {
            v.pos += dir;
        }
    }

    std::vector<Vertex> get_vertices() {
        return vertices;
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
    std::vector<Vertex> vertices;
};


#endif //V8ENGINE_RECT_H