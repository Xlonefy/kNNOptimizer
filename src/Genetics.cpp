#include <utility>
#include <unordered_set>

#include "Genetics.h"

namespace learn {
Genome::~Genome() {}

Genome::Genome(const Genome &g) : value_store_(g.value_store_) {}

bool Genome::hasKey(const std::string &key) const {
    return value_store_.count(key);
}

void Genome::swap(Genome &other) {
    value_store_.swap(other.value_store_);
}

void swap(Genome &g1, Genome &g2) {
    g1.swap(g2);
}

Variable::Variable(const std::string &name) : name_(name) {}

const std::string &Variable::getName() const{
    return name_;
}

SizeVar::SizeVar(size_t min, size_t max, const std::string &name)
    : Variable(name), min_(min), max_(max) {}

void SizeVar::getRandomValue(Genome &genome) const {
    genome.getKey<size_t>(getName()) = rng_.getSize(min_, max_);
}

void SizeVar::mixVariables(Genome &g1, const Genome &g2) const {
    if (rng_.getInt(0, 1)) 
        g1.getKey<size_t>(getName()) = g2.getKey<size_t>(getName());
}

SizeVar *SizeVar::clone() const {
    return new SizeVar(*this);
}

IntVar::IntVar(int min, int max, const std::string &name)
    : Variable(name), min_(min), max_(max) {}

void IntVar::getRandomValue(Genome &genome) const {
    genome.getKey<int>(getName()) = rng_.getInt(min_, max_);
}

void IntVar::mixVariables(Genome &g1, const Genome &g2) const {
    if (rng_.getInt(0, 1)) 
        g1.getKey<int>(getName()) = g2.getKey<int>(getName());
}

IntVar *IntVar::clone() const {
    return new IntVar(*this);
}

DoubleVar::DoubleVar(double min, double max, const std::string &name)
    : Variable(name), min_(min), max_(max) {}

void DoubleVar::getRandomValue(Genome &genome) const {
    genome.getKey<double>(getName()) = rng_.getDouble(min_, max_);
}

void DoubleVar::mixVariables(Genome &g1, const Genome &g2) const {
    if (rng_.getInt(0, 1)) 
        g1.getKey<double>(getName()) = g2.getKey<double>(getName());
}

DoubleVar *DoubleVar::clone() const {
    return new DoubleVar(*this);
}

DoubleVectorVar::DoubleVectorVar(double min, double max, size_t size,
                                 const std::string &name)
    : Variable(name), min_(min), max_(max), size_(size) {}

void DoubleVectorVar::getRandomValue(Genome &genome) const {
    std::vector<double> vec;
    vec.reserve(size_);
    for (size_t i = 0; i < size_; i++)
        vec.push_back(rng_.getDouble(min_, max_));

    genome.getKey<std::vector<double>>(getName()) = vec;
}

void DoubleVectorVar::mixVariables(Genome &g1, const Genome &g2) const {
    auto &vec1 = g1.getKey<std::vector<double>>(getName());
    const auto &vec2 = g2.getKey<std::vector<double>>(getName());
    
    for (size_t i = 0; i < vec1.size(); i++) {
        switch (rng_.getInt(0, 2)) {
        case 0:
            vec1[i] = (vec1[i] + vec2[i]) / 2.0;
            break;
        case 1:
            vec1[i] = vec2[i];
        case 2:
            break;
        }
    }
}

DoubleVectorVar *DoubleVectorVar::clone() const {
    return new DoubleVectorVar(*this);
}

}