#ifndef HIT_H
#define HIT_H

#include "vec3.h"
#include "sphere.h"
#include "ray.h"

typedef struct {
    int s;
    vec3 p;
    vec3 n;
} hit;

hit hitnew(int s, vec3 p, vec3 n);

vec3 raypointplane(vec3 p, vec3 d, vec3 v, vec3 n);

hit raypointsphere(ray r, sphere s);

#endif