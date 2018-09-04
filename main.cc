#include <iostream>
#include <utility>

#include "Reader.h"
#include "Classifier.h"
#include "Genetics.hpp"
#include "Problem.h"
#include "Optimizer.h"

using namespace learn;

std::ostream &operator<<(std::ostream &os, const std::vector<double> &vec) {
    os << "{ ";
    for (auto i : vec)
        os << i << " ";
    os << "}";
    return os;
}

void printGenome(const Genome &genome) {
    std::cout << "{\n";
    std::cout << "  " << genome.getKey<size_t>("p-norm") << ";\n";
    std::cout << "  " << genome.getKey<size_t>("n_neighbors") << ";\n";
    std::cout << "  " << genome.getKey<std::vector<double>>("column_weights") << ";\n";
    std::cout << "};\n";
}

int main() {
    CSVReader csv;
    DataSet data = csv.parseFile("filtered_data.csv");

    KNNOptimumParam problem(data);
    GeneticOptimizer optimizer(problem, 500);
    for (size_t i = 0; i < 10; i++) {
        optimizer.optimize();
        std::cout << "Cross validation score: " << 
                    optimizer.currentBestScore() <<
                    "\n";

        Genome genome = optimizer.currentBest();
        printGenome(genome);
    }
    return 0;
    char c;
    std::cin >> c;
}