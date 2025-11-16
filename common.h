#pragma once

#include <limits>
#include <memory>

using std::make_shared;
using std::shared_ptr; 

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) { return degrees * pi / 180.0; }

template<typename T>
inline T sq(T x) { return x * x; }