#ifndef __RT1_LAMBERTIAN_H
#define __RT1_LAMBERTIAN_H

#include "material.h"

class lambertian : public material {
public:
	lambertian(vec3 alb) : albedo(alb) {}

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenutation, ray& scattered) const {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = ray(rec.p, target - rec.p);
		attenutation = albedo;
		return true;
	}

	vec3 albedo;
};

#endif