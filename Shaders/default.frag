#version 330 core

out vec4 FragColor;
in vec3 vColor;

in vec2 vTex;
uniform sampler2D tex0;

void main() {
    FragColor = texture(tex0, vTex);
};
