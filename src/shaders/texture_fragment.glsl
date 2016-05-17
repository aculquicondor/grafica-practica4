#version 330

in vec2 UV;
in vec4 fragmentColor;
in vec3 normal_cameraSpace;
in vec3 lightDirection_cameraSpace;
in vec3 eyeDirection_cameraSpace;

out vec3 color;

uniform sampler2D textureSampler;
uniform vec3 lightColor;
uniform vec3 ambientLight;

void main() {
    vec3 materialColor = texture(textureSampler, UV).rgb;
    vec3 ambientColor = ambientLight * materialColor;

    vec3 n = normalize(normal_cameraSpace);
    vec3 l = normalize(lightDirection_cameraSpace);
    float cosTheta = clamp(dot(n, l), 0, 1);
    vec3 diffuseColor = lightColor * cosTheta * materialColor;

    vec3 E = normalize(eyeDirection_cameraSpace);
    vec3 R = reflect(-l, n);
    float cosAlpha = clamp(dot(E, R), 0, 1);
    vec3 specularColor = fragmentColor.rgb * lightColor * pow(cosAlpha, 5);

    color = ambientColor + diffuseColor + specularColor;
}
