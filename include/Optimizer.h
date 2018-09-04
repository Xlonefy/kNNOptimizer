#ifndef LEARN_INCLUDE_OPTIMIZER_H_
#define LEARN_INCLUDE_OPTIMIZER_H_

#include <vector>
#include <memory>
#include <utility>

#include "Problem.h"
#include "Genetics.hpp"

namespace learn {

class Optimizer {
public:
    virtual void optimize() = 0;
    virtual void optimize(size_t n_iters) = 0;
    virtual Genome currentBest() const = 0;
    virtual double currentBestScore() const = 0;
};

class GeneticOptimizer : public Optimizer {
public:
    GeneticOptimizer(const Problem &problem, size_t population_size = 100);
    void optimize();
    void optimize(size_t n_iters);
    Genome currentBest() const;
    double currentBestScore() const;
private:
    void randomizePopulation();
    void terminateWorst();
    void addRandom();
    void mixGenes();
    void rankPopulation();

    std::unique_ptr<Problem> problem_;
    size_t population_size_;
    std::vector<std::pair<Genome, double>> population_;
};

}

#endif /* LEARN_INCLUDE_OPTIMIZER_H_ */