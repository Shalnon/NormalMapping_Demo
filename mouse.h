

#include "stdafx.h"

class Mouse_Handler
{
public:
	int x;
	int y;
	float delta_x;
	float delta_y;
	Mouse_Handler(int x_in, int y_in);
	Mouse_Handler();
	void motion_callback(int x, int y);
	void passive_motion_callback(int x, int y);
	void button_callback(int button, int state, int x, int y);
	void update();
private:
	int x_res;
	int y_res;
	int middle_x;
	int middle_y;

};


extern Mouse_Handler Mouse;

void motion_callback_proxy(int x, int y);
void passive_motion_callback_proxy(int x, int y);
void button_callback_proxy(int button, int state, int x, int y);