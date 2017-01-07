// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include "GL/freeglut.h"
#include <GL/gl.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp".
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext.hpp"


#include "ShaderTools.h"
#include "Transform.h"
#include "Light.h"
#include "camera.h"
#include "Shape.h"
#include "keyboard.h"
#include "mouse.h"

#include "Loader.h"


#define PRINT_SHADER_DEBUG_INFO true
#define PRINT_DEBUG_INFO true
#define WINDOW_WIDTH 800.0F
#define WINDOW_HEIGHT 600.0F
#define DATA_PATH "C:\\Users\\Sean\\Documents\\Visual Studio 2012\\Projects\\GL_basic\\GL_basic\\assets"
#define FRAG_SHADER_LOCATION "C:\\Users\\Sean\\Documents\\Visual Studio 2012\\Projects\\GL_basic\\GL_basic\\shaders\\frag.txt"
#define VERTEX_SHADER_LOCATION "C:\\Users\\Sean\\Documents\\Visual Studio 2012\\Projects\\GL_basic\\GL_basic\\shaders\\vertex.txt"
extern glm::mat4 IDENTITY;
float X(float pixel_loc);
float Y(float pixel_loc); 

// TODO: reference additional headers your program requires here
