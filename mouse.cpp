#include "stdafx.h"

Mouse_Handler Mouse;

void Mouse_Handler::motion_callback(int x_in, int y_in)
{
	x = x_in;
	y= y_in;
}

void Mouse_Handler::passive_motion_callback(int x_in, int y_in)
{
	x = x_in;
	y = y_in;
	printf("not moving! x:%d, y:%d\n",x,y);


}
void Mouse_Handler::button_callback(int button, int state, int x, int y)
{


}
Mouse_Handler::Mouse_Handler(int x_in, int y_in)
{
	x = x_in;
	y = y_in; 
	x_res =  WINDOW_WIDTH;
	y_res = WINDOW_HEIGHT;
	middle_x = x_res/2;
	middle_y = y_res/2;
}
Mouse_Handler::Mouse_Handler()
{
	x = 0;
	y = 0; 
	x_res =  WINDOW_WIDTH;
	y_res = WINDOW_HEIGHT;
	middle_x = x_res/2;
	middle_y = y_res/2;
}
void Mouse_Handler::update()
{
	
	//delta_x = ((float)(x-middle_x))/middle_x;
//	delta_y = ((float)(y-middle_y))/middle_y;
//	printf("dx:%.4f, dy:%.4f\n",delta_x,delta_y);
	//glutWarpPointer(middle_x, middle_y);
}

void motion_callback_proxy(int x, int y)
{
	Mouse.motion_callback(x,y);//Mouse object declared in mouse.h as extern and initialized in Main.cpp
}

void passive_motion_callback_proxy(int x, int y)
{
	Mouse.passive_motion_callback(x,y);
}
