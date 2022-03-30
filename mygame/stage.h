#pragma once

#define GRID (sHei/12) //grid size
#define STEP (GRID/2)
#define gX (mX -(mX%GRID) +STEP)
#define gY (mY -(mY%GRID) +STEP)
#define WT 300  //speed

/* stage function prototype */
struct krug {
	int x;
	int y;
	unsigned int col;
};

struct magnet {
	int x;
	int y;
	int z;
	int m = 0;
};


extern struct krug maru;
extern struct magnet p1, p2, m1, m2, m3;

extern int bHandle, cHandle, gHandle, clHandle, cl2Handle;


int attrR( krug maru, magnet m );
int attrL( krug maru, magnet m );
int attrU( krug maru, magnet m );
int attrD( krug maru, magnet m );
