

#include "stdafx.h"



extern unsigned char* image;
extern unsigned char* image2;

class Scene
{	
public:
	GLuint VBO_ID;
	GLuint VAO_ID;
	int vert_count;
	Transform tr;
	Shape** shapes;
	int num_shapes;

	void render();
	Scene(int shape_count);
	void update();
	void BufferData(GLuint shader_program);
};
extern Scene* scene;
extern int* shape_count;
extern unsigned char* image;

void load_data_new(char* shape_names_file);


GLint loadTexture(const char * imagepath,unsigned char **dd);
void prepTexture(unsigned char *d,char* fname, GLuint *texID,int w, int h);

//void make_shape(shape** s,float * verts,float x, float y);