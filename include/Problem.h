#ifndef LEARN_INCLUDE_PROBLEM_H_
#define LEARN_INCLUDE_PROBLEM_H_

#include "Data.h"
#include "Genetics.hpp"

namespace learn {

class Problem {
public:
    virtual ~Problem() = default;
    virtual double evalScore(const Genome &genome) const = 0;
    virtual GenomeSpec getSpec() const = 0;
    virtual Problem *clone() const = 0;
};

class KNNOptimumParam : public Problem {
public:
    KNNOptimumParam(const DataSet &data);
    double evalScore(const Genome &genome) const;
    GenomeSpec getSpec() const;
    KNNOptimumParam *clone() const;
private:
    DataSet data_;
    size_t num_dims_;
};

}

#endif /* LEARN_INCLUDE_PROBLEM_H_ */