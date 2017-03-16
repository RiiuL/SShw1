#version 430

// ���� vertex�� world space. Mview ���ؾ� ī�޶� space
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 texture;
layout(location = 2) in vec3 normal;

out vec3 o_normal;
out vec3 toLightDir, halfDir;
out vec2 tc;

uniform mat4 Mproj;
uniform mat4 Mview;

// ���� light�� ī�޶� space�� ���ǵǾ� ����.
layout(binding = 3) uniform LIGHT{
	vec4 lightpos;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

void main(){
	vec4 CSposition = Mview * vec4(position, 1.0f); //ī�޶� �����̽��� ��ȯ

	vec3 toViewer = normalize( -1 * CSposition.xyz );
	toLightDir = normalize( lightpos.xyz - CSposition.xyz );
	halfDir = normalize( toViewer + toLightDir );

	o_normal = normalize( (Mview * vec4(normal, 0.f)).xyz ); // normal�� ī�޶� �����̽��� ��ȯ�ؾ���.
	gl_Position = Mproj * CSposition;

	tc = texture.xy;
}

