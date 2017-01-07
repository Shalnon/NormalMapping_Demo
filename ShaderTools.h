
#include "stdafx.h"

using namespace std;
class Shader_set
{

public:
	GLchar *VertshaderSource;
	GLchar *FragshaderSource;
	GLuint vertexShaderID, fragmentShaderID,shaderProgramID,vSize,fSize;
	
	
	GLuint createVertexShader(GLchar** vsource,char* Vname);
	GLuint createFragmentShader(GLchar** fsource,char* fName);
	GLuint createShaderProgram (char* Vname, char* Fname);
	void getShader(char* shaderName,GLchar **fsource,GLuint *sSize);
	void ShaderInit(char* vName,char* fName);
	bool compiledStatus(GLint shaderID,char* Vname,char* Fname);
};
void set_1i_Uniform(char *uName,GLint value,GLuint shaderProgramID);
void set_1f_Uniform(char *uName,GLfloat value,GLuint shaderProgramID);
void set_1ui_Uniform(char *uName,GLuint value,GLuint shaderProgramID);
void set_2f_Uniform(char *uName,GLfloat value[],GLuint shaderProgramID);
void set_3f_Uniform(char *uName,GLfloat value[],GLuint shaderProgramID);
void set_4f_Uniform(char *uName,GLfloat value[],GLuint shaderProgramID);
void set_4x4f_matrix(char *uName,glm::mat4 matrix,GLuint spid);
void set_2i_Uniform(char *uName,GLint *value,GLuint shaderProgramID);

