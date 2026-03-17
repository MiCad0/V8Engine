#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec4 inColor;
layout(location = 3) in vec2 inTexCoord;
layout(location = 4) in vec3 instancePos;

layout(binding = 0) uniform UniformBufferObject {
    mat4 view;
    mat4 proj;
    vec3 lightDir;
} ubo;

layout(push_constant) uniform Push {
    mat4 model;
} push;

layout(location = 0) out vec3 fragNormal;
layout(location = 1) out vec4 fragColor;
layout(location = 2) out vec3 fragLightDir;
layout(location = 3) out vec3 viewVec;
layout(location = 4) out vec2 fragTexCoord;

void main() {
    vec4 worldPosition = push.model * vec4(inPosition + instancePos, 1.0);
    gl_Position = ubo.proj * ubo.view * worldPosition;
    fragNormal = mat3(push.model) * inNormal;
    fragColor = inColor;
    fragLightDir = ubo.lightDir;
    viewVec = normalize(vec3(0,0,4) - worldPosition.xyz);
    fragTexCoord = inTexCoord;
}
