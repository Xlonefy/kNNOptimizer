#ifndef LEARN_INCLUDE_RANDOM_H_
#define LEARN_INCLUDE_RANDOM_H_

#include <random>

namespace learn {

class UniformGenerator {
public:
    UniformGenerator();
    size_t getSize(size_t min, size_t max) const;
    int getInt(int min, int max) const;
    double getDouble(double min, double max) const;
    void reSeed() const;
private:
    using rng_type = std::mt19937_64;
    mutable rng_type rng_;
};

}


#endif /* LEARN_INCLUDE_RANDOM_H_ */