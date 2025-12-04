#include <raytracer/common.h>
#include <raytracer/vec3.h>
#include <raytracer/hittable.h>
#include <raytracer/hittable_list.h>
#include <raytracer/sphere.h>
#include <raytracer/camera.h>
#include <raytracer/material.h>
#include <raytracer/rand_utils.h>



void scene_3_spheres() {
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    Point look_from(-2, 2, 1);
    Point look_at(0, 0, -1);
    double vpov = 20.0; // vertical point of view in degrees
    double defocus_angle = 10.0; // in degrees
    double focus_dist = 3.4;
    
    auto camera = Camera::create_camera(
        look_from, 
        look_at,
        vpov, defocus_angle, focus_dist,
        RenderImageParams(image_width, aspect_ratio)
    );

    camera.set_samples_per_pixel(10);
    
    // World
    HittableList world;
    auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<Dielectric>(1.50);
    auto material_bubble = make_shared<Dielectric>(1.00 / 1.50);
    auto material_right  = make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    world.add(make_shared<Sphere>(Point( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<Sphere>(Point( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(make_shared<Sphere>(Point(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<Sphere>(Point(-1.0,    0.0, -1.0),   0.4, material_bubble));
    world.add(make_shared<Sphere>(Point( 1.0,    0.0, -1.0),   0.5, material_right));
    
    
    // Render
    camera.render_scene(world);
}

void scene_from_book(bool test_moving_spheres = true) {
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 600;
    Point look_from(13, 2 ,3);
    Point look_at(0, 0, 0);
    double vpov = 20.0; // vertical point of view in degrees
    double defocus_angle = 0.6; // in degrees
    double focus_dist = 10.0;
    
    auto camera = Camera::create_camera(
        look_from, 
        look_at,
        vpov, defocus_angle, focus_dist,
        RenderImageParams(image_width, aspect_ratio)
    );

    camera.set_samples_per_pixel(10);
    

    // World
    HittableList world;

    auto ground_material = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(Point(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            Point center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - Point(4, 0.2, 0)).len() > 0.9) {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    sphere_material = make_shared<Lambertian>(albedo);

                    if(test_moving_spheres) {
                        auto center2 = center + Vec3(0, random_double(0,.5), 0); // vertical movement
                        world.add(make_shared<MovingSphere>(center, center2, 0.2, sphere_material));
                    }
                    else {
                        world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                    }
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(Point(0, 1, 0), 1.0, material1));
    auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(Point(-4, 1, 0), 1.0, material2));
    auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(Point(4, 1, 0), 1.0, material3));


    // Render
    camera.render_scene(world);
}


int main() {
    scene_from_book();
    // scene_3_spheres();
    return 0;
}