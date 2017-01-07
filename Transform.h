#include "stdafx.h"

class Transform
{
private:
	glm::vec4 locV;
	glm::vec4 rotV;
	glm::vec4 scaleV;
public:
	glm::mat4 translationM;
	glm::mat4 scaleM;
	glm::mat4 rotationM;
	void set_location(float x, float y, float z);
	void set_rotation(float rx, float ry, float rz);
	void set_scale(float sx, float sy, float sz);
	
	void translate(float tx, float ty, float tz);
	void translate(char axis, float dt);

	void rotate(float rx, float ry, float rz);
	void rotate(char axis, float dr);

	void scale(float sx, float sy, float sz);
	void scale(char axis, float ds);
	void update();
	Transform();

};
