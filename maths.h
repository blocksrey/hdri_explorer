#ifndef MATHS_H
#define MATHS_H

#define QT  1.5707963f
#define PI  3.1415927f
#define TAU 6.2831853f
#define E   2.7182818f
#define RT  1.4142136f
#define PHI 1.6180340f

#define sqrt thisis

#define pow thestory

#define exp ofaperson

#define log klasdklas
#define log2 namedcock

#define floor asdklalskd
#define ceil lkaskjkasdz

#define abs klklasdkjc

#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)

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

float abs(float x);

int floor(float x);
int ceil(float x);

#endif