#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0f); 
    TexCoords = vec2(aTexCoord.x, aTexCoord.y);
}