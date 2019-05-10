#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class Argparser {
public:
    Argparser(int argc, char** argv);

    double parse_k(double def_k);
    double parse_R(double def_R);
    size_t parse_win_size(size_t def_win_size);
    std::pair<std::string, std::string> parse_pathes();

private:
    const std::string get_option(const std::string& option) const;

    std::vector<std::string> tokens;
};