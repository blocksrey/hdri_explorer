#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "maths.h"
#include "vec2.h"
#include "vec3.h"
#include "mat3.h"
#include "ray.h"
#include "sphere.h"
#include "hit.h"
#include "trig.h"
#include "int.h"

int main() {
	u8 colordepth = 255;
	u8 maxframes  = 120;
	vec2 viewsize = vec2new(400, 200);
	vec2 hdrisize = vec2new(1800, 900);
	vec3 campos;
	mat3 camori;

	vec2 screencen(vec2 screen, vec2 view) {

	}

	vec2 censcreen(vec2 cen, vec2 view) {

	}

	vec2 cenhdri() {

	}

	vec2 hdricen() {

	}
	
	vec2 hdridir(vec3 dir, vec2 view) {
		float x = dir.x;
		float y = dir.y;
		float z = dir.z;

		return vec2new(
			view.x*atan2(z, x)/TAU,
			view.y*atan2(-y, -sqrt(x*x + z*z))/PI
		);
	}

	vec3 dirhdri(vec2 hdri, vec2 view) {
		float i = TAU*hdri.x/view.x;
		float j =  PI*hdri.y/view.y;

		float s = sin(j);

		return vec3new(
			-sin(i)*s,
			-cos(j),
			-cos(i)*s
		);
	}

	u8 hdritex[(int)(3*hdrisize.x*hdrisize.y)];

	void gettexture() {
		FILE *file = fopen("textures/ocean.ppm", "r");

		printf("%c\n", getc(file));//P
		printf("%c\n", getc(file));//6
		printf("%c\n", getc(file));//\n
		printf("%c\n", getc(file));
		printf("%c\n", getc(file));
		printf("%c\n", getc(file));
		printf("%c\n", getc(file));
		printf("%c\n", getc(file));
		printf("%c\n", getc(file));
		printf("%c\n", getc(file));
		printf("%c\n", getc(file));
		printf("%c\n", getc(file));
		printf("%c\n", getc(file));
		printf("%c\n", getc(file));
		printf("%c\n", getc(file));
		printf("%c\n", getc(file));

		/*
		char sizex[4]; fgets(sizex, sizeof(sizex)/sizeof(sizex[0]) + 1, file);
		printf("SIZEX: %s\n", sizex);

		printf("%c\n", getc(file));//

		char sizey[3]; fgets(sizey, sizeof(sizey)/sizeof(sizey[0]) + 1, file);
		printf("SIZEY: %s\n", sizey);

		printf("%c",   getc(file));//\n

		char range[3]; fgets(range, sizeof(range)/sizeof(range[0]) + 1, file);
		printf("RANGE: %s\n", range);

		printf("%c",   getc(file));//\n

		u16 sizexv = atoi(sizex);
		u16 sizeyv = atoi(sizey);
		u16 rangev = atoi(range);

		printf("INT SIZEX: %i\n", atoi(sizex));
		printf("INT SIZEY: %i\n", atoi(sizey));
		printf("INT RANGE: %i\n", atoi(range));
		*/

		u32 ind = 0;
		for (u16 y = 0; y < hdrisize.y; ++y) for (u16 x = 0; x < hdrisize.x; ++x) {
			u8 colr = getc(file);
			u8 colg = getc(file);
			u8 colb = getc(file);
			
			hdritex[ind] = colr; ++ind;
			hdritex[ind] = colg; ++ind;
			hdritex[ind] = colb; ++ind;
		}

		fclose(file);
	}
	gettexture();

	vec3 gethdricol(vec2 pos) {
		int x = mod(pos.x, hdrisize.x);
		int y = mod(pos.y, hdrisize.y);

		u32 i = 3*(x + hdrisize.x*y);

		return vec3new(
			hdritex[i + 0]/255.f,
			hdritex[i + 1]/255.f,
			hdritex[i + 2]/255.f
		);
	}

	//initialize spheres
	int numspheres = 3;
	sphere spheres[numspheres];
	spheres[0] = spherenew(vec3new( 0,  0,  0), 1.7);
	spheres[1] = spherenew(vec3new(-3, -1, -1), 1.4);
	spheres[2] = spherenew(vec3new( 2,  2,  1), 0.9);

	vec3 trace(vec3 pos, vec3 dir) {
		u8 bestind = 255;
		float bestval = 10000.f;
		vec3 col;
		for (int ind = 0; ind < numspheres; ++ind) {
			hit hitdat = raypointsphere(raynew(pos, dir), spheres[ind]);
			//float val = vec3len(vec3vec3sub(hitdat.p, pos));
			float val = vec3dotself(vec3vec3sub(hitdat.p, pos));
			if (hitdat.s && val < bestval) {
				bestind = ind;
				bestval = val;
				col = trace(hitdat.p, vec3reflect(dir, hitdat.n));
			}
		}
		if (bestind != 255) return col;
		else return gethdricol(hdridir(dir, hdrisize));
	}

	//iterate frames
	for (u8 ind = 0; ind < maxframes; ++ind) {
		//frame progress [0, 1)
		float progress = 1.f*ind/maxframes;

		//set camera position and orientation
		campos = vec3new(-6*sin(TAU*progress), 0, -6*cos(TAU*progress));
		camori = euleranglesy(TAU*progress);

		//initialize file name buffer
		u8 filename[16];
		//write to buffer
		sprintf(filename, "output/%04d.ppm", ind);
		//create file stream
		FILE *file = fopen(filename, "w");
		//write header to file
		fprintf(file, "P6\n%f %f\n%d\n", viewsize.x, viewsize.y, colordepth);

		//iterate through pixels
		for (u16 y = 0; y < viewsize.y; ++y) for (u16 x = 0; x < viewsize.x; ++x) {
			//vec3 reldir = vec3new((2*x - viewsize.x)/viewsize.y, (viewsize.y - 2*y)/viewsize.y, 1);
			vec3 reldir = dirhdri(vec2new(x, viewsize.y - y), viewsize);
			//get world space direction of pixel
			vec3 castdir = vec3unit(mat3vec3mul(camori, reldir));
			//calculate color
			vec3 color = trace(campos, castdir);
			//vec3 color = gethdricol(vec2new(8*x, 8*y));
			//write pixel color
			fwrite((u8[]){colordepth*color.x, colordepth*color.y, colordepth*color.z}, 1, 3, file);
		}

		//close file stream
		fclose(file);
	}

	//end program
	return 0;
}
