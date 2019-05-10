#include "binarizer.h"

bool SauvolaBinarizer::Binarize(const cv::Mat& img, const std::string& out_path, size_t win_size_, double k, double R) {
    win_size = win_size_;
    width = img.cols;
    height = img.rows;

    cv::Mat result_img = cv::Mat::zeros(cv::Size(img.cols, img.rows), CV_8UC3);;
    cv::cvtColor(img, gray_img, cv::COLOR_BGR2GRAY);

    SauvolaAlgo(result_img, k, R);
    save_image(result_img, out_path);
}

void SauvolaBinarizer::SauvolaAlgo(cv::Mat& res_img, double k, double R) {
    size_t hor_max_num = width / win_size + (width % win_size == 0);
    size_t ver_max_num = height / win_size + (height % win_size == 0);

    for (size_t hor_num = 0; hor_num < hor_max_num; ++hor_num) {
        for (size_t ver_num = 0; ver_num < ver_max_num; ++ver_num) {
            perform_thresholding(res_img, hor_num, ver_num, k, R);
        }
    }

}
void SauvolaBinarizer::perform_thresholding(cv::Mat& res_img, size_t x_win_num, size_t y_win_num, double k, double R) {
    size_t start_x = x_win_num * win_size;
    size_t start_y = y_win_num * win_size;
    size_t win_width = (width - start_x >= win_size) ? win_size : width - start_x;
    size_t win_height = (height - start_y >= win_size) ? win_size : height - start_y;

    double mean = cnt_win_mean(start_x, start_y, win_width, win_height);
    double var = cnt_win_var(start_x, start_y, win_width, win_height, mean);

    double threshold = mean * (1 + k * (var / R - 1));
    for (size_t i = start_x; i < (start_x + win_width); ++i) {
        for (size_t j = start_y; j < (start_y + win_height); ++j) {
            if (gray_img.at<uchar>(j, i) > threshold) {
                make_white(res_img, i, j);
            } else {
                make_black(res_img, i, j);
            }
        }
    }
}

double SauvolaBinarizer::cnt_win_mean(size_t start_x, size_t start_y, size_t win_width, size_t win_height) {
    double sum = 0;
    for (size_t i = start_x; i < (start_x + win_width); ++i) {
        for (size_t j = start_y; j < (start_y + win_height); ++j) {
            sum += gray_img.at<uchar>(j, i);
        }
    }
    return sum / (win_width * win_height);
}

double SauvolaBinarizer::cnt_win_var(size_t start_x, size_t start_y, size_t win_width, size_t win_height, double mean) {
    double sq_sum = 0;
    for (size_t i = start_x; i < (start_x + win_width); ++i) {
        for (size_t j = start_y; j < (start_y + win_height); ++j) {
            sq_sum += std::pow((gray_img.at<uchar>(j, i) - mean), 2);
        }
    }
    return std::sqrt(sq_sum / (win_width * win_height));
}

void SauvolaBinarizer::make_black(cv::Mat& image, size_t x, size_t y) {
    image.at<cv::Vec3b>(y, x)[0] = 0;
    image.at<cv::Vec3b>(y, x)[1] = 0;
    image.at<cv::Vec3b>(y, x)[2] = 0;
}

void SauvolaBinarizer::make_white(cv::Mat& image, size_t x, size_t y) {
    image.at<cv::Vec3b>(y, x)[0] = 255;
    image.at<cv::Vec3b>(y, x)[1] = 255;
    image.at<cv::Vec3b>(y, x)[2] = 255;
}

void SauvolaBinarizer::save_image(cv::Mat& img, const std::string& out_path) {
    std::vector<int> compression_params;
    compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);

    cv::imwrite(out_path, img, compression_params);
}
