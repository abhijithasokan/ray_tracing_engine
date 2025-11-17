#include <raytracer/common.h>
#include <raytracer/vec3.h>
#include <raytracer/hittable.h>
#include <raytracer/hittable_list.h>
#include <raytracer/sphere.h>
#include <raytracer/camera.h>


int main() {
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    
    auto camera = Camera::create_default_camera(RenderImageParams(image_width, aspect_ratio));
    camera.set_samples_per_pixel(10);
    // World
    HittableList world;
    world.add(make_shared<Sphere>(Point(0,0,-1), 0.5));
    world.add(make_shared<Sphere>(Point(0,-100.5, -1), 100));

    // Render
    camera.render_scene(world);
    return 0;
}