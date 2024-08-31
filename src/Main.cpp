#include "Color.hpp"
#include "Ray.hpp"
#include "Vec3.hpp"
#include <iostream>

using namespace cv;

bool hit_sphere(const Point3& center, double radius, const Ray& r) {
    Vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    return (discriminant >= 0);
}

Color ray_color(const Ray& r) {
    if (hit_sphere(Point3(0, 0, -1), 0.5, r)) {
        return Color(1, 0, 0);
    }

    Vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

// Image
auto aspect_ratio = 16.0 / 9.0;
int image_width = 400;

// Calculate the image height, and ensure that it's at least 1.
int ideal_image_height = static_cast<int>(image_width / aspect_ratio);
int image_height = (ideal_image_height < 1) ? 1 : ideal_image_height;

// Camera

auto focal_length = 1.0;
auto viewport_height = 2.0;
auto viewport_width = viewport_height * (double(image_width) / image_height);
auto camera_center = Point3(0, 0, 0);

// Calculate the vectors across the horizontal and down the vertical viewport edges.
auto viewport_u = Vec3(viewport_width, 0, 0);
auto viewport_v = Vec3(0, -viewport_height, 0);

// Calculate the horizontal and vertical delta vectors from pixel to pixel.
auto pixel_delta_u = viewport_u / image_width;
auto pixel_delta_v = viewport_v / image_height;

// Calculate the location of the upper left pixel.
auto viewport_upper_left = camera_center
    - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

void ppm_render() {
    std::cout << "P3\n"
              << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto pixel_direction = pixel_center - camera_center;
            Ray r(camera_center, pixel_direction);

            Color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}

void opencv_render() {
    Mat* image = new Mat(image_height, image_width, CV_8UC3);

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto pixel_direction = pixel_center - camera_center;
            Ray r(camera_center, pixel_direction);

            Color pixel_color = ray_color(r);
            write_color_to_cv(image, i, j, pixel_color);
        }
        namedWindow("Display Image", WINDOW_AUTOSIZE);
        imshow("Display Image", *image);
    }

    waitKey(0);
}

int main() {
    opencv_render();
}