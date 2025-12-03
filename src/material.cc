#include <raytracer/rand_utils.h>
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

std::optional<std::pair<Ray, Color>> Dielectric::scatter(const Ray& ray_in, const HitRecord& rec) const {
    Color attenuation(1.0, 1.0, 1.0); // no attenuation for dielectric materials

    double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;
    auto unit_direction = unit_vector(ray_in.get_direction());
    
    auto cosine = std::fmin(dot(-unit_direction, rec.normal), 1.0);
    auto is_reflected = (!can_refract(unit_direction, rec.normal, ri)) ||
                        (reflectance(cosine, ri) < random_double());
    Vec3 direction = is_reflected ? reflect(unit_direction, rec.normal) : refract(unit_direction, rec.normal, ri);
    Ray scattered_ray(rec.p, direction);
    return std::make_optional(std::make_pair(scattered_ray, attenuation));
}

bool Dielectric::can_refract(const Vec3& unit_direction, const Vec3& normal, double ri) const {
    double cos_theta = std::fmin(dot(-unit_direction, normal), 1.0);
    double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

    bool cannot_refract = ri * sin_theta > 1.0;
    return !cannot_refract;
}

double Dielectric::reflectance(double cosine, double ri) {
    // Use Schlick's approximation for reflectance.
    auto r0 = (1 - ri) / (1 + ri);
    r0 = r0*r0;
    return r0 + (1-r0)*std::pow((1 - cosine),5);
}