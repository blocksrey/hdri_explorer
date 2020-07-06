#include "hit.h"
#include "vec3.h"
#include "maths.h"

hit hitnew(int s, vec3 p, vec3 n) {
    hit h;
    h.s = s;
    h.p = p;
    h.n = n;
    return h;
}

vec3 raypointplane(vec3 p, vec3 d, vec3 v, vec3 n) {
    return vec3vec3add(p, vec3nummul(d, vec3dot(vec3vec3sub(v, p), n)/vec3dot(d, n)));
}

hit raypointsphere(ray r, sphere s) {
    vec3 pi = raypointplane(r.p, r.d, s.p, r.d);
    float xy = vec3len(vec3vec3sub(pi, s.p));
    if (xy < s.r) {
        float z = sqrt(s.r*s.r - xy*xy);
        vec3 p = vec3vec3sub(pi, vec3nummul(r.d, z));
        vec3 n = vec3unit(vec3vec3sub(p, s.p));
        if (vec3dot(vec3vec3sub(p, r.p), r.d) >= 0) {
            return hitnew(1, p, n);
        }
        else {
            return hitnew(0, vec3new(0, 0, 0), vec3new(0, 0, 0));
        }
    }
    else {
        return hitnew(0, vec3new(0, 0, 0), vec3new(0, 0, 0));
    }
}
