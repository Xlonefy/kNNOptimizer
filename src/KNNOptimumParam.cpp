#include <vector>

#include "Problem.h"
#include "Vector.h"
#include "Classifier.h"

namespace learn {

KNNOptimumParam::KNNOptimumParam(const DataSet &data) : data_(data) {
    num_dims_ = data[0].getData().len(); // TODO(Xlonefy): fix this monstrosity
}

double KNNOptimumParam::evalScore(const Genome &genome) const {
    KNNClassifier knn(genome);
    knn.fitData(data_);
    CrossValidator validator;
    return validator.crossValidationScore(knn, data_);
}

GenomeSpec KNNOptimumParam::getSpec() const {
    GenomeSpec spec;
    
    spec.registerVariable(new SizeVar(1, 3, "p-norm"));
    spec.registerVariable(new SizeVar(10, 100, "n_neighbors"));
    spec.registerVariable(new DoubleVectorVar(0.0, 5.0, num_dims_, "column_weights"));

    return spec;
}

KNNOptimumParam *KNNOptimumParam::clone() const {
    return new KNNOptimumParam(*this);
}

}