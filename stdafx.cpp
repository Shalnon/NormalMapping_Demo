// stdafx.cpp : source file that includes just the standard includes
// GL_basic.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

glm::mat4 IDENTITY = glm::mat4(1.0,0.0,0.0,0.0,
					 0.0,1.0,0.0,0.0,
					 0.0,0.0,1.0,0.0,
					 0.0,0.0,0.0,1.0);
float X(float pixel_loc)
{
	return (-1.0f + ((2.0f/WINDOW_WIDTH)*pixel_loc));
}
float Y(float pixel_loc)
{
	return (-1.0f + ((2.0f/WINDOW_HEIGHT)*pixel_loc));
}