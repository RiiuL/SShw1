#version 430

// 현재 vertex는 world space. Mview 곱해야 카메라 space
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 texture;
layout(location = 2) in vec3 normal;

out vec3 o_normal;
out vec3 toLightDir, halfDir;
out vec2 tc;

uniform mat4 Mproj;
uniform mat4 Mview;

// 현재 light는 카메라 space에 정의되어 있음.
layout(binding = 3) uniform LIGHT{
	vec4 lightpos;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

void main(){
	vec4 CSposition = Mview * vec4(position, 1.0f); //카메라 스페이스로 변환

	vec3 toViewer = normalize( -1 * CSposition.xyz );
	toLightDir = normalize( lightpos.xyz - CSposition.xyz );
	halfDir = normalize( toViewer + toLightDir );

	o_normal = normalize( (Mview * vec4(normal, 0.f)).xyz ); // normal도 카메라 스페이스로 변환해야지.
	gl_Position = Mproj * CSposition;

	tc = texture.xy;
}

