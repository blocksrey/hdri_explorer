#include "maths.h"

float invsqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck? 
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//  y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}

float sqrt(float x) {
	return 1.0f/invsqrt(x);//lol
}

float mod(float x, float y) {
	return x - y*floor(x/y);
}

float pow(float x, float y) {
	return exp(log(x)*y);
}

float fact(float x) {
	return x > 0 ? x*fact(x - 1) : 1;
}

float sfact(float x) {
	return sqrt(2.0f*PI*x)*pow(x/E, x);
}

float exp(float x) {
	x = x/1024.0f + 1.0f;
	x *= x; x *= x; x *= x; x *= x;
	x *= x; x *= x; x *= x; x *= x;
	x *= x; x *= x;
	return x;
}

float log(float x) {
	return 0.69314718f*log2(x);
}

float log2(float x)  // compute log2(x) by reducing x to [0.75, 1.5)
{
	// a*(x-1)^2 + b*(x-1) approximates log2(x) when 0.75 <= x < 1.5
	const float a =  -.6296735;
	const float b =   1.466967;
	float signif, fexp;
	int exp;
	float lg2;
	union { float f; unsigned int i; } ux1, ux2;
	int greater; // really a boolean 
	/* 
	 * Assume IEEE representation, which is sgn(1):exp(8):frac(23)
	 * representing (1+frac)*2^(exp-127)  Call 1+frac the significand
	 */

	// get exponent
	ux1.f = x;
	exp = (ux1.i & 0x7F800000) >> 23; 
	// actual exponent is exp-127, will subtract 127 later

	greater = ux1.i & 0x00400000;  // true if signif > 1.5
	if (greater) {
		// signif >= 1.5 so need to divide by 2.  Accomplish this by 
		// stuffing exp = 126 which corresponds to an exponent of -1 
		ux2.i = (ux1.i & 0x007FFFFF) | 0x3f000000;
		signif = ux2.f;
		fexp = exp - 126;    // 126 instead of 127 compensates for division by 2
		signif = signif - 1.0;                    // <
		lg2 = fexp + a*signif*signif + b*signif;  // <
	} else {
		// get signif by stuffing exp = 127 which corresponds to an exponent of 0
		ux2.i = (ux1.i & 0x007FFFFF) | 0x3f800000;
		signif = ux2.f;
		fexp = exp - 127;
		signif = signif - 1.0;                    // <<--
		lg2 = fexp + a*signif*signif + b*signif;  // <<--
	}
	// lines marked <<-- are common code, but optimize better 
	//  when duplicated, at least when using gcc
	return(lg2);
}

float fib(float x, float y) {

}

float bin(float x, float y) {

}

float gam(float x) {
	return sfact(x - 1);
}

float abs(float x) {
	return x < 0 ? x : -x;
}

int floor(float x) {
	int xi = (int)x;
	return x < xi ? xi - 1 : xi;
}

int ceil(float x) {
	int xi = (int)x;
	return x < xi ? xi : xi + 1;
}
