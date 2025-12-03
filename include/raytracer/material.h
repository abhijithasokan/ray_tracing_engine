#pragma once

#include <optional>

#include <raytracer/hittable.h>
#include <raytracer/ray.h>
#include <raytracer/color.h>


class Material {
    public:
        virtual std::optional<std::pair<Ray, Color>> scatter(const Ray& ray_in, const HitRecord& rec) const = 0;
};

class Lambertian : public Material {
    private:
        Color albedo;

    public:
        Lambertian(const Color& a) : albedo(a) {}
        std::optional<std::pair<Ray, Color>> scatter(const Ray& ray_in, const HitRecord& rec) const override;
};

class Metal : public Material {
    private:
        Color albedo;

    public:
        Metal(const Color& a) : albedo(a) {}
        std::optional<std::pair<Ray, Color>> scatter(const Ray& ray_in, const HitRecord& rec) const override;
};