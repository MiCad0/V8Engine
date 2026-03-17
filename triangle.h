//
// Created by micad0 on 14/03/2026.
//

#ifndef V8ENGINE_TRIANGLE_H
#define V8ENGINE_TRIANGLE_H
#include <vector>
#include <glm/vec3.hpp>
#include <glm/ext/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec4 color;
    glm::vec2 uv;

    bool operator==(const Vertex& other) const {
        return pos == other.pos && color == other.color && normal == other.normal && uv == other.uv;
    }

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 4> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 4> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, normal);

        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32B32A32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(Vertex, color);

        attributeDescriptions[3].binding = 0;
        attributeDescriptions[3].location = 3;
        attributeDescriptions[3].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[3].offset = offsetof(Vertex, uv);

        return attributeDescriptions;
    }
};


template<> struct std::hash<Vertex> {
    size_t operator()(Vertex const& vertex) const noexcept {
        return (((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.normal) << 1)) >> 1) ^ (hash<glm::vec3>()(vertex.color)) ^ (hash<glm::vec2>()(vertex.uv) << 1));
    }
};

class Triangle {
public:
    Triangle(): vertices{
        {{ 0.0f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{ 0.5f,  0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}}
    }{}
    Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 color):vertices{
        {a, color},
        {b, color},
        {c, color}
    }{}

    glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::vec3 rotation{0.0f, 0.0f, 0.0f};


    [[nodiscard]] glm::mat4 get_model_matrix() const {
        return glm::translate(glm::mat4(1.0f), position);
    }

    std::vector<Vertex> get_vertices() {
        return vertices;
    }

    [[nodiscard]] size_t get_vertex_count() const {
        return vertices.size();
    }
private:
    std::vector<Vertex> vertices;
};


#endif //V8ENGINE_TRIANGLE_H