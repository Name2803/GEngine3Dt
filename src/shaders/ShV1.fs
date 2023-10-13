#version 410 core
out vec4 FragColor;  
in vec4 ourColor;
in vec2 TexCoord;

uniform vec4 customLight;

uniform sampler2D texture1;

void main()
{
    vec4 texColor = texture(texture1, vec2(TexCoord.x / 29.9f + 23.39f / 30.0f, TexCoord.y / 35.0f + 14.439f / 35.0f));
    if(texColor.w < 0.1)
        discard;
    FragColor = texColor;
}