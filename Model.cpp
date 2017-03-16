#include "Model.h"



Model::Model()
{
}


Model::~Model()
{
}

#define pi 3.14159265359
inline glm::vec3 Sphere_Point(GLuint R, GLuint HD, GLuint WD, int j, int i) {
	// radius, 높이 해상도, 너비 해상도, 위도, 경도
	float rj = R*sin(pi / HD *j);
	glm::vec3 p = { rj*cos(2 * pi / WD *i), rj*sin(2 * pi / WD *i), R*cos(pi / HD *j) };
	return p;
}
void Model::Load_Object() { //구 만들기
	GLuint HD = 20; //높이를 얼마로 나눌 건지(height division; resolution)
	GLuint WD = 50; //너비를 얼마로 나눌 건지.
	GLuint R = 10; //radius

	for (int j = 0; j < HD; j++) {
		for (int i = 0; i < WD; i++) {
			glm::vec3 lu = Sphere_Point(R, HD, WD, j, i); //left up
			glm::vec3 ld = Sphere_Point(R, HD, WD, j+1, i);
			glm::vec3 ru = Sphere_Point(R, HD, WD, j, i+1);
			glm::vec3 rd = Sphere_Point(R, HD, WD, j+1, i+1);

			vertex_list.push_back(lu); normal_list.push_back(normalize(lu));
			vertex_list.push_back(ld); normal_list.push_back(normalize(ld));
			vertex_list.push_back(ru); normal_list.push_back(normalize(ru));
			vertex_list.push_back(ru); normal_list.push_back(normalize(ru));
			vertex_list.push_back(ld); normal_list.push_back(normalize(ld));
			vertex_list.push_back(rd); normal_list.push_back(normalize(rd));
		}
	}
}

void Model::Load_Triangle() {
	glm::vec3 a = { 0.f, 0.5f, 0.f };//vertex_list[0];//
	glm::vec3 b = { 0.f, 0.f, 0.f };//vertex_list[1];//
	glm::vec3 c = { 0.5f, 0.f, 0.f };//vertex_list[2];//
	vertex_list.push_back(a);
	vertex_list.push_back(b);
	vertex_list.push_back(c);

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertex_list.size(), &vertex_list[0].x, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);
}


void Model::Load_Objfile(const char* obj_path) {
	std::fstream file;
	std::string line;
	file.open(obj_path, std::fstream::in);
	if (!file.is_open()) { //읽기 실패
		std::cout << "Obj File Not Found" << std::endl;
		return;
	}


	// loading part
	typedef struct _triangle {
		int v1[3] = { -1, -1, -1 }; //첫 번째 vertex의 pos/tex/norm index. 없으면 -1
		int v2[3] = { -1, -1, -1 };
		int v3[3] = { -1, -1, -1 };
	}triangle;
	typedef struct _square {
		int v1[3] = { -1, -1, -1 }; //첫 번째 vertex의 pos/tex/norm index. 없으면 -1
		int v2[3] = { -1, -1, -1 };
		int v3[3] = { -1, -1, -1 };
		int v4[3] = { -1, -1, -1 };
	}square;
	std::vector<glm::vec3> Vertices, Normals, Textures;
	std::vector<triangle> TriagnleIndexes;
	glm::vec3 t; //temp

				 // 실제로 읽는 부분
	int n, linenum = 0;
	while (!file.eof()) {
		linenum++;
		getline(file, line);
		if (line.length() > 2) // line에 뭔가 있었을 때
			switch (line[0]) {
			case 'm': // material
				break;
			case 'v': // vertex

				switch (line[1]) {
				case ' ': // position 
					n = sscanf(line.c_str(), "v %f %f %f", &t.x, &t.y, &t.z);
					if (n == 3) Vertices.push_back(t);
					else printf("fail at line %d\n", linenum);
					break;
				case 't': //texture ok
					n = sscanf(line.c_str(), "vt %f %f %f", &t.x, &t.y, &t.z);
					if (n == 3) Textures.push_back(t);
					else if (n == 2) { t.z = 0.f; Textures.push_back(t); }
					else printf("fail at line %d\n", linenum);
					break;
				case 'n': // normal ok, not unit vec
					n = sscanf(line.c_str(), "vt %f %f %f", &t.x, &t.y, &t.z);
					if (n == 3) Normals.push_back(t);
					else printf("fail at line %d\n", linenum);
					break;
					//vp?
				default:
					printf("fail at line %d\n", linenum);
					break;
				}
				break;

			case 'f': // tri, sqr만 다룰 것.
					  // 한 vertex만 스캔.
				int t[3] = { -1, -1, -1 };
				n = sscanf(line.c_str(), "f %d/%d/%d", &t[0], &t[1], &t[2]);

				switch (n) {
					/*case 1: // %f, %f//%f 두가지 경우.
					n = sscanf(line.c_str(), "f %f//%f", &t.x, &t.y, &t.z, &t.w);
					if(n==3) */
				case 2:
					square ts;
					n = sscanf(line.c_str(), "f %d/%d %d/%d %d/%d %d/%d",
						&ts.v1[0], &ts.v1[1], &ts.v2[0], &ts.v2[1], &ts.v3[0], &ts.v3[1], &ts.v4[0], &ts.v4[1]);
					if (n == 8) {
						triangle t1;
						t1.v1[0] = ts.v1[0] - 1; t1.v1[1] = ts.v1[1] - 1;
						t1.v2[0] = ts.v2[0] - 1; t1.v2[1] = ts.v2[1] - 1;
						t1.v3[0] = ts.v3[0] - 1; t1.v3[1] = ts.v3[1] - 1;
						TriagnleIndexes.push_back(t1);
						triangle t2;
						t2.v1[0] = t1.v1[0]; t2.v1[1] = t1.v1[1];
						t2.v2[0] = t1.v3[0]; t2.v2[1] = t1.v3[1];
						t2.v3[0] = ts.v4[0] - 1; t2.v3[1] = ts.v4[1] - 1;
						TriagnleIndexes.push_back(t2);
					}
					else if (n == 6) {
						triangle t1;
						t1.v1[0] = ts.v1[0] - 1; t1.v1[1] = ts.v1[1] - 1;
						t1.v2[0] = ts.v2[0] - 1; t1.v2[1] = ts.v2[1] - 1;
						t1.v3[0] = ts.v3[0] - 1; t1.v3[1] = ts.v3[1] - 1;
						TriagnleIndexes.push_back(t1);
					}
				}
				break;

				//default:
				//break;
			}
	}
	printf("v, vt, vn : %d, %d, %d", Vertices.size(), Textures.size(), Normals.size());


	//make vertex list, index list;
	for (int i = 0; i < TriagnleIndexes.size(); i++) {
		//vertex list에 position 정보 대입
		glm::vec3 v1 = Vertices[TriagnleIndexes[i].v1[0]];
		glm::vec3 v2 = Vertices[TriagnleIndexes[i].v2[0]];
		glm::vec3 v3 = Vertices[TriagnleIndexes[i].v3[0]];
		vertex_list.push_back(v1);
		vertex_list.push_back(v2);
		vertex_list.push_back(v3);

		//texture list에 tex좌표 대입
		texture_list.push_back(Textures[TriagnleIndexes[i].v1[1]]);
		texture_list.push_back(Textures[TriagnleIndexes[i].v2[1]]);
		texture_list.push_back(Textures[TriagnleIndexes[i].v3[1]]);

		//caluarate normal
		glm::vec3 vnorm = normalize(cross(v2 - v1, v3 - v1));
		normal_list.push_back(vnorm);
		normal_list.push_back(vnorm);
		normal_list.push_back(vnorm);
	}
	printf("vl, tl, nl : %d, %d, %d", vertex_list.size(), texture_list.size(), normal_list.size());


}
void Model::Bind_VBO(const VVec3 vertex_list, const VVec3 texture_list, const VVec3 normal_list) {

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertex_list.size(), &vertex_list[0][0], GL_STATIC_DRAW);
	glVertexAttribPointer(vbo_count, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(vbo_count++);

	
	glGenBuffers(1, &texture_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, texture_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*texture_list.size(), &texture_list[0][0], GL_STATIC_DRAW);
	glVertexAttribPointer(vbo_count, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(vbo_count++);
	

	glGenBuffers(1, &normal_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*normal_list.size(), &normal_list[0][0], GL_STATIC_DRAW);
	glVertexAttribPointer(vbo_count, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(vbo_count++);

}
void Model::Bind_Texture(const char* texpath) {
	TEX.myLoadBMP24(texpath); //데이터읽는 부분과 bind 부분 분리할 것.

}

