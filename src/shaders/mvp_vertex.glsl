#version 330

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec2 vertexUV;
layout(location = 3) in vec3 vertexNormal;

out vec4 fragmentColor;
out vec2 UV;
out vec3 normal_cameraSpace;
out vec3 lightDirection_cameraSpace;
out vec3 eyeDirection_cameraSpace;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 lightPosition;

void main() {
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
    fragmentColor = vertexColor;
    UV = vertexUV;

    vec3 vertexPosition_cameraSpace = (V * M * vec4(vertexPosition_modelspace, 1)).xyz;
    vec3 lightPosition_cameraSpace = (V * vec4(lightPosition, 1)).xyz;

    eyeDirection_cameraSpace = vec3(0, 0, 0) - vertexPosition_cameraSpace;
    lightDirection_cameraSpace = lightPosition_cameraSpace + eyeDirection_cameraSpace;
    normal_cameraSpace = (V * M * vec4(vertexNormal, 0)).xyz;
}
