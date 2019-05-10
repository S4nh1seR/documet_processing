#include "argparser.h"

Argparser::Argparser(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        this->tokens.push_back(std::string(argv[i]));
    }
}

const std::string Argparser::get_option(const std::string& option) const{
    auto itr = std::find(tokens.begin(), tokens.end(), option);
    if (itr != tokens.end() && ++itr != tokens.end()) {
        return *itr;
    }
    return "";
}

double Argparser::parse_k(double def_k) {
    std::string k_arg = get_option("-k");
    return (!k_arg.empty()) ? std::stod(k_arg) : def_k;
}

double Argparser::parse_R(double def_R) {
    std::string R_arg = get_option("-R");
    return (!R_arg.empty()) ? std::stod(R_arg) : def_R;
}

size_t Argparser::parse_win_size(size_t def_win_size) {
    std::string win_size_arg = get_option("-ws");
    return (!win_size_arg.empty()) ? std::stoi(win_size_arg) : def_win_size;
}

std::pair<std::string, std::string> Argparser::parse_pathes() {
    std::string img_path = get_option("-in");
    if (img_path.empty()) {
        std::cout << "Введите путь в системе до изображения!" << std::endl;
        std::cin >> img_path;
    }

    size_t found = img_path.find_last_of("/");
    std::string folder_path = img_path.substr(0, found);
    std::string image_filename = img_path.substr(found + 1);
    image_filename = image_filename.substr(0, image_filename.find_last_of("."));

    std::string out_dir = get_option("-out");
    if (out_dir.empty()) {
        out_dir = folder_path;
    }
    std::string out_path = out_dir + "/" + image_filename + ".png";
    return std::make_pair(img_path, out_path);
};
