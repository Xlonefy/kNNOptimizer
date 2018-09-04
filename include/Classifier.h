#ifndef LEARN_INCLUDE_CLASSIFIER_H_
#define LEARN_INCLUDE_CLASSIFIER_H_

#include <optional>

#include "Data.h"
#include "Vector.h"
#include "Genetics.h"

namespace learn {

class Classifier {
public:
    Classifier();
    void fitData(const DataSet &data);
    virtual void classifyData(DataSet &data) const = 0;
    const DataSet &getFittedData() const;
protected:
    DataSet fitted_;
};

class CrossValidator {
public:
    CrossValidator(size_t num_iters = 1, double percent_test = 0.05);
    double crossValidationScore(Classifier &classifier, const DataSet &data) const;
private:
    double crossValidationIteration(Classifier &classifier, DataSet data) const;
    size_t num_iters_;
    double percent_test_;
};

class KNNClassifier : public Classifier {
public:
    KNNClassifier(const Genome &config);
    void classifyData(DataSet &data) const;
private:
    void classifyPoint(DataPoint &point) const;

    size_t n_neighbors_;
    LNNorm norm_;
    double use_column_weights_;
    std::optional<Vector> column_weights_;
};

} 

#endif /* LEARN_INCLUDE_CLASSIFIER_H_ */