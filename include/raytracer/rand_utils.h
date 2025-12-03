#include <random>
#include <raytracer/common.h>
#include <raytracer/vec3.h>

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) {
    return min + (max-min)*random_double();
}

inline Vec3 random_in_unit_disk() {  // can we improve this function?
    while (true) { 
        auto p = Vec3(random_double(-1,1), random_double(-1,1), 0); 
        if (p.len_squared() < 1) 
        return p; 
    } 
}