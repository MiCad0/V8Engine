//
// Created by MiCad0 on 16/03/2026.
//

#ifndef V8ENGINE_CAMERA_H
#define V8ENGINE_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera {
public:
    // Camera settings
    glm::vec3 position{0.0f, 0.0f, 4.0f};
    glm::vec3 front{0.0f, 0.0f, -1.0f};
    glm::vec3 up{0.0f, 1.0f, 0.0f};

    float speed{2.0f};
    float yaw{-90.0f};
    float pitch{0.0f};

    // Mouse info
    bool firstMouse{true};
    double lastX{1920.0 / 2.0};
    double lastY{1080.0 / 2.0};
    float sensitivity{0.1f};

    Camera() = default;

    [[nodiscard]] glm::mat4 getViewMatrix() const {
        return glm::lookAt(position, position + front, up);
    }

    void processKeyboard(const bool* keys, float deltaTime) {
        float velocity = speed * deltaTime;
        if (keys[GLFW_KEY_W])           position += front * velocity;
        if (keys[GLFW_KEY_S])           position -= front * velocity;
        if (keys[GLFW_KEY_A])           position -= glm::normalize(glm::cross(front, up)) * velocity;
        if (keys[GLFW_KEY_D])           position += glm::normalize(glm::cross(front, up)) * velocity;
        if (keys[GLFW_KEY_SPACE])       position += up * velocity;
        if (keys[GLFW_KEY_LEFT_SHIFT])  position -= up * velocity;
    }

    void processMouseMovement(double xpos, double ypos) {
        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        auto xoffset = static_cast<float>(xpos - lastX);
        auto yoffset = static_cast<float>(lastY - ypos);

        lastX = xpos;
        lastY = ypos;

        yaw += xoffset * sensitivity;
        pitch += yoffset * sensitivity;

        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        updateCameraVectors();
    }

    void processMouseScroll(double yoffset) {
        if (yoffset > 0) {
            if (speed <= 1000.0f) speed /= 0.8f;
        } else {
            if (speed >= 0.001f) speed *= 0.8f;
        }
    }

private:
    void updateCameraVectors() {
        glm::vec3 newFront;
        newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        newFront.y = sin(glm::radians(pitch));
        newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(newFront);
    }
};

#endif //V8ENGINE_CAMERA_H