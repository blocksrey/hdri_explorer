#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct {
    vec3 p;
    vec3 d;
} ray;

ray raynew(vec3 p, vec3 d);

#endif