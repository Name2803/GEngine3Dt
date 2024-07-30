#version 410 core
layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_color;

out vec4 a_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	a_color = vec4(v_color ,1.0f);
	gl_Position = projection * view * model * vec4(v_position, 1.0);
}