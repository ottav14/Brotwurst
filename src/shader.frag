#version 330 core
out vec4 FragColor;

#define ITERATIONS 100
#define MAX_DISTANCE 5000
#define PI 3.141592

uniform vec2 u_resolution;
uniform vec2 u_position;
uniform float u_zoom;
uniform float u_time;

float wave(vec2 p, float tb, float ra) {
    tb = 3.1415927*5.0/6.0*max(tb,0.0001);
    vec2 co = ra*vec2(sin(tb),cos(tb));
    p.x = abs(mod(p.x,co.x*4.0)-co.x*2.0);
    vec2  p1 = p;
    vec2  p2 = vec2(abs(p.x-2.0*co.x),-p.y+2.0*co.y);
    float d1 = ((co.y*p1.x>co.x*p1.y) ? length(p1-co) : abs(length(p1)-ra));
    float d2 = ((co.y*p2.x>co.x*p2.y) ? length(p2-co) : abs(length(p2)-ra));
    return min(d1, d2);
}

float triangle(vec2 p, float r) {
    const float k = sqrt(3.0);
    p.x = abs(p.x) - r;
    p.y = p.y + r/k;

    if(p.x + k * p.y > 0.0) 
		p = vec2(p.x - k * p.y, -k * p.x - p.y) / 2.0;

    p.x -= clamp(p.x, -2.0 * r, 0.0);
    return -length(p) * sign(p.y);
}

float bounce() {
	return 0.5*sin(u_time)+0.5;
}

float trap(vec2 z) {
	float point = length(z);
	
	return point;
}

vec3 color(vec3 a, vec3 b, vec3 c, vec3 d, float t) {
	return a + b * cos(2.0 * PI * (c * t + d));
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

	vec3 as[7];
	vec3 bs[7];
	vec3 cs[7];
	vec3 ds[7];

	as[0] = vec3(0.5);
	as[1] = vec3(0.5); 
	as[2] = vec3(0.5);
	as[3] = vec3(0.5);
	as[4] = vec3(0.5);
	as[5] = vec3(0.5);
	as[6] = vec3(0.8, 0.5, 0.4);

	bs[0] = vec3(0.5);
	bs[1] = vec3(0.5);
	bs[2] = vec3(0.5);
	bs[3] = vec3(0.5);
	bs[4] = vec3(0.5);
	bs[5] = vec3(0.5);
	bs[6] = vec3(0.2, 0.4, 0.2);

	cs[0] = vec3(1.0);
	cs[1] = vec3(1.0);
	cs[2] = vec3(1.0);
	cs[3] = vec3(1.0, 1.0, 0.5);
	cs[4] = vec3(1.0, 0.7, 0.4);
	cs[5] = vec3(2.0, 1.0, 0.0);
	cs[6] = vec3(2.0, 1.0, 1.0);

	ds[0] = vec3(0.0, 0.33, 0.67);
	ds[1] = vec3(0.0, 0.1, 0.2);
	ds[2] = vec3(0.3, 0.2, 0.2);
	ds[3] = vec3(0.8, 0.9, 0.3);
	ds[4] = vec3(0.0, 0.15, 0.2);
	ds[5] = vec3(0.5, 0.2, 0.25);
	ds[6] = vec3(0.0, 0.25, 0.25);


	vec2 uv = u_zoom * (2.0 * gl_FragCoord.xy / u_resolution - 1.0) + u_position;
	int i = 2;

	float t = 1-get_trap(uv);
	vec3 a = vec3(0.5);
	vec3 b = vec3(0.5);
	vec3 c = vec3(2.0, 1.0, 0.0);
	vec3 d = vec3(0.5, 0.2, 0.25);

	vec3 col = color(as[i], bs[i], cs[i], ds[i], t);

    FragColor = vec4(col, 1.0); 

}
