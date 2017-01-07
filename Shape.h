#include "stdafx.h"

class Shape
{
public:
	Shape(int vcount);
	int tri_count;
	int buff_position;
	int vert_count;
	char* name;
	GLfloat color[3];
	glm::vec4* verts;
	glm::vec4* normals;
	glm::vec4* tangents;
	glm::vec4* bitangents;
	glm::vec2* UVs;
	Transform tr; 
	Shape(std::string shape_file_name);
	glm::mat4 get_Model_Matrix();
}; 

