#ifndef DEBUG_H
#define DEBUG_H
#include <iostream>
#include <SDL.h>
#include "Vector.h"
using namespace MATH;

class Debug {
public:
	virtual inline void debug(float string) { printf("%f \n", string); }
	virtual inline void debug(int string) { printf("%i \n", string); }
	virtual inline void debug(Vec3 string) { printf("%f %f %f \n", string.x, string.y, string.z); }
};
#endif