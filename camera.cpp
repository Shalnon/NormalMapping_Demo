#include "stdafx.h"

/*
class Camera
{
public:
	Transform tr;
	glm::mat4 view_matrix;
	glm::mat4 projection_matrix;
	Camera();


};
*/

Camera::Camera()
{
	tr = Transform();
	//45.0f/57.2957795f
	projection_matrix = glm::perspectiveFov(25.0f, WINDOW_WIDTH,WINDOW_HEIGHT, 1.0f, 100.0f);

}

glm::mat4 Camera::get_view_matrix()
{
	return (tr.rotationM * tr.translationM * tr.scaleM);
}