#pragma once

#include <raytracer/vec3.h>

class Ray {
    private: 
        Point origin;
        Vec3 direction;
        double time; // used for feature like motion blur
        
    public:
        Ray(const Point& ori, const Vec3& dir, double t = 0.0) : origin(ori), direction(dir), time(t) {}

        const auto& get_origin() const { return origin; }
        const auto& get_direction() const { return direction; }
        double get_time() const { return time; }

        Point at(double tt) const {
            return origin + tt * direction;
        }

};

