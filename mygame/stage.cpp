/* stage common functions */
#include "mode.h"
#include "stage.h"

int bHandle, cHandle, gHandle, clHandle, cl2Handle;
struct krug maru;
struct magnet p1, p2, m1, m2, m3;



int attrR( krug maru, magnet m ) {
	if ( m.z == 1 ) {
		if ( maru.y == m.y && maru.x <= ( m.x - STEP ) ) {
			return 1;
		} else return 0;
	}
	if ( m.z == -1 ) {
		if ( maru.y == m.y && maru.x >= ( m.x ) ) {
			return 1;
		} else return 0;
	}
	return 0;
}
int attrL( krug maru, magnet m ) {
	if ( m.z == 1 ) {
		if ( maru.y == m.y && maru.x >= ( m.x + STEP ) ) {
			return 1;
		} else return 0;
	}
	if ( m.z == -1 ) {
		if ( maru.y == m.y && maru.x <= ( m.x ) ) {
			return 1;
		} else return 0;
	}
	return 0;
}
int attrU( krug maru, magnet m ) {
	if ( m.z == 1 ) {
		if ( maru.x == m.x && maru.y >= ( m.y + STEP ) ) {
			return 1;
		} else return 0;
	}
	if ( m.z == -1 ) {
		if ( maru.x == m.x && maru.y <= ( m.y ) ) {
			return 1;
		} else return 0;
	}
	return 0;
}
int attrD( krug maru, magnet m ) {
	if ( m.z == 1 ) {
		if ( maru.x == m.x && maru.y <= ( m.y - STEP ) ) {
			return 1;
		} else return 0;
	}
	if ( m.z == -1 ) {
		if ( maru.x == m.x && maru.y >= ( m.y ) ) {
			return 1;
		} else return 0;
	}
	return 0;
}

