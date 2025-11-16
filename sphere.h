#pragma once

#include "vec3.h"
#include "hittable.h"


class Sphere : public Hittable {
private:
    Vec3 center;
    double radius;

public:
    Sphere(const Vec3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}

    std::optional<HitRecord> hit(const Ray& ray, double tmin, double tmax) const {
        Vec3 oc = center - ray.get_origin();

        auto a = ray.get_direction().len_squared();
        auto h = dot(oc, ray.get_direction());
        auto c = oc.len_squared() - radius * radius;

        auto discriminant = h*h - a*c;
        if(discriminant < 0.0) 
            return std::nullopt;
        
        
        auto sq_discriminant = std::sqrt(discriminant);
        auto tt = (h - sq_discriminant) / a;
        if(tt <= tmin || tt >= tmax) 
            tt = (h + sq_discriminant) / a;
        
        if(tt <= tmin || tt >= tmax)
            return std::nullopt;

        
        HitRecord hit_rec;
        hit_rec.p = ray.at(tt);
        hit_rec.tt = tt;
        
        auto outward_normal = (hit_rec.p - center) / radius;
        hit_rec.set_face_normal(ray, outward_normal);

        return hit_rec;
    }
};