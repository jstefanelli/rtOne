#ifndef __RT1_MATERIAL_H
#define __RT1_MATERIAL_H

#include "ray.h"
#include "hitable.h"

class material {
public:
	virtual bool scatter(const ray &r, const hit_record &rec, vec3 &attenutation, ray& scattered) const = 0;
};

#endif
