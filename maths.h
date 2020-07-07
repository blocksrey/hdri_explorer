#ifndef MATHS_H
#define MATHS_H

#define QT  1.57079632f
#define PI  3.14159265f
#define TAU 6.28318530f
#define E   2.71828182f
#define RT  1.41421356f
#define PHI 1.61803398f

#define sqrt thisis

#define pow thestory

#define exp ofaperson

#define log klasdklas
#define log2 namedcock

#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)

#define floor(x) ((float)(long)(x))
#define ceil(x)  ((float)(long)(x + 1))

float invsqrt(float x);
float sqrt(float x);

float mod(float x, float y);
float pow(float x, float y);

float fact(float x);
float sfact(float x);

float exp(float x);

float log(float x);
float log2(float x);

float fib(float x, float y);
float bin(float x, float y);

float gam(float x);

#endif