#include <raytracer/camera.h>

#include <iostream>
#include <raytracer/common.h>
#include <raytracer/ray.h>
#include <raytracer/vec3.h>
#include <raytracer/color.h>
#include <raytracer/hittable.h>
#include <raytracer/hittable_list.h>


void Camera::initialize_pixel_deltas_and_location() {
    auto viewport_u = Vec3(cam_params.vp_width(), 0, 0);
    auto viewport_v = Vec3(0, -cam_params.vp_height(), 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u / img_params.width();
    pixel_delta_v = viewport_v / img_params.height();

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = origin - Vec3(0, 0, cam_params.focal_length()) - viewport_u/2 - viewport_v/2;
    pixel00_location = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}




Color Camera::ray_color(const Ray& ray, const HittableList& world) {
    auto hit_rec = world.hit(ray, Interval(0, infinity));
    if(hit_rec) {
        return 0.5 * (hit_rec->normal + Color(1, 1, 1));
    }

    auto unit_vec = unit_vector(ray.get_direction());
    auto a = 0.5*(unit_vec.y() + 1.0);
    return (1.0-a)*Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0);
}


void Camera::render_scene(const HittableList& world) {
    std::cout << "P3\n" << img_params.width() << ' ' << img_params.height() << "\n255\n";
    for(u_short j = 0; j < img_params.height(); ++j) {
        std::clog << "\rScanlines remaining: " << (img_params.height() - j) << ' ' << std::flush;
        for(u_short i = 0; i < img_params.width(); ++i) {
            auto pixel_center = pixel00_location + (i * pixel_delta_u) + (j * pixel_delta_v);
            Ray ray(origin, pixel_center - origin);
            Color pixel_color = ray_color(ray, world);

            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\nDone.\n";
}


Camera Camera::create_default_camera(const RenderImageParams& img_params) {
    double focal_length = 1.0;
    double vp_height = 2.0;
    double vp_width = vp_height * (double(img_params.width()) / img_params.height());
    
    CameraIntrinsicParameters cam_params(focal_length, vp_width, vp_height);
    Point origin(0, 0, 0);
    
    return Camera(origin, cam_params, img_params);
}
