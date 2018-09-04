#include "Random.h"

namespace learn {

UniformGenerator::UniformGenerator() {
    reSeed();
}

size_t UniformGenerator::getSize(size_t min, size_t max) const {
    std::uniform_int_distribution<size_t> dist(min, max);
    return dist(rng_);
}

int UniformGenerator::getInt(int min, int max) const {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng_);
}

double UniformGenerator::getDouble(double min, double max) const {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(rng_);
}

void UniformGenerator::reSeed() const {
    std::random_device rd;
    rng_.seed(rd());
}

}