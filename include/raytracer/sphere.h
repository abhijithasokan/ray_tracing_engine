#pragma once

#include <raytracer/common.h>
#include <raytracer/vec3.h>
#include <raytracer/ray.h>
#include <raytracer/hittable.h>


class Sphere : public Hittable {
private:
    Vec3 center;
    double radius;

public:
    Sphere(const Vec3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}
    std::optional<HitRecord> hit(const Ray& ray, Interval interval) const;
};