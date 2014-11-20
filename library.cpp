#include <sstream>
#include <random>
#include "library.h"

std::string int_to_string(int x) {
    std::ostringstream ss;
    ss << x;
    return ss.str();
}

int rnd_gen(int min, int max) {
    static std::random_device rd;
    static std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> uni_dist(min, max);
    return uni_dist(generator);
}
