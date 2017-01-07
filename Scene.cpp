#include "stdafx.h"

using namespace std;
Scene::Scene(int shape_count)
{
	num_shapes = shape_count;
	tr = Transform();
	shapes =(Shape**) malloc(sizeof(Shape*)*num_shapes);
	vert_count = 0;
}