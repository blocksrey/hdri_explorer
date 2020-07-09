#include "trig.h"

//forward
float cos(float x) {
	x *= 0.6366198f; x += 1;
	float p = mod(x, 2) - 1; p *= p;
	return (1 - 2*mod(floor(.5f*x), 2))*0.2265329f*(1.0017028f - p)*(4.4050123f - p);
}

float sin(float x) {
	x *= 0.6366198f;
	float p = mod(x, 2) - 1; p *= p;
	return (1 - 2*mod(floor(.5f*x), 2))*0.2265329f*(1.0017028f - p)*(4.4050123f - p);
}

float tan(float x) {
	return sin(x)/cos(x);
}

//inverse
//[-1, 1]
float acos(float x) {
	return
		1.5707963f -
		1.0469419f*x +
		0.1610680f*x*x*x -
		0.5315243f*x*x*x*x*x;
}

//[-1, 1]
float asin(float x) {
	return
		1.0469419f*x -
		0.1610680f*x*x*x +
		0.5315243f*x*x*x*x*x;
}

//[-1, 1]
float atan(float x) {
	return
		0.9959826f*x -
		0.2922813f*x*x*x +
		0.0830216*x*x*x*x*x;
}

float atan2(float x, float y) {

}

//forward hyperbolic
float cosh(float x) {
	float y = exp(x);
	return .5f*(1/y + y);
}

float sinh(float x) {
	float y = exp(x);
	return .5f*(y - 1/y);
}

float tanh(float x) {
	float y = exp(2*x);
	return (y - 1)/(y + 1);
}

//inverse hyperbolic
float acosh(float x) {
	return log(x + sqrt(x*x - 1));
}

float asinh(float x) {
	return log(x + sqrt(x*x + 1));
}

float atanh(float x) {
	return .5f*(log(1 + x) - log(1 - x));
}