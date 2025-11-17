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

class Interval {
private:
    double _min = +infinity;
    double _max = -infinity;

public:
    constexpr Interval() = default;
    constexpr Interval(double min, double max) : _min(min), _max(max) {}

    constexpr double min() const { return _min; }
    constexpr double max() const { return _max; }
    constexpr double size() const { return _max - _min; }
    constexpr bool contains(double xx) const { return _min <= xx && xx <= _max; }
    constexpr bool surrounds(double xx) const { return _min < xx && xx < _max; }
    constexpr double clamp(double x) const {
        if (x < _min) return _min;
        if (x > _max) return _max;
        return x;
    }
    static const Interval empty, universe;
};