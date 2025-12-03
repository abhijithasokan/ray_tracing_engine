#pragma once

#include <raytracer/common.h>
#include <raytracer/ray.h>
#include <raytracer/vec3.h>
#include <raytracer/color.h>
#include <raytracer/hittable.h>
#include <raytracer/hittable_list.h>

using u_short = unsigned short int;

class CameraIntrinsicParameters {
private:
    double _focus_dist;
    double _vp_height, _vp_width;
    double _vertical_fov; // field of view in degrees
    double _defocus_angle; // in degrees

public:
    constexpr CameraIntrinsicParameters(double focus_dist, double vfov, double defocus_angle, double rr)
    : _focus_dist(focus_dist), _vertical_fov(vfov), _defocus_angle(defocus_angle) {
        auto theta = degrees_to_radians(_vertical_fov);
        _vp_height = 2.0 * std::tan(theta / 2.0) * _focus_dist;
        _vp_width = rr * _vp_height;
    }

    constexpr double focus_dist() const { return _focus_dist; }
    constexpr double vp_height() const { return _vp_height; }
    constexpr double vp_width() const { return _vp_width; }
    constexpr double vertical_fov() const { return _vertical_fov; }
    constexpr double defocus_angle() const { return _defocus_angle; }
    constexpr double compute_defocus_radius() const {
        return _focus_dist * std::tan(degrees_to_radians(_defocus_angle) / 2.0);
    }
};


class RenderImageParams {
private:
    u_short _width, _height;
    double _aspect_ratio;

public:
    constexpr RenderImageParams(u_short width, double aspect_ratio) : _width(width), _aspect_ratio(aspect_ratio) {
        _height = _width / _aspect_ratio;
        _height = (_height == 0) ? 1 : _height;
    }
    constexpr u_short width() const { return _width; }
    constexpr u_short height() const { return _height; }
    constexpr double aspect_ratio() const { return _aspect_ratio; }
};



class Camera {
private:
    CameraIntrinsicParameters cam_params;
    RenderImageParams img_params;

    // camera location and orientation
    Point look_from;
    Point look_at;
    Vec3 vup; // "view up" vector
    Vec3 u, v, w; // camera coordinate system basis vectors

    // things related to rendering
    Vec3 pixel_delta_u, pixel_delta_v;
    Point pixel00_location; // location of the upper left pixel
    Vec3 defocus_disk_u, defocus_disk_v;

    ushort samples_per_pixel = 1;
    int max_depth = 50;

    constexpr static double SURFACE_ACHNE_OFFSET = 1e-3;

private:    
    Camera(const Point& look_from, const Point& look_at, const Vec3& vup, const CameraIntrinsicParameters& cam_params, const RenderImageParams& img_params) 
    : look_from(look_from), look_at(look_at), vup(vup), cam_params(cam_params), img_params(img_params) {
        initialize_camera();
    }

    void initialize_camera() {
        initialize_camera_coordinate_system();
        initialize_pixel_deltas_and_location();
    }

public:
    void render_scene(const HittableList& world);

    static Camera create_camera(const Point& look_from, const Point& look_at, 
        double vpov, double defocus_angle, double focus_dist,
        const RenderImageParams& img_params);
    constexpr ushort get_samples_per_pixel() const { return samples_per_pixel; }
    constexpr void set_samples_per_pixel(ushort samples) { samples_per_pixel = samples; }

private:
    void initialize_pixel_deltas_and_location(); 
    void initialize_camera_coordinate_system();
    Color ray_color(const Ray& ray, const HittableList& world, int depth);
    Ray get_ray(u_short i, u_short j) const;
    Vec3 defocus_disk_sample() const;
};


