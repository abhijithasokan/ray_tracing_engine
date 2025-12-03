#pragma once

#include <array>
#include <cmath>
#include <cassert>

class Vec3 {
    private:
        std::array<double, 3> ele;

    public:
        constexpr Vec3() : ele{0.0, 0.0, 0.0}  {}
        constexpr Vec3(double e0, double e1, double e2) : ele{e0, e1, e2} {}

        // Accessors
        constexpr auto x() const { return ele[0]; }
        constexpr auto y() const { return ele[1]; }
        constexpr auto z() const { return ele[2]; }

        // Operator overloads
        constexpr Vec3 operator-() const {
            return Vec3(-ele[0], -ele[1], -ele[2]);
        }

        constexpr auto& operator[](std::size_t ind) { 
            assert(ind < 3);
            return ele[ind];
        }

        constexpr auto operator[](std::size_t ind) const { 
            assert(ind < 3);
            return ele[ind];
        }

        Vec3& operator+=(const Vec3& other) {
            ele[0] += other[0];
            ele[1] += other[1];
            ele[2] += other[2];
            return *this;
        }

        Vec3& operator*=(double mm) {
            ele[0] *= mm;
            ele[1] *= mm;
            ele[2] *= mm;
            return *this;
        }

        Vec3& operator/=(double mm) {
            assert(mm != 0.0);
            return *this *= (1.0 / mm);
        }

        Vec3& operator*=(const Vec3& other) {
            ele[0] *= other[0];
            ele[1] *= other[1];
            ele[2] *= other[2];
            return *this;
        }

        constexpr double len_squared() const {
            return ele[0]*ele[0] + ele[1]*ele[1] + ele[2]*ele[2];
        }        

        double len() const {
            return std::sqrt(len_squared());
        }

        bool near_zero() const { 
            constexpr auto sv = 1e-8;
            return (std::fabs(ele[0]) < sv) && (std::fabs(ele[1]) < sv) && (std::fabs(ele[2]) < sv);
        }

        // Friend functions
        friend Vec3 operator*(double t, Vec3 v) { 
            v *= t;
            return v;
        }

        friend Vec3 operator+(Vec3 u, const Vec3& v) {
            u += v;
            return u;
        }

        friend Vec3 operator-(Vec3 u, const Vec3& v) {
            u += -v;
            return u;
        }

        friend Vec3 operator*(Vec3 u, const Vec3& v) {
            u *= v;
            return u;
        }

        friend double dot(const Vec3& u, const Vec3& v) {
            return u[0] * v[0]
                 + u[1] * v[1]
                 + u[2] * v[2];
        }

        friend Vec3 cross(const Vec3& u, const Vec3& v) {
            return Vec3(u[1] * v[2] - u[2] * v[1],
                        u[2] * v[0] - u[0] * v[2],
                        u[0] * v[1] - u[1] * v[0]);
        }
        
        friend inline Vec3 unit_vector(Vec3 v) {
            v /= v.len();
            return v;
        }

        static Vec3 random(double min, double max);
        static Vec3 random();
        static Vec3 random_unit_vector();
        static Vec3 random_on_hemisphere(const Vec3& normal);
};

using Point = Vec3;



inline Vec3 operator*(const Vec3& vec, double mm) { return mm * vec; }
inline Vec3 operator/(const Vec3& vec, double mm) { return (1/mm) * vec; }
inline Vec3 reflect(const Vec3& in_vec, const Vec3& normal) {
    return in_vec - 2*dot(in_vec, normal)*normal;
}

static constexpr const double VERY_SMALL_POSITIVE_DOUBLE = 1e-160;

