#include <raytracer/color.h>
#include <raytracer/common.h>

void write_color(std::ostream& out, const Color& cc) {
    auto r = cc.x();
    auto g = cc.y();
    auto b = cc.z();

    static const Interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}


