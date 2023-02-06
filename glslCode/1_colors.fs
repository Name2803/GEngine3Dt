#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;  
in vec3 FragPos; 

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform sampler2D Texture;
uniform sampler2D Texture2;
uniform vec3 viewPos; 
uniform vec3 objectColor;

void main()
{
	// ambient
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;
      	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1000);
    vec3 specular = specularStrength * spec * lightColor;  
    
    vec4 result = vec4((ambient + diffuse + specular), 1.0f) * vec4(ourColor, 1.0f);
	FragColor = result;
}    