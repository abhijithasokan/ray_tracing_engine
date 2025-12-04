#include <raytracer/camera.h>

#include <iostream>
#include <omp.h>
#include <chrono>

#include <raytracer/common.h>
#include <raytracer/ray.h>
#include <raytracer/vec3.h>
#include <raytracer/color.h>
#include <raytracer/hittable.h>
#include <raytracer/material.h>
#include <raytracer/hittable_list.h>
#include <raytracer/rand_utils.h>


void Camera::initialize_camera_coordinate_system() {
    w = -unit_vector(look_at - look_from);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);
}

bool is_omp_enabled() {
    #ifdef _OPENMP
        return true;
    #else
        return false;
    #endif
}

void Camera::initialize_pixel_deltas_and_location() {
    auto viewport_u = cam_params.vp_width() * u;
    auto viewport_v = cam_params.vp_height() * -v;

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u / img_params.width();
    pixel_delta_v = viewport_v / img_params.height();

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = look_from - cam_params.focus_dist() * w - viewport_u/2 - viewport_v/2;
    pixel00_location = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    defocus_disk_u = u * cam_params.compute_defocus_radius();
    defocus_disk_v = v * cam_params.compute_defocus_radius();
}




Color Camera::ray_color(const Ray& ray, const HittableList& world, int depth) {
    if(depth <= 0) // when we exceed the ray bounce limit, we just return black
        return Color(0, 0, 0);

    // we add SURFACE_ACHNE_OFFSET to avoid hitting very close surfaces
    // which can be the case when the computed ray origin, due to floating point inaccuracies, 
    // lies exactly on/inside the surface
    auto hit_rec = world.hit(ray, Interval(0 + SURFACE_ACHNE_OFFSET, infinity));
    if(hit_rec) {
        auto scatter_info = hit_rec->mat_ptr->scatter(ray, *hit_rec);
        if(scatter_info) {
            auto [scattered_ray, attenuation] = *scatter_info;
            return attenuation * ray_color(scattered_ray, world, depth - 1);
        }
        return Color(0, 0, 0);
    }

    auto unit_vec = unit_vector(ray.get_direction());
    auto a = 0.5*(unit_vec.y() + 1.0);
    return (1.0-a)*Color(1.0, 1.0, 1.0) + a*Color(0.5, 0.7, 1.0);
}

Ray Camera::get_ray(u_short i, u_short j) const {
    auto offset_u = random_double(-0.5, 0.5);
    auto offset_v = random_double(-0.5, 0.5);

    auto pixel_location = pixel00_location + (i + offset_u)*pixel_delta_u + (j + offset_v)*pixel_delta_v;

    auto ray_origin = look_from;
    if(cam_params.compute_defocus_radius() > 0.0) 
        ray_origin += defocus_disk_sample();

    auto ray_start_time = random_double(0.0, 1.0); // for motion blur feature
    return Ray(ray_origin, pixel_location - ray_origin, ray_start_time);
}

void Camera::render_scene(const HittableList& world) {
    if(is_omp_enabled()) 
        std::clog << "Rendering with OpenMP using " << omp_get_max_threads() << " threads...\n";
    else
        std::clog << "Rendering without OpenMP...\n";

    

    std::vector<std::vector<Color>> framebuffer(img_params.height(), std::vector<Color>(img_params.width()));

    auto render_pixel = [&framebuffer, this, &world](u_short ii, u_short jj) {
        Color pixel_color(0, 0, 0);
        for(u_short sample_idx = 0; sample_idx < samples_per_pixel; ++sample_idx) {
            auto ray = get_ray(ii, jj);
            pixel_color += ray_color(ray, world, max_depth);
        } 
        pixel_color /= double(samples_per_pixel);
        framebuffer[jj][ii] = pixel_color;
    };

    auto start_time = std::chrono::high_resolution_clock::now();

    #pragma omp parallel for collapse(2) schedule(dynamic,1)
    for(u_short jj = 0; jj < img_params.height(); ++jj) {
        for(u_short ii = 0; ii < img_params.width(); ++ii) {
            render_pixel(ii, jj);
        }
    }


    auto end_time = std::chrono::high_resolution_clock::now();
    auto render_duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
    std::clog << "\nRender time: " << render_duration << " seconds.\n";

    std::cout << "P3\n" << img_params.width() << ' ' << img_params.height() << "\n255\n";
    for(u_short jj = 0; jj < img_params.height(); ++jj) {
        for(u_short ii = 0; ii < img_params.width(); ++ii) {
            write_color(std::cout, framebuffer[jj][ii]);
        }
    }
    std::clog << "\nDone.\n";
}


Camera Camera::create_camera(
    const Point& look_from, const Point& look_at, 
    double vpov, double defocus_angle, double focus_dist,
    const RenderImageParams& img_params
) {
    Vec3 vup(0, 1, 0); // "view up" vector
    double rr = (double(img_params.width()) / img_params.height());
    
    CameraIntrinsicParameters cam_params(focus_dist, vpov, defocus_angle, rr);
    Point origin(0, 0, 0);
    
    return Camera(look_from, look_at, vup, cam_params, img_params);
}


Vec3 Camera::defocus_disk_sample() const {
    auto rd = random_in_unit_disk();
    return rd.x() * defocus_disk_u + rd.y() * defocus_disk_v;
}