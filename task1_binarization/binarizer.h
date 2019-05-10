#pragma once

#include <iostream>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>


class SauvolaBinarizer {
public:
    bool Binarize(const cv::Mat& img, const std::string& out_path, size_t win_size_, double k, double R);

private:
    void SauvolaAlgo(cv::Mat& res_img, double k, double R);

    void save_image(cv::Mat& image, const std::string& out_path);
    void make_black(cv::Mat& image, size_t x, size_t y);
    void make_white(cv::Mat& image, size_t x, size_t y);

    void perform_thresholding(cv::Mat& res_img, size_t x_win_num, size_t y_win_num, double k, double R);
    double cnt_win_mean(size_t start_x, size_t start_y, size_t win_width, size_t win_height);
    double cnt_win_var(size_t start_x, size_t start_y, size_t win_width, size_t win_height, double mean);


    size_t win_size;
    size_t height;
    size_t width;

    cv::Mat gray_img;
};