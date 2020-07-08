#include <stdio.h>
#include <stdlib.h>
#include "maths.h"
#include "vec2.h"
#include "vec3.h"
#include "mat3.h"
#include "ray.h"
#include "sphere.h"
#include "hit.h"
#include "trig.h"

vec3 skycolor(vec3 d) {
	float x = d.x;
	float y = d.y;
	float z = d.z;
	//return vec3new(0.6 + 0.4*y*y, 0.6 + 0.4*y*y, 1.0);
	return vec3new(max(0, d.x), max(0, d.y), max(0, d.z));
}

int main() {
	//config
	vec3 worldlightposition = vec3unit(vec3new(-1, 3, -2));
	vec3 worldlightcolor = vec3new(1, 0, 0);
	vec3 cameraposition = vec3new(0, 0, 0);
	mat3 cameraorientation = mat3mat3mul(mat3mat3mul(euleranglesx(-0.1), euleranglesy(-0.2)), euleranglesz(0.1));
	vec2 viewsize = vec2new(800, 600);
	int colordepth = 255;
	//y

	vec3 tween3(vec3 a, vec3 b, float p) {
		float ax = a.x;
		float ay = a.y;
		float az = a.z;

		float bx = b.x;
		float by = b.y;
		float bz = b.z;

		return vec3new(
			ax + p*(bx - ax),
			ay + p*(by - ay),
			az + p*(bz - az)
		);
	}

	//store information
	int numspheres = 3;

	sphere spheres[] = {
		spheres[0] = spherenew(vec3new(1.2, -0.3, 4), 1.7),
		spheres[1] = spherenew(vec3new(-2.6, 0.5, 6), 0.9),
		spheres[2] = spherenew(vec3new(3.5, 4.7, 7.2), 1.4)
	};

	vec3 spherecolors[] = {
		vec3new(1, 0, 0),
		vec3new(0, 1, 0),
		vec3new(0, 0, 1)
	};

	float spherereflects[] = {
		0,
		0,
		0
	};

	vec3 vec3reflect(vec3 v, vec3 n) {
		return vec3vec3sub(v, vec3nummul(n, 2*vec3dot(v, n)));
	}

	//cool stuff
	vec3 trace(vec3 p, vec3 d) {
		for (int i = 0; i < numspheres; ++i) {
			hit h = raypointsphere(raynew(p, d), spheres[i]);
			if (h.s) {
				float distance = vec3len(vec3vec3sub(h.p, p));
				vec3 color0 = tween3(vec3nummul(vec3vec3mul(worldlightcolor, spherecolors[i]), max(0, vec3dot(h.n, worldlightposition))), trace(h.p, vec3reflect(d, h.n)), spherereflects[i]);
				return color0;
			}
		}
		return skycolor(d);
	}
	
	//dewit
	for (int i = 0; i < 240; ++i) {
		cameraposition = vec3vec3add(cameraposition, vec3new(0.1/4.0, 0.07/4.0, 0.4/4.0));
		cameraorientation = mat3mat3mul(cameraorientation, mat3mat3mul(euleranglesy(-0.03), euleranglesz(0.01)));
		//fucking name
		char filename[32];
		sprintf(filename, "output/%04d.ppm", i);
		//open file
		FILE *file = fopen(filename, "wb");
		//create initial data
		fprintf(file, "P6\n%f %f\n%d\n", viewsize.x, viewsize.y, colordepth);

		//iterate through pixels
		for (int y = 0; y < viewsize.y; ++y) for (int x = 0; x < viewsize.x; ++x) {
			//get world space direction of pixel
			vec3 castdirection = vec3unit(mat3vec3mul(cameraorientation, vec3new((2*x - viewsize.x)/viewsize.y, (viewsize.y - 2*y)/viewsize.y, 0.5)));
			//calculate color
			vec3 color = trace(cameraposition, castdirection);
			//write pixel color
			fwrite((char[]){colordepth*color.x, colordepth*color.y, colordepth*color.z}, 1, 3, file);
		}

		//close file
		fclose(file);
	}

	//terminate
	return 0;
}
