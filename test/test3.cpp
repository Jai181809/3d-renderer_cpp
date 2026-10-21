#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <cstdint>
#include <omp.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../src/stb_image_write.h"

#include "../objects/ob.hpp"
#include "../raytracer/hittable_list.hpp"
#include "../header_files.hpp"

using namespace std;

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
    int samples_per_pixel = 100;
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

    void render(const string& png_path) {
        clog << "Rendering initialization started...\n";
        auto start_init = chrono::high_resolution_clock::now();
        initialize();

        world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
        world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
        world.add(make_shared<triangle>(point3(0, 0, -5), point3(4, 0, -5), point3(0, 4, -3)));

        // 1. Allocate in-memory pixel buffer
        vector<colour> framebuffer(Im_width * Im_height);

        auto end_init = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed_init = end_init - start_init;
        double init_seconds = elapsed_init.count();

        clog << "Rendering started [" << Im_width << "x" << Im_height 
            << " | " << samples_per_pixel << " spp]...\n";

        // 2. High-precision timer starts
        auto start_render = chrono::high_resolution_clock::now();

        // --- Core ray-tracing calculation (NO DISK I/O) ---
        #pragma omp parallel for schedule(dynamic, 1)
        for (int j = 0; j < Im_height; j++) {
            for (int i = 0; i < Im_width; i++) {
                colour pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, world);
                }
                framebuffer[j * Im_width + i] = pixel_samples_scale * pixel_color;
            }
        }

        auto end_render = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed_render = end_render - start_render;
        double render_seconds = elapsed_render.count();

        // 3. Performance metrics
        uint64_t total_rays = static_cast<uint64_t>(Im_width) * Im_height * samples_per_pixel;
        double mrays_per_sec = (total_rays / 1'000'000.0) / render_seconds;
        double pixels_per_sec = (Im_width * Im_height) / render_seconds;

        // 4. Direct in-memory PNG encoding and write
        clog << "Writing direct PNG to: " << png_path << "...\n";
        auto start_png = chrono::high_resolution_clock::now();

        vector<uint8_t> byte_buffer(Im_width * Im_height * 3);
        static const interval intensity(0.000, 0.999);
        size_t idx = 0;

        for (const auto& pixel : framebuffer) {
            byte_buffer[idx++] = static_cast<uint8_t>(256 * intensity.clamp(pixel.x()));
            byte_buffer[idx++] = static_cast<uint8_t>(256 * intensity.clamp(pixel.y()));
            byte_buffer[idx++] = static_cast<uint8_t>(256 * intensity.clamp(pixel.z()));
        }

        int stride_bytes = Im_width * 3;
        int success = stbi_write_png(png_path.c_str(), Im_width, Im_height, 3, byte_buffer.data(), stride_bytes);

        auto end_png = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed_png = end_png - start_png;
        double png_seconds = elapsed_png.count();

        if (!success) {
            cerr << "Error: Failed to write PNG image to " << png_path << "\n";
            return;
        }

        clog << "Done.\n";
        clog << "\n================ Benchmark Results ================\n";
        clog << "Render initialization time : " << init_seconds << " seconds\n";
        clog << "Pure Render loop Time      : " << render_seconds << " seconds\n";
        clog << "Direct PNG write time      : " << png_seconds << " seconds\n";
        clog << "Throughput                 : " << pixels_per_sec << " pixels/sec\n";
        clog << "Primary Ray Rate           : " << mrays_per_sec << " MRays/sec\n";
        clog << "===================================================\n\n";
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

int main() {
    camera cl;
    cl.render("image3.png");
    return 0;
}