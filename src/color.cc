#include <raytracer/color.h>

void write_color(std::ostream& out, const Color& cc) {
    auto r = cc.x();
    auto g = cc.y();
    auto b = cc.z();

    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}


