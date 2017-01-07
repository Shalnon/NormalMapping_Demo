

#include "stdafx.h"


class Camera
{
public:
	Transform tr;
	glm::mat4 projection_matrix;
	Camera();
	glm::mat4 get_view_matrix();

};