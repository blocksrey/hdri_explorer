#include "ray.h"

ray raynew(vec3 p, vec3 d) {
    ray r;
    r.p = p;
    r.d = d;
    return r;
}