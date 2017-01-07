

#include "stdafx.h"
#include <iostream>     
#include <fstream>
#include <sstream>
#include <string>
/*

typedef struct transform
{
	float translation[3];
	float scale[3];
	float rotation[3];
}transform;

typedef struct shape
{


	int tri_count;
	int* indexes;
	GLfloat* verts;
	transform t; 

}shape; 

extern shape* shapes;

void load_data(char* shape_names_file);
void load_shape(char* shape_name);
*/
Scene* scene;
int* shape_count;
unsigned char* image;
unsigned char* image2;

char* get_file(char* file_name,FILE** fp)
{
	char path[2048];
	memset(path,'\0',2048);
	sprintf(path,"%s/%s",DATA_PATH,file_name);
	*fp = fopen(path,"r");
	//printf("path=%s\n", path);
	if(fp!=NULL){fprintf(stderr,"file loaded successfully\n");}
	else{fprintf(stderr,"file loaded unsuccessfully");}
	return path;
}



void load_data_new(char* shape_names_file)
{
	int num_shapes;
	std::ifstream ifs;

	ifs.open(shape_names_file);
	printf("shapes_names_file path: %s\n",shape_names_file);
	if(!ifs.is_open()){printf("file didnt open\n"); return;}
	ifs>>num_shapes;
	scene = new Scene(num_shapes);
	for(int i=0; i<num_shapes; i++)
	{
		std::string shape_file_name;
		ifs>>shape_file_name;
		scene->shapes[i] = new Shape(shape_file_name);
		scene->shapes[i]->buff_position = scene->vert_count;
		scene->vert_count += scene->shapes[i]->vert_count;
	}
	


}

void Scene::BufferData(GLuint shader_program)
{
	int verts_in = 0; 
	int vert_floats = 14;
	int current_float = 0;
	glGenVertexArrays(1,&VAO_ID);
	glBindVertexArray(VAO_ID);

	glGenBuffers(1, &VBO_ID);
	glBindBuffer(GL_ARRAY_BUFFER,VBO_ID);


	//3 position floats, 3 normal coordinates, 2 texture coordinates

	glBufferData(GL_ARRAY_BUFFER,vert_count*vert_floats*sizeof(GLfloat),NULL,GL_STATIC_DRAW);

	void* vdata = glMapBuffer(GL_ARRAY_BUFFER,GL_READ_WRITE);

	GLfloat* vertex_data = (GLfloat*)vdata;

	

	for(int i=0; i<num_shapes; i++)
	{
		if(i<num_shapes){printf("i is less then num_shapes\n");}
		for( int n=0; n<shapes[i]->vert_count; n++)
		{
			vertex_data[current_float++] = shapes[i]->verts[n].x;
			vertex_data[current_float++] = shapes[i]->verts[n].y;
			vertex_data[current_float++] = shapes[i]->verts[n].z;
			vertex_data[current_float++] = shapes[i]->normals[n].x;
			vertex_data[current_float++] = shapes[i]->normals[n].y;
			vertex_data[current_float++] = shapes[i]->normals[n].z;
			float length = fabs(sqrt(pow(shapes[i]->normals[n].x,2.0) + pow(shapes[i]->normals[n].y,2.0) + pow(shapes[i]->normals[n].z,2.0)))-1.0 ;
			if(fabs(length) >0.1){printf("normal not normalized!!!\n");}
			vertex_data[current_float++] = shapes[i]->UVs[n].x;
			vertex_data[current_float++] = shapes[i]->UVs[n].y;
			vertex_data[current_float++] = shapes[i]->tangents[n].x;
			vertex_data[current_float++] = shapes[i]->tangents[n].y;
			vertex_data[current_float++] = shapes[i]->tangents[n].z;
			vertex_data[current_float++] = shapes[i]->bitangents[n].x;
			vertex_data[current_float++] = shapes[i]->bitangents[n].y;
			vertex_data[current_float++] = shapes[i]->bitangents[n].z;
			verts_in++;
		}
	}




	glUnmapBuffer(GL_ARRAY_BUFFER);

	GLuint pos_attrib = glGetAttribLocation(shader_program,"Vposition");
	GLuint normal_attrib = glGetAttribLocation(shader_program,"Vnormal");
	GLuint UV_attrib = glGetAttribLocation(shader_program,"UV");
	GLuint tan_attrib = glGetAttribLocation(shader_program,"Vtangent");
	GLuint bitan_attrib = glGetAttribLocation(shader_program,"Vbitangent");

	int stride = vert_floats*sizeof(GLfloat);
	glVertexAttribPointer(pos_attrib,3,GL_FLOAT,GL_FALSE,stride,0);									if(int e=glGetError())printf("\n\n--fillBuffers().%d error# %d :%s\n",__LINE__,e,gluErrorString(e));
	glVertexAttribPointer(normal_attrib,3,GL_FLOAT,GL_FALSE,stride,(void*)(sizeof(GLfloat)*3));		if(int e=glGetError())printf("\n\n--fillBuffers().%d error# %d :%s\n",__LINE__,e,gluErrorString(e));
	glVertexAttribPointer(UV_attrib,2,GL_FLOAT,GL_FALSE,stride,(void*)(sizeof(GLfloat)*6));			if(int e=glGetError())printf("\n\n--fillBuffers().%d error# %d :%s\n",__LINE__,e,gluErrorString(e));
	glVertexAttribPointer(tan_attrib,3,GL_FLOAT,GL_FALSE,stride,(void*)(sizeof(GLfloat)*8));		if(int e=glGetError())printf("\n\n--fillBuffers().%d error# %d :%s\n",__LINE__,e,gluErrorString(e));
	glVertexAttribPointer(bitan_attrib,3,GL_FLOAT,GL_FALSE,stride,(void*)(sizeof(GLfloat)*11));		if(int e=glGetError())printf("\n\n--fillBuffers().%d error# %d :%s\n",__LINE__,e,gluErrorString(e));
	  
	glEnableVertexAttribArray(pos_attrib);
	glEnableVertexAttribArray(normal_attrib);
	glEnableVertexAttribArray(UV_attrib);
	glEnableVertexAttribArray(tan_attrib);
	glEnableVertexAttribArray(bitan_attrib);

}

GLint loadTexture(const char * imagepath,unsigned char **dd)
{
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
	// Actual RGB data

	// Open the file
	FILE * file = fopen(imagepath,"rb");
	if (!file)  {
		printf("Texture could not be loaded\n"); 
		return 0;
	}
	if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
    	printf("Not a correct BMP file\n");
    	return false;
	}
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);
	printf("width=%d,height=%d\n",width,height);
	if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos==0)      dataPos=54; 

	// Create a buffer
	*dd =(unsigned char*) malloc(sizeof(unsigned char)*imageSize);
 
	
	fread(*dd,1,imageSize,file);
 	printf("Texture loaded into memory\n");
	
	fclose(file);
	return true;
}

void prepTexture(unsigned char *d,char* fname, GLuint *texID,int w, int h)
{

	glGenTextures(1,texID);
	printf("texid=%u\n",*texID);
	glActiveTexture(GL_TEXTURE0 + *texID);
	glBindTexture(GL_TEXTURE_2D, *texID);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, *texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	loadTexture(fname,&d);
	

	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, d);
}

