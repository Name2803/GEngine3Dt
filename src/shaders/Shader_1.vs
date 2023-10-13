#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec3 aNormal;

out vec4 ourColor; // output a color to the fragment shader
out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    ourColor = vec4(aColor, 1.0);
    TexCoords = aTexCoords;
}  