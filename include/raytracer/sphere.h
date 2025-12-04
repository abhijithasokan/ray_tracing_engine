#pragma once

#include <memory>
#include <optional>

#include <raytracer/common.h>
#include <raytracer/vec3.h>
#include <raytracer/ray.h>
#include <raytracer/hittable.h>

class Material; 

class Sphere : public Hittable {
protected:
    Point center;
    double radius;
    std::shared_ptr<Material> mat_ptr;

public:
    Sphere(const Point& center, double radius, std::shared_ptr<Material> mat_ptr) : center(center), radius(std::fmax(0, radius)), mat_ptr(mat_ptr) {}
    std::optional<HitRecord> hit(const Ray& ray, Interval interval) const override {
        return hit_c(center, ray, interval);
    }

protected:
    std::optional<HitRecord> hit_c(const Point& cur_center, const Ray& ray, Interval interval) const;
};


class MovingSphere : public Sphere {
private:
    Ray movement_ray; // defines the movement of the sphere over time
public:
    MovingSphere(const Point& center_start, const Point& center_end, double radius, std::shared_ptr<Material> mat_ptr)
        : Sphere(center_start, radius, mat_ptr),
          movement_ray(Ray(center_start, center_end - center_start, 1.0)) {} // time from 0.0 to 1.0

    std::optional<HitRecord> hit(const Ray& ray, Interval interval) const override;
};