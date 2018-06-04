#ifndef __RT1_HITABLE_LIST_H
#define __RT1_HITABLE_LIST_H

#include "hitable.h"
#include <vector>

class hitable_list : public hitable {
public:
	hitable_list() : list(std::vector<hitable*>()) {  }
	virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;

	std::vector<hitable*> list;
};

bool hitable_list::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
	hit_record temp_rec;
	bool hit_anything = false;
	double closest_so_far = t_max;
	for (auto& h : list) {
		if (h->hit(r, t_min, closest_so_far, temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}

#endif