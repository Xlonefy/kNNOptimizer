#include "Vector.h"

namespace learn {

Vector::Vector(size_t size, double default_value) : data_(size) {
    for (size_t i = 0; i < size; i++)
        data_[i] = default_value; 
}

Vector::Vector(const std::vector<double> &vals) : data_(vals.size()) {
    for (size_t i = 0; i < vals.size(); i++)
        data_[i] = vals[i]; 
}

Vector::Vector(const Eigen::VectorXd &data) : data_(data) {}

Vector Vector::operator-(const Vector &v) const {
    return Vector(v.data_ - data_);
}

Vector Vector::operator+(const Vector &v) const {
    return Vector(v.data_ + data_);
}

Vector Vector::operator*(const Vector &v) const {
    return Vector(v.data_.array() * data_.array());
}

double &Vector::operator[](size_t idx) {
    return data_[idx];
}

double Vector::operator[](size_t idx) const {
    return data_[idx];
}

double Vector::dot(const Vector &v) const {
    return data_.dot(v.data_);
}

size_t Vector::len() const {
    return data_.size();
}

}