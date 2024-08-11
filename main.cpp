#include <opencv2/core.hpp>
#include <opencv4/opencv2/opencv.hpp>

using namespace cv;

int main() {
    // Image

    int image_width = 256;
    int image_height = 256;

    // Render

    auto image = new Mat(image_height, image_width, CV_8UC3);

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            image->at<Vec3b>(j, i) = Vec3b(ib, ig, ir);
        }
    }

    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", *image);

    waitKey(0);
}