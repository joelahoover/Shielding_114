uniform vec2 position;

const float pi = 3.14159265;

void main()
{	
	vec2 pos = position + gl_TexCoord[0].xy * vec2(640.0, 480.0);
    float theta = atan(pos.x / pos.y);
    float r = length(pos);
	float r2 = length(pos+vec2(0.0, 2700.0));
	float inside = clamp(2650.0*50.0/r - 49.0 - 100.0*5.0/r2 + 4.0, 0.0, 2.0);
	float outside = sin(clamp(150.0*20.0/r2 - 10.0, 0.0, 8.0*pi));

	gl_FragColor = vec4(mix(vec3(0.1, 0.4, 0.5)*outside, gl_Color.rgb * inside, min(inside,1.0)), mix(outside, inside, min(inside,1.0)));
}
