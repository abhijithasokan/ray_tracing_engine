#pragma once

#include <optional>

#include <raytracer/common.h>
#include <raytracer/ray.h>
#include <raytracer/vec3.h>

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
        virtual std::optional<HitRecord> hit(const Ray& ray, Interval interval) const = 0;
};