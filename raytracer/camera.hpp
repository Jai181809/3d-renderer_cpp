#pragma once

#include <fstream>
#include "objects/ob.hpp"
#include "hittable_list.hpp"
#include "header_files.hpp"

colour ray_color(const ray& r, const hittable& objects) {
    hit_record rec;

    // object hitting
    if (objects.hit(r, interval(0, infinity), rec)) {
        return 0.5 * (rec.normal + colour(1, 1, 1));
    }

    vec3 unit_direction = unit(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * colour(1.0, 1.0, 1.0) + a * colour(0.5, 0.7, 1.0);
}

class camera {
public: 
    // Image definitions
    double aspect_ratio = 16.0 / 9.0;
    int Im_width = 1200;
    int samples_per_pixel = 10;
    vec3 camera_center = point3(0, 0, 0); // Camera position
    double focal_length = 1.0;

    void initialize() {
        Im_height = int(Im_width / aspect_ratio);
        Im_height = (Im_height < 1) ? 1 : Im_height;

        pixel_samples_scale = 1.0 / samples_per_pixel;

        viewport_height = 2.0;
        viewport_width = viewport_height * (double(Im_width) / Im_height);

        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        delta_u = viewport_u / Im_width;
        delta_v = viewport_v / Im_height;

        auto viewport_upperleft = camera_center - vec3(0, 0, focal_length) - (viewport_v / 2) - (viewport_u / 2);
        pixel_0_0 = viewport_upperleft + (delta_u + delta_v) / 2;
    }

    ray get_ray(int i, int j) const {
        auto offset = sample_square();
        auto pixel_sample = pixel_0_0
                          + ((i + offset.x()) * delta_u)
                          + ((j + offset.y()) * delta_v);

        auto ray_origin = camera_center;
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const {
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    void render(string path) {
        initialize();

        world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
        world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
        world.add(make_shared<triangle>(point3(0, 0, -5), point3(4, 0, -5), point3(0, 4, -3)));

        ofstream File(path);
        File << "P3\n" << Im_width << " " << Im_height << "\n255\n";

        for (int j = 0; j < Im_height; j++) {
            clog << "\rScanlines remaining: " << (Im_height - j) << ' ' << flush;
            for (int i = 0; i < Im_width; i++) {
                colour pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, world);
                }
                write_color(File, pixel_samples_scale * pixel_color);
            }
        }
        File.close();
        clog << "\rDone.                 \n";
    }

private:
    int Im_height;
    double viewport_height;
    double viewport_width;
    double pixel_samples_scale;
    vec3 pixel_0_0;
    vec3 delta_u;
    vec3 delta_v;
    hittable_list world;
};