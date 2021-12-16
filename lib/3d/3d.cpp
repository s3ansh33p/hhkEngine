/**
 * @file 3d.cpp
 * @author SnailMath
 * @brief 3d library
 * @version 1.1
 * @date 2021-12-16
 */

#include "../../calc.hpp"
#include "3d.hpp"

extern void _sdivisi3_i4i(int a, int b);

int camx = 0;
int camy = -100;
int camz = 0;
int cama = 0; //Alpha (left/right)
int camb = 0; //Beta  (up/down)

uint32_t uintsqrt(uint32_t x){
	uint32_t res = 0;
	uint32_t one = 0x40000000; //The highest power of 4
	while(one>x)
		one>>=2;
	while(one!=0){
		if(x>=res+one){
			x=x-(res+one);
			res=res+2*one;
		}
		res>>=1;
		one>>=2;
	}
	return res;
}

int to3dx(int x, int y, int z){
	(void)z;
	int dx = x-camx;
	int dy = y-camy;
	// int dz = z-camz;
	int newx = intern_atan(dx,dy)-cama;
	while(newx<-1024) newx+=2048;
	while(newx>=1024) newx-=2048;
	//now newx is between -1024 and 1023.
	return (width/2)+newx; //now it is between -255 and +256
}
int to3dy(int x, int y, int z){
	int dx = x-camx;
	int dy = y-camy;
	int dz = z-camz;
	int d  = uintsqrt((dx*dx)+(dy*dy));
	int newy = intern_atan(dz,d)-camb;
	while(newy<-1024) newy+=2048;
	while(newy>=1024) newy-=2048;
	//now newy is between -1024 and 1023.
	return (height/2)-newy; //now it is between -255 and +256
}
#define ATANS 256 //Size of the atan table
int intern_atan(int dx, int dy){
	if (dx==0 && dy>0)
		return 0;
	else if(dx>0 && dy>dx)
		return arctan[(uint8_t)(dx*ATANS/dy)];
	else if(dx>0 && dy==dx)
		return 256;
	else if(dx>0 && dy>0)
		return 512-arctan[(uint8_t)(dy*ATANS/dx)];
	else if(dx>0 && dy==0)
		return 512;
	else if(dx>0 && -dy<dx)
		return 512+arctan[(uint8_t)((-dy)*ATANS/dx)];
	else if(dx>0 && -dy==dx)
		return 768;
	else if(dx>0)
		return 1024-arctan[(uint8_t)(dx*ATANS/(-dy))];
	else if(dx==0 && dy<0)
		return 1024;
	else if(dx<0 && -dy>-dx)
		return 1024+arctan[(uint8_t)((-dx)*ATANS/(-dy))];
	else if(dx<0 && -dy==-dx)
		return 1280;
	else if(dx<0 && dy<0)
		return 1536-arctan[(uint8_t)((-dy)*ATANS/(-dx))];
	else if(dx<0 && dy==0)
		return 1536;
	else if(dx<0 && dy<-dx)
		return 1536+arctan[(uint8_t)((dy)*ATANS/(-dx))];
	else if(dx<0 && dy==-dx)
		return 1792;
	else
		return 2048-arctan[(uint8_t)((-dx)*ATANS/(dy))];
}


void cube(int x, int y, int z, int w, uint16_t color){
	line(x  ,y  ,z  ,x+w,y  ,z  ,color);
	line(x+w,y  ,z  ,x+w,y+w,z  ,color);
	line(x+w,y+w,z  ,x  ,y+w,z  ,color);
	line(x  ,y+w,z  ,x  ,y  ,z  ,color);
	
	line(x  ,y  ,z+w,x+w,y  ,z+w,color);
	line(x+w,y  ,z+w,x+w,y+w,z+w,color);
	line(x+w,y+w,z+w,x  ,y+w,z+w,color);
	line(x  ,y+w,z+w,x  ,y  ,z+w,color);
	
	line(x  ,y  ,z  ,x  ,y  ,z+w,color);
	line(x+w,y  ,z  ,x+w,y  ,z+w,color);
	line(x+w,y+w,z  ,x+w,y+w,z+w,color);
	line(x  ,y+w,z  ,x  ,y+w,z+w,color);

}

void line(int x1, int y1, int z1, int x2, int y2, int z2, uint16_t color){
	line( to3dx(x1,y1,z1),
		  to3dy(x1,y1,z1),
		  to3dx(x2,y2,z2),
		  to3dy(x2,y2,z2),
		  color);
}

void triangle(	int x1, int y1, int z1,
		int x2, int y2, int z2,
		int x3, int y3, int z3,
		uint16_t c1, uint16_t c2 ){
	triangle( to3dx(x1,y1,z1),
		  to3dy(x1,y1,z1),
		  to3dx(x2,y2,z2),
		  to3dy(x2,y2,z2),
		  to3dx(x3,y3,z3),
		  to3dy(x3,y3,z3),
		  c1,c2);
}

//arctan[] contains the values of the result of the function f(x)=ARCTAN(x/ATANS)/PI*1024
uint8_t arctan[] = {
  0,  1,  3,  4,  5,  6,  8,  9, 10, 11, 13, 14, 15, 17, 18, 19,
 20, 22, 23, 24, 25, 27, 28, 29, 30, 32, 33, 34, 36, 37, 38, 39,
 41, 42, 43, 44, 46, 47, 48, 49, 51, 52, 53, 54, 55, 57, 58, 59,
 60, 62, 63, 64, 65, 67, 68, 69, 70, 71, 73, 74, 75, 76, 77, 79,
 80, 81, 82, 83, 85, 86, 87, 88, 89, 91, 92, 93, 94, 95, 96, 98,
 99,100,101,102,103,104,106,107,108,109,110,111,112,114,115,116,
117,118,119,120,121,122,124,125,126,127,128,129,130,131,132,133,
134,135,137,138,139,140,141,142,143,144,145,146,147,148,149,150,
151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,
167,168,169,170,171,172,173,174,175,176,177,177,178,179,180,181,
182,183,184,185,186,187,188,188,189,190,191,192,193,194,195,195,
196,197,198,199,200,201,201,202,203,204,205,206,206,207,208,209,
210,211,211,212,213,214,215,215,216,217,218,219,219,220,221,222,
222,223,224,225,225,226,227,228,228,229,230,231,231,232,233,234,
234,235,236,236,237,238,239,239,240,241,241,242,243,243,244,245,
245,246,247,248,248,249,250,250,251,251,252,253,253,254,255,255};

