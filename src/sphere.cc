#include <raytracer/sphere.h>

#include <raytracer/common.h>
#include <raytracer/vec3.h>
#include <raytracer/ray.h>


std::optional<HitRecord> Sphere::hit_c(const Point& cur_center, const Ray& ray, Interval interval) const {
    Vec3 oc = cur_center - ray.get_origin();

    auto a = ray.get_direction().len_squared();
    auto h = dot(oc, ray.get_direction());
    auto c = oc.len_squared() - radius * radius;

    auto discriminant = h*h - a*c;
    if(discriminant < 0.0) 
        return std::nullopt;
    
    
    auto sq_discriminant = std::sqrt(discriminant);
    auto tt = (h - sq_discriminant) / a;
    if(!interval.surrounds(tt)) 
        tt = (h + sq_discriminant) / a;
    
    if(!interval.surrounds(tt))
        return std::nullopt;

    
    HitRecord hit_rec;
    hit_rec.p = ray.at(tt);
    hit_rec.tt = tt;
    hit_rec.mat_ptr = mat_ptr;
    
    auto outward_normal = (hit_rec.p - cur_center) / radius;
    hit_rec.set_face_normal(ray, outward_normal);

    return hit_rec;
}


std::optional<HitRecord> MovingSphere::hit(const Ray& ray, Interval interval) const {
    // Compute sphere center at the time of the ray
    auto cur_center = movement_ray.at(ray.get_time());
    return Sphere::hit_c(cur_center, ray, interval);
}