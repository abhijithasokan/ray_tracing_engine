#include <memory>
#include <vector>

#include <raytracer/hittable_list.h>

#include <raytracer/common.h>
#include <raytracer/ray.h>
#include <raytracer/hittable.h>


std::optional<HitRecord> HittableList::hit(const Ray& ray, Interval interval) const {
    std::optional<HitRecord> hit_rec;  
    auto closest_so_far = interval.max();

    for(const auto& object: objects) {
        auto obj_hit_rec = object->hit(ray, Interval(interval.min(), closest_so_far));
        if(obj_hit_rec) {
            hit_rec = obj_hit_rec;
            closest_so_far = obj_hit_rec->tt;
        }
    }

    return hit_rec;
}
