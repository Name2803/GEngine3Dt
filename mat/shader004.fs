#version 460 core
out vec4 FragColor;

in vec3 ourColor;
  

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;

void main()
{
    //FragColor = texture(ourTexture, TexCoord);
    //FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0);
    FragColor = mix(texture(texture1, TexCoord)  , texture(texture2, TexCoord), 0.5);
    FragColor = mix(texture(texture2, TexCoord), texture(texture4, TexCoord), 0.5);
}