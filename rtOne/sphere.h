#ifndef __RT1_SPHERE_H
#define __RT1_SPHERE_H

#include "vec3.h"
#include "hitable.h"
#include "material.h"
#include <memory>

class sphere : public hitable {
public:
	sphere() {}
	sphere(vec3 cen, float r, material* m) { center = cen; radius = r; mat = m; }
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;

	material* mat;
	vec3 center;
	float radius;
};

bool sphere::hit(const ray &r, float t_min, float t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float delta = (b * b) - (a*c);
	if (delta > 0) {
		float sqrd = sqrt(delta);
		float temp = (-b - sqrd) / a;
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(temp);
			rec.normal = (rec.p - center) / radius; // TODO: "/ radius" might be to normalize. Investigate.
			rec.mat = mat;
			return true;
		}

		temp = (-b + sqrd) / a;
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(temp);
			rec.normal = (rec.p - center) / radius; // same as above
			rec.mat = mat;
			return true;
		}

	}
	return false;
}




#endif