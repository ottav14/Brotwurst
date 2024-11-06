#version 330 core
out vec4 FragColor;

uniform vec2 u_resolution;

void main() {

	vec2 uv = gl_FragCoord.xy / u_resolution;
	vec3 col = vec3(uv, 0.0);

    FragColor = vec4(col, 1.0); 

}
