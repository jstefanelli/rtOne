// rtOne.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <random>
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"
#include "metallic.h"
#include "lambertian.h"
#include <memory>

#define MAX_DISTANCE 100000.0f

#define NX 800
#define NY 400
#define NS 50
#define NB 50


vec3 color(const ray &r, hitable& world, int bounce) {
	hit_record rec;
	if (world.hit(r, 0.001, MAX_DISTANCE, rec)) {
		ray scattered;
		vec3 attenuation;
		if (bounce < NB && rec.mat->scatter(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, bounce + 1);
		}
		else {
			return vec3(0, 0, 0);
		}
	}
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5*(unit_direction.y() + 1.0);
	return (1.0 - t) * vec3(1, 1, 1) + t * vec3(0.5, 0.7, 1.0);
}

vec3 color(const ray &r, hitable& world) {
	return color(r, world, 0);
}


int main()
{
	std::ofstream f("out.ppm");
	f << "P3\n" << NX << " " << NY << "\n255\n";
	hitable_list list;
	lambertian mat1(vec3(0, 0, 1));
	lambertian mat2(vec3(0.9, 0.9, 0.9));
	metal mat3(vec3(0.9, 0.9, 0.9));
	sphere s1(vec3(0.5, 0, -1), 0.5, &mat1);
	sphere s2(vec3(0, -100.5, -1), 100, &mat2);
	sphere s3(vec3(-0.5, 0, -1), 0.5, &mat3);
	list.list.push_back(&s1);
	list.list.push_back(&s2);
	list.list.push_back(&s3);
	camera cam;
	int n = 1;
	for (int j = NY - 1; j >= 0; j--) {
		std::cout << "Calculating row " << n << "/" << NY << "\r";
		for (int i = 0; i < NX; i++) {
			vec3 col(0, 0, 0);
			for (int s = 0; s < NS; s++) {
				float u = float(i + (2 * getRandom()) - 0.5f) / float(NX);
				float v = float(j + (2 * getRandom()) - 0.5f) / float(NY);
				ray r = cam.get_ray(u, v);
				col += color(r, list);
			}
			col /= NS;
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99* col[0]);
			int ig = int(255.99* col[1]);
			int ib = int(255.99* col[2]);
			f << ir << " " << ig << " " << ib << "\n";
		}
		n++;
	}
	std::cout << "\n";
	f.close();
    return 0;
}

