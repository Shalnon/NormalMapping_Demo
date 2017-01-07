#include "stdafx.h"


class Light
{
public:
	glm::vec3 location;
	Transform tr;
	Light(float x, float y, float z)
	{
		tr = Transform();
		tr.translate(x,y,z);
	}
};