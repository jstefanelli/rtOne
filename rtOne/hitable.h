#ifndef __RT1_HITABLE_H
#define __RT1_HITABLE_H

#include "ray.h"
#include <memory>

class material;

struct hit_record {
	float t;
	vec3 p;
	vec3 normal;
	material* mat;
};

class hitable {
public:
	virtual bool hit(const ray& ray, float t_min, float t_max, hit_record &rec) const = 0;
};


#endif