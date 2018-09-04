#include <cmath>
#include <functional>
#include <array>
#include <utility>

#include "Vector.h"

namespace learn {

LNNorm::LNNorm(int n) : n_(n) {}

double LNNorm::operator()(const Vector &vec) const {
    // TODO(Xlonefy): Hum... Do I need to say anything?
    switch (n_) {
    case 1:
        return vec.data_.lpNorm<1>();
    case 2:
        return vec.data_.norm();
    case 3:
        return vec.data_.lpNorm<3>();
    }

    double sum = 0.0;
    for (size_t i = 0; i < vec.len(); i++)
        sum += pow(vec[i], n_);
    
    return pow(sum, 1.0 / n_);
}

}