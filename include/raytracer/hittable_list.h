#pragma once

#include <memory>
#include <vector>

#include <raytracer/common.h>
#include <raytracer/ray.h>
#include <raytracer/hittable.h>

using HittablePtr = std::shared_ptr<Hittable>;

class HittableList {
private:
    std::vector<HittablePtr> objects;

public:
    HittableList() {}

    void add(HittablePtr object) {
        objects.push_back(object);
    }

    std::optional<HitRecord> hit(const Ray& ray, Interval interval) const;
};