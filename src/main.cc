#include <raytracer/common.h>
#include <raytracer/vec3.h>
#include <raytracer/hittable.h>
#include <raytracer/hittable_list.h>
#include <raytracer/sphere.h>
#include <raytracer/camera.h>
#include <raytracer/material.h>



int main() {
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    
    auto camera = Camera::create_default_camera(RenderImageParams(image_width, aspect_ratio));
    camera.set_samples_per_pixel(10);
    // World
    HittableList world;
    auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.3);
    auto material_right  = make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    world.add(make_shared<Sphere>(Point( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<Sphere>(Point( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(make_shared<Sphere>(Point(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<Sphere>(Point( 1.0,    0.0, -1.0),   0.5, material_right));

    // Render
    camera.render_scene(world);
    return 0;
}