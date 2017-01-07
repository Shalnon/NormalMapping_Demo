// GL_basic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
GLint Width =(GLint)WINDOW_WIDTH,Height =(GLint)WINDOW_HEIGHT; 
GLuint normal_map_id;
GLuint brick_normal_map_id;
GLuint brick_diffuse_id;
GLuint piller_diffuse_id;
Camera camera;
Shader_set shaders;
Light* light;
void IdleFunction(void)
{

	glutPostRedisplay();
}

void controls()
{
	//cout<<"conrtols!\n"<<endl;
	if(skey)
	{
		camera.tr.translate('z',-0.05);
	}
	if(wkey){camera.tr.translate('z',0.05);}
	if(akey){camera.tr.translate('x',0.05);}
	if(dkey){camera.tr.translate('x',-0.05);}
	if(leftkey){light->tr.translate('x',-0.05);}
	if(rightkey)
	{
		light->tr.translate('x',0.05);
		glm::vec4 l = light->tr.translationM*glm::vec4(0.0,0.0,0.0,1.0);
		printf("light %f,%f,%f\n",l.x,l.y,l.z);
	}
	if(ekey){camera.tr.translate('y',0.05);}
	if(qkey){camera.tr.translate('y',-0.05);}
}

void init()
{
	const GLubyte* version_string;
	version_string = glGetString(GL_VERSION);
	fprintf(stderr, "OpenGL Version %s\n", version_string);
	glClearColor(1.0,1.0,1.0,1.0);
	glutIdleFunc(IdleFunction);
	glutKeyboardFunc(KeyPressed);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(SpKeyPressed);
	glutSpecialUpFunc(SpKeyUp);
	glutPassiveMotionFunc(motion_callback_proxy);
	glutMotionFunc(passive_motion_callback_proxy);
	glutMouseFunc(button_callback_proxy);
	//gluOrtho2D(0.0, 200, 0.0, 150);
}
void render()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
	GLuint textures[2] = {brick_normal_map_id,normal_map_id};
	GLuint diffuse_maps[2] = {brick_diffuse_id,piller_diffuse_id};
	glBindVertexArray(scene->VAO_ID);	
	//getting the location in the shader of all uniform variables
	GLint normal_map_uniform = glGetUniformLocation(shaders.shaderProgramID,"normal_map");
	GLint light_uniform = glGetUniformLocation(shaders.shaderProgramID,"Light_Position");
	GLint brick_diffuse_sampler = glGetUniformLocation(shaders.shaderProgramID,"diffuse_map");
	
	//setting the projection and View matrix uniform variables in the shader
	set_4x4f_matrix("Projection",camera.projection_matrix,shaders.shaderProgramID);
	set_4x4f_matrix("View",camera.get_view_matrix(),shaders.shaderProgramID);
	glm::vec4 l = glm::vec4(0.0,0.0,0.0,1.0)*light->tr.translationM;
	//setting the light location uniform
	glProgramUniform3f(shaders.shaderProgramID,light_uniform,l.x,l.y,l.z);
	for(int i=0; i<scene->num_shapes; i++)
	{
		glm::mat4 mm = scene->shapes[i]->get_Model_Matrix(); //get the model matrix for this mesh
		glActiveTexture(GL_TEXTURE0+textures[i]);//setting the active texture slot 
		glBindTexture(GL_TEXTURE_2D,textures[i]);//bind textures[i] to GL_TEXTURE_2D in the active texture slot
		glProgramUniform1i(shaders.shaderProgramID,normal_map_uniform,textures[i]);//pass the normal map texture id to the shader sampler uniform. 

		glActiveTexture(GL_TEXTURE0+diffuse_maps[i]);
		glBindTexture(GL_TEXTURE_2D,diffuse_maps[i]);
		glProgramUniform1i(shaders.shaderProgramID,brick_diffuse_sampler,diffuse_maps[i]);//pass the color texture id to the shader sampler uniform
		set_4x4f_matrix("Model",mm,shaders.shaderProgramID);//set the model matrix in the shader
		glDrawArrays(GL_TRIANGLES,scene->shapes[i]->buff_position,scene->shapes[i]->vert_count);//draw a mesh
	}


	glutSwapBuffers();


}
void mloop()
{
	controls();
	Mouse.update();
	for(int i=0; i<scene->num_shapes; i++)
	{
		scene->shapes[i]->tr.update();
	}
	camera.tr.update();
	light->tr.update();
	render();
}

void winReshape(GLint new_width, GLint new_height)
{
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

} 
void button_callback_proxy(int button, int state, int x, int y)
{
	Mouse.button_callback(button,state,x,y);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH|GLUT_ALPHA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(Width,Height);
	glutCreateWindow("CMSC405 Sean Halnon HW3");
	init();
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_TEXTURE_2D);

	glutDisplayFunc(mloop);
	glutReshapeFunc(winReshape);

	glewInit();

	shaders = Shader_set();
	shaders.ShaderInit(VERTEX_SHADER_LOCATION,FRAG_SHADER_LOCATION);
	glUseProgram(shaders.shaderProgramID);

	//bullets.reserve(100);
	char buff[512];
	memset(buff,'\0',512);
	sprintf(buff,"%s/Shapes.txt",DATA_PATH);

	load_data_new("C:\\Users\\Sean\\Documents\\Visual Studio 2012\\Projects\\GL_basic\\GL_basic\\assets\\Shapes.txt");
	scene->BufferData(shaders.shaderProgramID);	             
	
	camera = Camera();
	scene->shapes[0]->tr.rotate('y',180);
	Mouse = Mouse_Handler(0,0);


		
	light = new Light(1.0,0.5,0.0);


	cout<<glm::to_string(scene->shapes[0]->get_Model_Matrix())<<endl;
//	square1->rotate(00,0,30);
//	square1->translate(0.7,0.7);
	memset(buff,'\0',512);
	sprintf(buff,"%s\\piller.bmp",DATA_PATH);
	prepTexture(image,buff,&normal_map_id,2048,2048);

	memset(buff,'\0',512);
	sprintf(buff,"%s\\brick_normal2.bmp",DATA_PATH);
	prepTexture(image2,buff,&brick_normal_map_id,400,400);


	memset(buff,'\0',512);
	sprintf(buff,"%s\\brick_diffuse.bmp",DATA_PATH);
	prepTexture(image2,buff,&brick_diffuse_id,400,400);

			memset(buff,'\0',512);
	sprintf(buff,"%s\\piller_diffuse.bmp",DATA_PATH);
	prepTexture(image2,buff,&piller_diffuse_id,256,256);
	glutMainLoop();

}

