#include "Classifier.h"

namespace learn {

Classifier::Classifier() {}

void Classifier::fitData(const DataSet &data) {
    fitted_ = data;
}

const DataSet &Classifier::getFittedData() const {
    return fitted_;
}

CrossValidator::CrossValidator(size_t num_iters, double percent_test) 
    : num_iters_(num_iters), percent_test_(percent_test) {}

double CrossValidator::crossValidationScore(Classifier &classifier,
                                                const DataSet &data) const {
    double sum = 0.0;
    for (size_t i = 0; i < num_iters_; i++) {
        sum += crossValidationIteration(classifier, data);
    }
    return sum / num_iters_;
}

double CrossValidator::crossValidationIteration(Classifier &classifier,
                                                DataSet data) const {
    // prepares test data
    size_t n_test = static_cast<size_t>(data.size() * percent_test_);
    DataSet test = data.extractRandomBatch(n_test);
    DataSet test_labeled = test;
    test.stripLabels();

    // classifies test data
    classifier.fitData(data);
    classifier.classifyData(test);

    // checks accuracy
    size_t n_correct = 0;
    for (size_t i = 0; i < n_test; i++) {
        if (test[i].getLabel() == test_labeled[i].getLabel())
            n_correct++;
    }

    // returns percentage of correct predictions
    return static_cast<double>(n_correct) / n_test;
}

}