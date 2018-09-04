#ifndef LEARN_INCLUDE_VECTOR_H_
#define LEARN_INCLUDE_VECTOR_H_

#include <vector>
#include <Eigen/Dense>

namespace learn {

class Vector {
public:
    Vector(size_t size, double default_value = 0.0);
    Vector(const std::vector<double> &vals);
    Vector(const Eigen::VectorXd &data);
    Vector operator-(const Vector &v) const;
    Vector operator+(const Vector &v) const;
    Vector operator*(const Vector &v) const;
    double &operator[](size_t idx);
    double operator[](size_t idx) const;
    double dot(const Vector &v) const; 
    size_t len() const;
    friend class LNNorm;
private:
    Eigen::VectorXd data_;
};

class LNNorm {
public:
    LNNorm(int n = 2);
    double operator()(const Vector &vec) const;
private:
    int n_;
};

}

#endif /* LEARN_INCLUDE_VECTOR_H_ */