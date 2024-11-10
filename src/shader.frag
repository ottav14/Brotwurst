#version 330 core
out vec4 FragColor;

#define ITERATIONS 100
#define MAX_DISTANCE 5000

uniform vec2 u_resolution;
uniform vec2 u_position;
uniform float u_zoom;
uniform float u_time;

float bounce() {
	return 0.5*sin(u_time)+0.5;
}

float trap(vec2 z) {
	float point = distance(z, vec2(cos(u_time), sin(u_time)));
	float line = min(abs(z.x), abs(z.y));
	
	return mix(line, point, bounce());
}

float get_trap(vec2 c) {

	vec2 z = vec2(c.x, c.y);
	float d = MAX_DISTANCE;
	
	for(int i=0; i<ITERATIONS; i++) {
		float a = z.x*z.x - z.y*z.y + c.x;
		float b = 2*z.x*z.y + c.y;
		z = vec2(a, b);
		d = min(d, trap(z));
		if(length(z) > MAX_DISTANCE)
			break;
	}
	return d;
}

void main() {

	vec3 cols[8];

	cols[0] = vec3(255,   0,   0) / 255;
	cols[1] = vec3(255, 127,   0) / 255;
	cols[2] = vec3(255, 255,   0) / 255;
	cols[3] = vec3(  0, 255,   0) / 255;
	cols[4] = vec3(  0,   0, 255) / 255;
	cols[5] = vec3( 75,   0, 130) / 255;
	cols[6] = vec3(238, 130, 238) / 255;
	cols[7] = vec3(255,   0,   0) / 255;

	vec2 c = u_zoom * (2.0 * gl_FragCoord.xy / u_resolution - 1.0) + u_position;
	float d = 1-get_trap(c);
	d = 6 * clamp(0, 1, pow(d, 3));
	vec3 col= mix(cols[int(d)], cols[int(d)+1], fract(d));

    FragColor = vec4(col, 1.0); 

}
