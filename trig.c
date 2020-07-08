#include "trig.h"

#define C0 0.22653292f
#define C1 1.00085104f
#define C2 2.09881212f
#define K  0.63661977f

int m(float x) {
	return 1 - 2*mod(floor(0.5f*x), 2.0f);
}

float l(float x) {
	return min(mod(x, 2), mod(-x, 2));
}

//forward
float cos(float x) {
	x *= K;
	float p = l(x);
	return m(x + 1)*C0*(C1 + p)*(C1 - p)*(C2 + p)*(C2 - p);
}

float sin(float x) {
	x *= K;
	float p = l(x + 1);
	return m(x)*C0*(C1 + p)*(C1 - p)*(C2 + p)*(C2 - p);
}

float tan(float x) {
	return sin(x)/cos(x);
}

//inverse
float acos(float x) {

}

float asin(float x) {

}

float atan(float x) {

}

float atan2(float x, float y) {

}

//forward hyperbolic
float cosh(float x) {
	float y = exp(x);
	return 0.5f*(1.0f/y + y);
}

float sinh(float x) {
	float y = exp(x);
	return 0.5f*(y - 1.0f/y);
}

float tanh(float x) {
	float y = exp(2.0f*x);
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
	return 0.5f*(log(1 + x) - log(1 - x));
}