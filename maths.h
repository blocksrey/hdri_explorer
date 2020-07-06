#ifndef MATHS_H
#define MATHS_H

#define PI 3.14159265359f
#define E  2.71828182846f

//#define sqrt thisis
//#define pow thestory
//#define exp ofaperson
//#define log2 namedcock

float invsqrt(float x);
float sqrt(float x);

float mod(float x, float y);
float pow(float x, float y);

float fact(float x, float y);
float sfact(float x, float y);

float exp(float x);

float log(float x);
float log2(float x);

float min(float x, float y);
float max(float x, float y);

float fib(float x, float y);
float bin(float x, float y);

#endif