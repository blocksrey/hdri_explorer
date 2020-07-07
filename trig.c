#include "trig.h"

//forward
float cos(float x) {
	return sin(x + QT);
}

float sin(float x) {
	float b = PI - 2.0f*mod(x, PI);
	return (1 - 0.13484935f*pow(b*b, 0.87513963f))*(1 - 2.0f*mod(floor(x/PI), 2.0f));
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