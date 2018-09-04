#include <algorithm>

#include "Optimizer.h"
#include "Random.h"

namespace learn {

GeneticOptimizer::GeneticOptimizer(const Problem &problem,
                                   size_t population_size)
    : problem_(problem.clone()),
      population_size_(population_size) {
    randomizePopulation();
}

void GeneticOptimizer::optimize() {
    terminateWorst();
    addRandom();
    mixGenes();
    rankPopulation();
}

void GeneticOptimizer::optimize(size_t n_iters) {
    for (size_t i = 0; i < n_iters; i++)
        optimize();
}

Genome GeneticOptimizer::currentBest() const {
    return population_.front().first;
}

double GeneticOptimizer::currentBestScore() const {
    return population_.front().second;
}

void GeneticOptimizer::randomizePopulation() {
    population_.clear();
    population_.reserve(population_size_);

    GenomeSpec spec = problem_->getSpec();
    for (size_t i = 0; i < population_size_; i++) {
        population_.emplace_back(spec.getRandomGenome(), 0);
    }
}

void GeneticOptimizer::terminateWorst() {
    population_.resize(population_size_ * 0.5);
}

void GeneticOptimizer::addRandom() {
    size_t n_rand = (population_size_ - population_.size()) / 2;

    GenomeSpec spec = problem_->getSpec();
    for (size_t i = 0; i < n_rand; i++) {
        population_.emplace_back(spec.getRandomGenome(), 0);
    }
}

void GeneticOptimizer::mixGenes() {
    UniformGenerator gen;
    GenomeSpec spec = problem_->getSpec();
    while (population_.size() != population_size_) {
        size_t first = gen.getSize(0, population_.size() - 1);
        size_t second = gen.getSize(0, population_.size() - 1);

        population_.emplace_back(spec.mixGenes(
            population_[first].first, population_[second].first
        ), 0);
    }
}

void GeneticOptimizer::rankPopulation() {
    size_t pop_size = population_.size();
    #pragma omp parallel for schedule(dynamic)
    for (size_t i = 0; i < pop_size; i++) {
        population_[i].second = problem_->evalScore(population_[i].first);
    }
    
    std::sort(population_.begin(), population_.end(),
              [](const std::pair<Genome, double> &a, const std::pair<Genome, double> &b) {
        return a.second > b.second;
    });
}


}