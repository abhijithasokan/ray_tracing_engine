#pragma once

#include <memory>
#include <optional>

#include <raytracer/common.h>
#include <raytracer/vec3.h>
#include <raytracer/ray.h>
#include <raytracer/hittable.h>

class Material; 

class Sphere : public Hittable {
private:
    Vec3 center;
    double radius;
    std::shared_ptr<Material> mat_ptr;

public:
    Sphere(const Vec3& center, double radius, std::shared_ptr<Material> mat_ptr) : center(center), radius(std::fmax(0, radius)), mat_ptr(mat_ptr) {}
    std::optional<HitRecord> hit(const Ray& ray, Interval interval) const;
};