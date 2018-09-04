#include <iostream>
#include <utility>

#include "Reader.h"
#include "Classifier.h"
#include "Config.h"
#include "Genetics.h"
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

    // CrossValidator validator;
    // Genome g;
    // g.getKey<size_t>("num_neighbors") = 27;
    // KNNClassifier knn(g);
    // knn.fitData(data);
    // std::cout << "Cross validation score: " << 
    //              validator.crossValidationScore(knn, data) <<
    //              "\n";

    // KNNOptimumParam problem(data);
    // GenomeSpec spec = problem.getSpec();
    // std::vector<std::pair<Genome, double>> gs;
    // UniformGenerator rng;
    // for (size_t i = 0; i < 5; i++)
    //     gs.emplace_back(spec.getRandomGenome(), rng.getDouble(-5, 5));


    // std::cout << std::boolalpha <<
    //              std::is_move_assignable<Genome>::value << "\n" <<
    //              std::is_move_constructible<Genome>::value << "\n"; 

    // std::pair<Genome, double> g1 = {spec.getRandomGenome(), 0.5};
    // std::pair<Genome, double> g2 = {spec.getRandomGenome(), 1.0};
    // std::swap(*gs.begin(), *(gs.begin() + 1));

    // std::sort(gs.begin(), gs.end(), [](const std::pair<Genome, double> &a, const std::pair<Genome, double> &b) {
    //     return a.second < b.second;
    // });

    // for (const auto &i : gs) {
    //     printGenome(i.first);
    //     std::cout << i.second << ";\n";
    // }

    // std::cout << "Cross validation score: " << 
    //              problem.evalScore(genome) <<
    //              "\n";

    // std::cout << "{\n";
    // std::cout << "  " << genome.getKey<size_t>("p-norm") << ";\n";
    // std::cout << "  " << genome.getKey<size_t>("n_neighbors") << ";\n";
    // std::cout << "  " << genome.getKey<std::vector<double>>("column_weights") << ";\n";
    // std::cout << "};\n";

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