#version 330 core
out vec4 FragColor;

#define ITERATIONS 100

uniform vec2 u_resolution;
uniform vec2 u_position;
uniform float u_zoom;

void main() {

	vec2 c = u_zoom * (2.0 * gl_FragCoord.xy / u_resolution - 1.0) + u_position;
	vec2 z = vec2(c.x, c.y);
	int i;
	
	for(i=0; i<ITERATIONS; i++) {
		float a = z.x*z.x - z.y*z.y + c.x;
		float b = 2*z.x*z.y + c.y;
		z = vec2(a, b);
		if(length(z) > 2)
			break;
	}

    FragColor = vec4(vec3(i * 0.01 + 0.1), 1.0); 

}
