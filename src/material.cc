#include <raytracer/material.h>

std::optional<std::pair<Ray, Color>> Lambertian::scatter(const Ray& ray_in, const HitRecord& rec) const {
    auto scatter_direction = rec.normal + Vec3::random_unit_vector();
    if(scatter_direction.near_zero()) // case when normal and random unit vector are opposite
        scatter_direction = rec.normal;
    Ray scattered_ray(rec.p, scatter_direction);
    return std::make_optional(std::make_pair(scattered_ray, albedo));
}

std::optional<std::pair<Ray, Color>> Metal::scatter(const Ray& ray_in, const HitRecord& rec) const {
    auto reflected = reflect(ray_in.get_direction(), rec.normal);
    reflected = unit_vector(reflected) + fuzz * Vec3::random_unit_vector();
    Ray scattered_ray(rec.p, reflected);
    if(dot(scattered_ray.get_direction(), rec.normal) <= 0) // ray is scattered inside the surface
        return std::nullopt;
    return std::make_optional(std::make_pair(scattered_ray, albedo));
}