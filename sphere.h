#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"

typedef struct {
    vec3 p;
    float r;
} sphere;

sphere spherenew(vec3 p, float r);

#endif