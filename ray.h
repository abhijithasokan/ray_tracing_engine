#pragma once

#include "vec3.h"

class Ray {
    private: 
        Point origin;
        Vec3 direction;      
        
    public:
        Ray(const Point& ori, const Vec3& dir) : origin(ori), direction(dir) {}

        const auto& get_origin() const { return origin; }
        const auto& get_direction() const { return direction; }

        Point at(double tt) const {
            return origin + tt * direction;
        }

};

