#pragma once

#include <iostream>
#include <raytracer/vec3.h>


using Color = Vec3;
void write_color(std::ostream& out, const Color& cc);
double linear_to_gamma(double linear_intensity);