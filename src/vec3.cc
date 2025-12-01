#include <raytracer/vec3.h>
#include <raytracer/rand_utils.h>


Vec3 Vec3::random(double min, double max) {
    return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

Vec3 Vec3::random() {
    return Vec3::random(0.0, 1.0);
}

Vec3 Vec3::random_unit_vector() {
    while(true) {
        auto p = Vec3::random(-1.0, 1.0);
        auto len_sq = p.len_squared();
        if(VERY_SMALL_POSITIVE_DOUBLE < len_sq && len_sq <= 1.0) 
            return p / std::sqrt(len_sq);
    }
}

Vec3 Vec3::random_on_hemisphere(const Vec3& normal) {
    Vec3 on_unit_sphere = random_unit_vector();
    
    if(dot(normal, on_unit_sphere) > 0.0)
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}