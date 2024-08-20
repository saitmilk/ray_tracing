#include "Color.hpp"
#include <iostream>

using namespace cv;

// Image

int image_width = 256;
int image_height = 256;

void ppm_render() {
    std::cout << "P3\n"
              << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto pixel_color = Color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}

void opencv_render() {
    Mat* image = new Mat(image_height, image_width, CV_8UC3);

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            auto pixel_color = Color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0);
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