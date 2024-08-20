#ifndef COLOR_H
#define COLOR_H

#include "Vec3.hpp"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv4/opencv2/opencv.hpp>

using namespace cv;

using Color = Vec3;

inline void write_color(std::ostream& out, const Color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

inline void write_color_to_cv(Mat* image, int x, int y, const Color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();
    int ir = int(255.999 * r);
    int ig = int(255.999 * g);
    int ib = int(255.999 * b);

    image->at<Vec3b>(y, x) = Vec3b(ib, ig, ir);
}

#endif