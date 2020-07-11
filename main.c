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
#include "int.h"
#include <string.h>

int main() {
	//config
	vec3 campos;
	mat3 camori;
	vec2 viewsize = vec2new(1000, 500);
	//vec2 hdrisize = vec2new(1500, 750);
	u8 colordepth = 255;
	u8 maxframes = 120;

	//y
	//DO HDRI THINGS
	int hdriwidth  = 1800;
	int hdriheight = 900;

	vec2 screencen(vec2 screen, vec2 view) {

	}

	vec2 censcreen(vec2 cen, vec2 view) {

	}

	vec2 cenhdri() {

	}

	vec2 hdricen() {

	}
	
	vec2 dirhdri(vec3 dir, vec2 view) {
		float x = dir.x;
		float y = dir.y;
		float z = dir.z;

		return vec2new(
			view.x*atan2(z, x)/TAU,
			view.y*atan2(-y, -sqrt(x*x + z*z))/PI
		);
	}

	vec3 hdridir(vec2 hdri, vec2 view) {
		float i = TAU*hdri.x/view.x;
		float j =  PI*hdri.y/view.y;

		float s = sin(j);

		return vec3new(
			-sin(i)*s,
			-cos(j),
			-cos(i)*s
		);
	}

	u8 hdritex[3*hdriwidth*hdriheight];


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
		for (u16 y = 0; y < hdriheight; ++y) for (u16 x = 0; x < hdriwidth; ++x) {
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
		int x = mod(pos.x, hdriwidth);
		int y = mod(pos.y, hdriheight);

		u32 i = 3*(x + hdriwidth*y);

		return vec3new(
			hdritex[i + 0]/255.f,
			hdritex[i + 1]/255.f,
			hdritex[i + 2]/255.f
		);
	}

	vec3 tween3(vec3 a, vec3 b, float p) {
		float o = 1 - p;

		return vec3new(
			o*a.x + p*b.x,
			o*a.y + p*b.y,
			o*a.z + p*b.z
		);
	}

	//store information
	int numspheres = 3;

	sphere spheres[] = {
		spheres[0] = spherenew(vec3new( 0,  0,  0), 1.7),
		spheres[1] = spherenew(vec3new(-3, -1, -1), 1.4),
		spheres[2] = spherenew(vec3new( 2,  2,  1), 0.9)
	};

	vec3 vec3reflect(vec3 v, vec3 n) {
		return vec3vec3sub(v, vec3nummul(n, 2*vec3dot(v, n)));
	}

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
		else return gethdricol(dirhdri(dir, vec2new(hdriwidth, hdriheight)));
	}

	for (u8 i = 0; i < maxframes; ++i) {
		float progress = 1.f*i/maxframes;

		campos = vec3new(-6*sin(TAU*progress), 0, -6*cos(TAU*progress));
		camori = euleranglesy(TAU*progress);

		//fucking name
		u8 filename[24];
		sprintf(filename, "output/%04d.ppm", i);
		//open file
		FILE *file = fopen(filename, "w");
		//create header data
		fprintf(file, "P6\n%f %f\n%d\n", viewsize.x, viewsize.y, colordepth);

		//iterate through pixels
		for (u16 y = 0; y < viewsize.y; ++y) for (u16 x = 0; x < viewsize.x; ++x) {
			//vec3 reldir = vec3new((2*x - viewsize.x)/viewsize.y, (viewsize.y - 2*y)/viewsize.y, 1);
			vec3 reldir = hdridir(vec2new(x, viewsize.y - y), viewsize);
			//get world space direction of pixel
			vec3 castdir = vec3unit(mat3vec3mul(camori, reldir));
			//calculate color
			vec3 color = trace(campos, castdir);
			//vec3 color = gethdricol(vec2new(8*x, 8*y));
			//write pixel color
			fwrite((u8[]){colordepth*color.x, colordepth*color.y, colordepth*color.z}, 1, 3, file);
		}

		//close file
		fclose(file);
	}

	//terminate
	return 0;
}
