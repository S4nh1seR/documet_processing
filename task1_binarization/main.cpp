#include <chrono>

#include "argparser.h"
#include "binarizer.h"

const double def_k = 0.15;
const double def_R = 128;
const size_t def_win_size = 20;

int main(int argc, char** argv) {
    Argparser parser(argc, argv);

    std::pair<std::string, std::string> pathes = parser.parse_pathes();
    std::string img_path = pathes.first;
    std::string out_path = pathes.second;
    double k = parser.parse_k(def_k);
    double R = parser.parse_R(def_R);
    size_t win_size = parser.parse_win_size(def_win_size);

    cv::Mat img = cv::imread(img_path, cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cout <<  "Could not open or find the image" << std::endl;
    }

    SauvolaBinarizer binarizer;

    auto start = std::chrono::high_resolution_clock::now();
    binarizer.Binarize(img, out_path, win_size, k, R);
    auto end = std::chrono::high_resolution_clock::now();

    double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
    double speed = (time_taken * 1e+6) / (img.cols * img.rows);
    std::cout << "speed: " << speed << " sec / m_pix" << std::endl;

    return 0;
}