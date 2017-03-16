#version 430

in vec3 o_normal;
in vec3 toLightDir, halfDir;
out vec4 fragColor;
in vec2 tc;

layout(binding = 3) uniform LIGHT{
	vec4 lightpos;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

uniform sampler2D TEX;

void main(){
	float Ka = 0.2f;
	float Kd = 0.5f;
	float Ks = 0.7f;

	float Kdld_f = Kd*dot(toLightDir, o_normal);
	float Ksls_f = Ks*dot(o_normal, halfDir);

	//vec3 Kala = Ka*texture2D(TEX, tc).rgb;//ambient.xyz;
	//vec3 Kala = Ka*vec3(1.f, 0.f, 0.f);
	vec3 Kdld = max(Kdld_f*diffuse.xyz, 0);
	vec3 Ksls = max(Ksls_f*specular.xyz, 0);

	//fragColor = vec4( Kala + Kdld + Ksls, 1.0f);
	fragColor = vec4(1.f, 0.f, 0.f, 1.f);
}