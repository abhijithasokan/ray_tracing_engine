#pragma once

#include <memory>
#include <vector>

#include "ray.h"
#include "vec3.h"
#include "hittable.h"


using HittablePtr = std::shared_ptr<Hittable>;

class HittableList {
private:
    std::vector<HittablePtr> objects;

public:
    HittableList() {}
    // HittableList(const HittablePtr& object) {
    //     add(object);
    // }

    void add(HittablePtr object) {
        objects.push_back(object);
    }

    std::optional<HitRecord> hit(const Ray& ray, double tmin, double tmax) const {
        std::optional<HitRecord> hit_rec;  
        auto closest_so_far = tmax;

        for(const auto& object: objects) {
            auto obj_hit_rec = object->hit(ray, tmin, closest_so_far);
            if(obj_hit_rec) {
                hit_rec = obj_hit_rec;
                closest_so_far = obj_hit_rec->tt;
            }
        }

        return hit_rec;
    }
};