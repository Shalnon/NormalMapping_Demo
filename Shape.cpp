#include "stdafx.h"

using namespace std;
Shape::Shape(int vcount)
{
	verts = new glm::vec4[vcount];
	normals = new glm::vec4[vcount];
	UVs = new glm::vec2[vcount];
	tangents = new glm::vec4[vcount];
	bitangents = new glm::vec4[vcount];
	tr = Transform();
}

Shape::Shape(string shape_file_name)
{

	tr = Transform();

	ifstream ifs;
	char buff[512];
	memset(buff,'\0',512);
	sprintf(buff,"%s\\%s",DATA_PATH,shape_file_name.c_str());
	ifs.open(buff);
	if(!ifs.is_open()){printf("%s did not open\n",buff); return;}
	
	char c;
	ifs.ignore(256,'=');
	ifs>>vert_count;

	verts = new glm::vec4[vert_count];
	normals = new glm::vec4[vert_count];
	UVs = new glm::vec2[vert_count];
	tangents = new glm::vec4[vert_count];
	bitangents = new glm::vec4[vert_count];

	ifs.ignore(256,'{');
	float x,y,z;
	for(int i=0; i<vert_count; i++)
	{
		
		ifs>>c>>x>>c>>y>>c>>z;
		ifs>>c>>c;
		verts[i] = glm::vec4(x,y,z,1.0);
	}
	ifs.ignore(256,'{');
	for(int i=0; i<vert_count; i++)
	{
		ifs>>c>>x>>c>>y>>c>>z;
		ifs>>c>>c;
		normals[i] = glm::vec4(x,y,z,1.0);
	}
	ifs.ignore(256,'{');
	for(int i=0; i<vert_count; i++)
	{
		ifs>>c>>x>>c>>y;
		ifs>>c>>c;
		UVs[i]=glm::vec2(x,y);
	}
	ifs.ignore(256,'{');
	for(int i=0; i<vert_count; i++)
	{
		ifs>>c>>x>>c>>y>>c>>z;
		ifs>>c>>c;
		tangents[i] = glm::vec4(x,y,z,1.0);
	}
	ifs.ignore(256,'{');
	for(int i=0; i<vert_count; i++)
	{
		ifs>>c>>x>>c>>y>>c>>z;
		ifs>>c>>c;
		bitangents[i] = glm::vec4(x,y,z,1.0);
	}
	ifs.ignore(256,'{');

	float tx,ty,tz,rx,ry,rz,sx,sy,sz;
	
	ifs>>tx>>c>>ty>>c>>tz;
	ifs.ignore(256,'{');
	ifs>>rx>>c>>ry>>c>>rz;
	ifs.ignore(256,'{');
	ifs>>sx>>c>>sy>>c>>sz;

	float rtod = 57.2958;
	tr.set_location(tx,ty,tz);
	tr.set_rotation(rx*rtod,ry*rtod,rz*rtod);
	tr.set_scale(sx,sy,sz);
	tr.update();

	

}

glm::mat4 Shape::get_Model_Matrix()
{
	glm::mat4 model_matrix = tr.rotationM * tr.translationM * tr.scaleM;

	return model_matrix;
}
