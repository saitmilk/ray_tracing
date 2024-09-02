#include "Color.hpp"
#include "Hittable.hpp"
#include "HittableList.hpp"
#include "Interval.hpp"
#include "Rtweekend.hpp"
#include "Sphere.hpp"
#include <memory>

using namespace cv;
using std::make_shared;

bool isOpencvRender = true;

Color ray_color(const Ray& r, const Hittable& world) {
    HitRecord rec;
    if (world.hit(r, Interval(0, infinity), rec)) {
        return 0.5 * (rec.normal + Color(1, 1, 1));
    }

    Vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main() {
    // Image
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int ideal_image_height = static_cast<int>(image_width / aspect_ratio);
    int image_height = (ideal_image_height < 1) ? 1 : ideal_image_height;

    // World

    auto world = HittableList(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

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

    if (isOpencvRender) {
        Mat* image = new Mat(image_height, image_width, CV_8UC3);

        for (int j = 0; j < image_height; j++) {
            for (int i = 0; i < image_width; i++) {
                auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                auto pixel_direction = pixel_center - camera_center;
                Ray r(camera_center, pixel_direction);

                Color pixel_color = ray_color(r, world);
                write_color_to_cv(image, i, j, pixel_color);
            }
            namedWindow("Display Image", WINDOW_AUTOSIZE);
            imshow("Display Image", *image);
        }

        waitKey(0);
    } else {
        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                auto pixel_direction = pixel_center - camera_center;
                Ray r(camera_center, pixel_direction);

                Color pixel_color = ray_color(r, world);
                write_color(std::cout, pixel_color);
            }
        }

        std::clog << "\rDone.                 \n";
    }
}