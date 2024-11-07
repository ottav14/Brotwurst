#version 330 core
out vec4 FragColor;

#define ITERATIONS 100

uniform vec2 u_resolution;
uniform vec2 u_position;
uniform float u_zoom;

void main() {

	vec3 cols[5];

	cols[0] = vec3(205, 246, 255) / 255;
	cols[1] = vec3(249, 208, 255) / 255;
	cols[2] = vec3(226, 246, 211) / 255;
	cols[3] = vec3(161, 197, 255) / 255;
	cols[4] = vec3(215, 274, 255) / 255;

	vec2 c = u_zoom * (2.0 * gl_FragCoord.xy / u_resolution - 1.0) + u_position;
	vec2 z = vec2(c.x, c.y);
	int i;
	float d = 100;
	
	for(i=0; i<ITERATIONS; i++) {
		float a = z.x*z.x - z.y*z.y + c.x;
		float b = 2*z.x*z.y + c.y;
		z = vec2(a, b);
		d = min(d, distance(z, vec2(-1, 0)));
		if(length(z) > 2)
			break;
	}
	float t = 3.0 * float(i) / float(ITERATIONS);
	i = int(t);
	t -= i;
	vec3 col = mix(cols[i], cols[i+1], t);
	col.r *= col.r;
	col.g *= col.g;
	col.b *= col.b;

    FragColor = vec4(col, 1.0); 

}
