#ifndef COLOR_H
#define COLOR_H

#include "Interval.hpp"
#include "Vec3.hpp"
#include <opencv2/core.hpp>
#include <opencv4/opencv2/opencv.hpp>

using namespace cv;

using Color = Vec3;

inline double linear_to_gamma(double linear_component) {
    if (linear_component > 0)
        return std::sqrt(linear_component);

    return 0;
}

inline void write_color(std::ostream& out, const Color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Apply a linear to gamma transform for gamma 2
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    // Translate the [0,1] component values to the byte range [0,255].
    static const Interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

inline void write_color_to_cv(Mat* image, int x, int y, const Color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);
    static const Interval intensity(0.000, 0.999);
    int ir = int(256 * intensity.clamp(r));
    int ig = int(256 * intensity.clamp(g));
    int ib = int(256 * intensity.clamp(b));

    image->at<Vec3b>(y, x) = Vec3b(ib, ig, ir);
}

#endif