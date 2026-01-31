#version 410 core

uniform vec3 u_BaseColor;
out vec4 FragColor;

void main() {
    FragColor = vec4(u_BaseColor, 1.0);
}