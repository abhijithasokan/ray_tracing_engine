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
    double _focal_length;
    double _vp_height, _vp_width;

public:
    constexpr CameraIntrinsicParameters(double focal_len, double vp_width, double vp_height) 
    : _focal_length(focal_len), _vp_width(vp_width), _vp_height(vp_height) {
    }

    constexpr double focal_length() const { return _focal_length; }
    constexpr double vp_height() const { return _vp_height; }
    constexpr double vp_width() const { return _vp_width; }
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
    Point origin;

    // things related to rendering
    Vec3 pixel_delta_u, pixel_delta_v;
    Point pixel00_location; // location of the upper left pixel
    ushort samples_per_pixel = 1;
    int max_depth = 10;

    constexpr static double SURFACE_ACHNE_OFFSET = 1e-3;

public:    
    Camera(const Point& origin, const CameraIntrinsicParameters& cam_params, const RenderImageParams& img_params) 
    : origin(origin), cam_params(cam_params), img_params(img_params) {
        initialize_camera();
    }

    void initialize_camera() {
        initialize_pixel_deltas_and_location();
    }

    void render_scene(const HittableList& world);

    static Camera create_default_camera(const RenderImageParams& img_params);
    constexpr ushort get_samples_per_pixel() const { return samples_per_pixel; }
    constexpr void set_samples_per_pixel(ushort samples) { samples_per_pixel = samples; }

private:
    void initialize_pixel_deltas_and_location(); 
    Color ray_color(const Ray& ray, const HittableList& world, int depth);
    Ray get_ray(u_short i, u_short j) const;
};


