
#include "stdafx.h"
using namespace std;
	int wkey=0;
	int qkey=0;
	int ekey=0;
	int akey=0;
	int skey=0;
	int dkey=0;
	int kkey=0;
	int lkey=0;
	int cKey=0;
	int vkey=0;
	int jkey=0;
	int nkey=0;
	int mkey=0;
	int okey=0;
	int pkey=0; 
	int spaceKey=0;
	int leftkey=0;
	int rightkey=0;
	int dirKeyDown=0;
	int hkey=0;
	int gkey=0;
	int upkey=0;
	int downkey=0;
	int key_1=0;
	int key_2=0;
	int key_3=0;
	int key_4=0;
	int key_5=0;
	int key_6=0;
	int key_7=0;
	int key_8=0;
	int key_9=0;
	int key_0=0;
void KeyPressed(unsigned char Key,int x, int y) 
{

	if(Key=='w') wkey=1;
	if(Key=='n') nkey=1;
	if(Key=='m') mkey=1;
	if(Key=='o') okey=1;
	if(Key=='p') pkey=1;
	if(Key=='v') vkey=1; 
	if(Key=='j') jkey=1;
	if(Key=='e') ekey=1;
	if(Key=='q') qkey=1;
	if(Key== 's'){ skey=1;}
	if(Key== 'a') akey=1;
	if(Key== 'd') dkey=1; 
    	if (Key== 27) exit(0); 
    	if (Key== 32) spaceKey=1; 
    	if(Key=='c') cKey=1;
    	if(Key== 'g') gkey=1;
    	if(Key== 'h') hkey=1;
	if(Key== 'k') kkey=1;
	if(Key== 'l') lkey=1;

	if(Key=='1') key_1=1;
	if(Key=='2') key_2=1;
	if(Key=='3') key_3=1;
	if(Key=='4') key_4=1;
	if(Key=='5') key_5=1;
	if(Key=='6') key_6=1;
	if(Key=='7') key_7=1;
	if(Key=='8') key_8=1;
	if(Key=='9') key_9=1;
	if(Key=='0') key_0=1;
			
		
}
void SpKeyPressed(int Key,int x, int y)
{	
	//printf("SpKeyPressed, key = %c\n", Key);
	if(Key==GLUT_KEY_LEFT) leftkey=1;
    if(Key==GLUT_KEY_RIGHT) rightkey=1;
    if(Key==GLUT_KEY_UP) upkey=1;
    if(Key==GLUT_KEY_DOWN) downkey=1;
}
void keyUp(unsigned char Key,int x, int y)
{
	
	if(Key=='w') wkey=0;
	if(Key=='j') jkey=0;
	if(Key=='v') vkey=0;
	if(Key=='e') ekey=0;
	if(Key=='q') qkey=0;
	if(Key== 's')skey=0;
	if(Key== 'a')akey=0;
	if(Key== 'd')dkey=0;
	if(Key== 'g')gkey=0;
	if(Key== 'h')hkey=0;
    if(Key=='c') cKey=0;
    if(Key== 32)spaceKey=0;

	if(Key=='n') nkey=0;
	if(Key=='m') mkey=0;
	if(Key=='o') okey=0;
	if(Key=='p') pkey=0;

	if(Key=='1') key_1=0;
	if(Key=='2') key_2=0;
	if(Key=='3') key_3=0;
	if(Key=='4') key_4=0;
	if(Key=='5') key_5=0;
	if(Key=='6') key_6=0;
	if(Key=='7') key_7=0;
	if(Key=='8') key_8=0;
	if(Key=='9') key_9=0;
	if(Key=='0') key_0=0;
    if(Key== 'k') kkey=0;
	if(Key== 'l') lkey=0;
		
}
void SpKeyUp(int Key,int x, int y)
{
	//printf("spKeyUp");
	if(Key==GLUT_KEY_LEFT) leftkey=0;
    if(Key==GLUT_KEY_RIGHT) rightkey=0;
    if(Key==GLUT_KEY_UP) upkey=0;
    if(Key==GLUT_KEY_DOWN) downkey=0;
}
