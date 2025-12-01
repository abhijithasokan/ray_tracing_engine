#include <raytracer/color.h>
#include <raytracer/common.h>


double linear_to_gamma(double linear_intensity) {
    // using gamma = 2.0
    if(linear_intensity > 0.0)
        return std::sqrt(linear_intensity);
    
    return 0.0;
}

void write_color(std::ostream& out, const Color& cc) {
    auto r = linear_to_gamma(cc.x());
    auto g = linear_to_gamma(cc.y());
    auto b = linear_to_gamma(cc.z());

    static const Interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}


