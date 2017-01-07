#include "stdafx.h"

using namespace std;

#define shader_version 330

void Shader_set::getShader(char* shaderName,GLchar **fsource,GLuint *sSize)
{
	
	int shaderSize; 
	ifstream fp (shaderName,  std::ifstream::in);
	fp.clear();
	fp.seekg(0, fp.end);
	shaderSize=fp.tellg();

	(*fsource)=(GLchar*) malloc((sizeof(GLchar)*shaderSize)+1);
	fp.seekg(0, fp.beg);
	fp.read((*fsource), shaderSize);

	char* lastBracket= strrchr((*fsource),'}');
	if(((*fsource)+shaderSize)>lastBracket+1&& lastBracket)
	{
		*sSize=((*fsource)+shaderSize)-lastBracket;
		memset(lastBracket+1,0,((*fsource)+shaderSize)-lastBracket);
		*(lastBracket+1)='\0';
	}
	else{
	(*fsource)[shaderSize]='\0';
	}

}
bool Shader_set::compiledStatus(GLint shaderID,char* Vname,char* Fname)
{
	GLint compiled = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
	if (compiled==true) 
	{
		if(PRINT_DEBUG_INFO)
		{
			if(int e=glGetError())
				printf("\n\n===========================compiledStatus(%s,%s) error# %d :%s\n",Vname,Fname,e,glewGetErrorString(e));
		}
		return true;
	}
	else {

		GLint logLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
		GLchar* msgBuffer = (GLchar*)malloc(sizeof(GLchar)*logLength);
		glGetShaderInfoLog(shaderID, logLength, NULL,msgBuffer);
		if(PRINT_DEBUG_INFO){printf("ERROR LOG:\n%s\n\n",msgBuffer);}
		delete (msgBuffer);
	//	if(int e=glGetError())printf("\n\n===========================compiledStatus(%s,%s) error# %d :%s\n",Vname,Fname,e,glewGetErrorString(e));
		return false;
	}
}


GLuint Shader_set::createVertexShader(GLchar** vsource,char* Vname)
{
	GLuint vShaderID = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vShaderID,1,(const GLchar**)vsource,NULL);
	//free(VertshaderSource);
	glCompileShader(vShaderID);
	 bool compiledCorrectly = compiledStatus(vShaderID,Vname," ");
	 	GLint compiled = 0;
	glGetShaderiv(vShaderID, GL_COMPILE_STATUS, &compiled); if(PRINT_SHADER_DEBUG_INFO){printf("Vertex Shader Compile status=%d\n",compiled);}
	 if (compiledCorrectly==1) {
		// if(int e=glGetError())printf("\n\n--createFragmentShader(%s) error# %d :%s\n",Vname,e,glewGetErrorString(e));
	 	return vShaderID;
	 }
	 if(PRINT_SHADER_DEBUG_INFO){printf("createVertexShader:%s did not compile\n",Vname);}
	// if(int e=glGetError())printf("\n\n--createFragmentShader(%s) error# %d :%s\n",Vname,e,glewGetErrorString(e));
	 return -1;
}
GLuint Shader_set::createFragmentShader(GLchar** fsource,char* fName) 
{
	if(PRINT_SHADER_DEBUG_INFO){printf("Inside createFragmentShader ");}
	GLuint fShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShaderID, 1, (const GLchar**)fsource,NULL);
	glCompileShader(fShaderID);
		 	GLint compiled = 0;
	glGetShaderiv(fShaderID, GL_COMPILE_STATUS, &compiled); if(PRINT_SHADER_DEBUG_INFO){printf("Frag Shader Compile status=%d\n",compiled);}
	bool compiledCorrectly = compiledStatus(fShaderID,fName," ");
	 if (compiledCorrectly==1) {
		// if(int e=glGetError())printf("\n\n--createFragmentShader(%s) error# %d :%s\n",fName,e,glewGetErrorString(e));
	 	return fShaderID;
	 }
	 if(PRINT_SHADER_DEBUG_INFO){printf("Fragment Shader:%s did not compile\n",fName);}
	//  if(int e=glGetError())printf("\n\n--createFragmentShader(%s) error# %d :%s\n",fName,e,glewGetErrorString(e));
	 return -1;
}



GLuint Shader_set::createShaderProgram (char* Vname, char* Fname) {
	GLuint shaderID = glCreateProgram();                       //       if(int e=glGetError())printf("\n\n--createShaderProgram(%s,%s).162 error# %d :%s\n",Vname,Fname,e,glewGetErrorString(e));       
	if(PRINT_SHADER_DEBUG_INFO){printf("shaderID=%d\n",shaderID); }
	glAttachShader(shaderID, vertexShaderID);                 
	glAttachShader(shaderID, fragmentShaderID);               // if(int e=glGetError())printf("\n\n--createShaderProgram(%s,%s).164 error# %d :%s\n",Vname,Fname,e,glewGetErrorString(e));
	glLinkProgram(shaderID);                                 
	GLint status=-1,vstatus=-1,logLength=-1;                  
	glGetProgramiv(shaderID,GL_LINK_STATUS,&status);          
	glGetProgramiv(shaderID,GL_VALIDATE_STATUS,&vstatus);     
	glGetProgramiv(shaderID,GL_INFO_LOG_LENGTH,&logLength);   
	if(PRINT_SHADER_DEBUG_INFO){printf("GL_LINK_STATUS=%d,GL_VALIDATE_STATUS=%d,GL_INFO_LOG_LENGTH=%d ",status,vstatus,logLength);}

	GLchar* errorlog= (GLchar*) malloc(sizeof(GLchar)*256);
	GLint logsize=0;
	glGetProgramInfoLog(shaderID,256,&logsize,errorlog);
	if(PRINT_SHADER_DEBUG_INFO){if(logsize)printf("Shader Program Error Log:\n%s\n",errorlog);}

//	if(int e=glGetError())printf("\n\n--createShaderProgram(%s,%s) error# %d :%s\n",Vname,Fname,e,glewGetErrorString(e));
	return shaderID;
}

void Shader_set::ShaderInit(char* vName, char* fName)
{
	if(PRINT_SHADER_DEBUG_INFO){printf("\n=====ShaderInit Begin====\n");}

	getShader(vName, &VertshaderSource,&vSize);                             //     if(int e=glGetError())printf("\n\n--ShaderInit(%s,%s).167 error# %d :%s\n",fName,vName,e,gluErrorString(e));
	vertexShaderID=createVertexShader(&VertshaderSource,vName);               //   if(int e=glGetError())printf("\n\n-ShaderInit(%s,%s).168 error# %d :%s\n",fName,vName,e,gluErrorString(e));

	getShader(fName,&FragshaderSource,&fSize);                               //    if(int e=glGetError())printf("\n\n-ShaderInit(%s,%s).169 error# %d :%s\n",fName,vName,e,gluErrorString(e));
	fragmentShaderID=createFragmentShader(&FragshaderSource,fName);           //   if(int e=glGetError())printf("\n\n--ShaderInit(%s,%s).70 error# %d :%s\n",fName,vName,e,gluErrorString(e));

	shaderProgramID=createShaderProgram((char*)(vName),(char*)fName);         //   if(int e=glGetError())printf("\n\n--ShaderInit(%s,%s).171 error# %d :%s\n",fName,vName,e,gluErrorString(e));
	//compiledStatus(shaderProgramID,fName,vName);
	if(PRINT_SHADER_DEBUG_INFO){printf("\n=====ShaderInit End====\n");}
}


void set_4x4f_matrix(char *uName,glm::mat4 matrix,GLuint spid)
{
	
	GLint uniformID = glGetUniformLocation(spid,uName);
	if(uniformID==-1)
	{
		// printf("Matrix Uniform %s could not be found!\n", uName);
	}
	if(int e=glGetError())
	{
	//	printf("\n\n--set_4x4f_matrix(%s,%f,%d)",uName,*value,spid);
	//	printf("error# %d :%s\n",e,gluErrorString(e));
	}
	if(shader_version > 400)
	{
		glProgramUniformMatrix4fv(spid,uniformID,1,0,glm::value_ptr(matrix));
	}
	else
	{
		glUniformMatrix4fv(uniformID,1,0,glm::value_ptr(matrix));
	}
	/*if(int e=glGetError())
		{
			printf("\n\n--set_4x4f_matrix(%s,%f,%d)",uName,*value,spid);
			printf("error# %d :%s\n",e,gluErrorString(e));
	}*/
}