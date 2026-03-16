#version 450

layout(location = 0) in vec3 fragNormal;
layout(location = 1) in vec4 fragColor;
layout(location = 2) in vec3 fragLightDir;
layout(location = 3) in vec3 viewVec;

layout(location = 0) out vec4 outColor;

void main() {
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(fragLightDir);
    vec3 view = normalize(viewVec);
    vec3 reflect = reflect(-lightDir, normal);

    float ambientIntensity = 0.15;
    vec3 ambient = ambientIntensity * fragColor.rgb;

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * fragColor.rgb;

    float specularStrength = 0.5;
    float spec = pow(max(dot(view, reflect), 0.0), 32.0);
    vec3 specular = specularStrength * spec * vec3(1.0);

    vec3 finalColor = (ambient + diffuse + specular);
    outColor = vec4(finalColor, fragColor.a);
}