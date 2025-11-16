#pragma once

#include <optional>

#include "ray.h"
#include "vec3.h"

struct HitRecord {
public:
    Point p;
    Vec3 normal;
    double tt; // time
    bool front_face;

    void set_face_normal(const Ray& r, const Vec3& outward_normal) {
        front_face = dot(r.get_direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};


class Hittable {
    public:
        virtual std::optional<HitRecord> hit(const Ray& ray, double tmin, double tmax) const = 0;
};