#include "stdafx.h"


/*
class Transform
{
private:
	float loc[3];
	float rot[3];
	float scale[3];
public:
	glm::mat4 translation;
	glm::mat4 scale;
	glm::mat4 rotation;
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
*/


Transform::Transform()
{
	locV = glm::vec4(0.0,0.0,0.0,1.0);
	rotV = glm::vec4(0.0,0.0,0.0,1.0);
	scaleV = glm::vec4(1.0,1.0,1.0,1.0);


	translationM = IDENTITY;
	rotationM = IDENTITY;
	scaleM = IDENTITY;
}

void Transform::set_location(float x, float y, float z)
{
	locV = glm::vec4(x,y,z,1.0);
}
void Transform::set_rotation(float x, float y, float z)
{
	rotV = glm::vec4(x,y,z,1.0);
}
void Transform::set_scale(float x, float y, float z)
{
	scaleV = glm::vec4(x,y,z,1.0);
}
void Transform::translate(float tx, float ty, float tz)
{
	locV = locV + glm::vec4(tx,ty,tz,0.0);
}
void Transform::rotate(float rx, float ry, float rz)
{
	rotV = rotV + glm::vec4(rx,ry,rz,0.0);
}
void Transform::scale(float sx, float sy, float sz)
{
	scaleV = scaleV + glm::vec4(sx,sy,sz,0.0);
}

void Transform::translate(char axis, float dt)
{
	switch(axis)
	{
		case 'x':
			locV.x += dt;
			return;
		case 'y':
			locV.y += dt;
			return;
		case 'z':
			locV.z += dt;
			return;
		case 'X':
			locV.x += dt;
			return;
		case 'Y':
			locV.y+=dt;
			return;
		case 'Z':
			locV.z+=dt;
		default:
			printf("invalid axis parameter. Must be 'x', 'y' or 'z'");
			return;
	}
}
void Transform::rotate(char axis, float dt)
{
	switch(axis)
	{
		case 'x':
			rotV.x += dt;
			return;
		case 'y':
			rotV.y += dt;
			return;
		case 'z':
			rotV.z += dt;
			return;
		case 'X':
			rotV.x += dt;
			return;
		case 'Y':
			rotV.y+=dt;
			return;
		case 'Z':
			rotV.z+=dt;
		default:
			printf("invalid axis parameter. Must be 'x', 'y' or 'z'");
			return;
	}
}
void Transform::scale(char axis, float dt)
{
	switch(axis)
	{
		case 'x':
			scaleV.x *= dt;
			return;
		case 'y':
			scaleV.y *= dt;
			return;
		case 'z':
			scaleV.z *= dt;
			return;
		case 'X':
			scaleV.x *= dt;
			return;
		case 'Y':
			scaleV.y*=dt;
			return;
		case 'Z':
			scaleV.z*=dt;
		default:
			printf("invalid axis parameter. Must be 'x', 'y' or 'z'");
			return;
	}
}

void Transform::update()
{

	translationM = glm::mat4(1.0,0.0,0.0,locV.x,
							 0.0,1.0,0.0,locV.y,
							 0.0,0.0,1.0,locV.z,
							 0.0,0.0,0.0,1.0);
	rotationM = IDENTITY;
	rotationM = glm::rotate(rotationM,(rotV.x),glm::vec3(1.0,0.0,0.0));
	rotationM = glm::rotate(rotationM,rotV.y,glm::vec3(0.0,1.0,0.0));
	rotationM = glm::rotate(rotationM,rotV.z,glm::vec3(0.0,0.0,1.0));

	scaleM = glm::mat4(scaleV.x,0.0,0.0,0.0,
					   0.0,scaleV.y,0.0,0.0,
					   0.0,0.0,scaleV.z,0.0,
					   0.0,0.0,0.0,1.0);

}