#ifndef LEARN_INCLUDE_DATA_H_
#define LEARN_INCLUDE_DATA_H_

#include <optional>
#include <vector>
#include <random>

#include "Vector.h"
#include "Random.h"

namespace learn {

class DataPoint {
public:
    DataPoint(const Vector &data, size_t label);
    DataPoint(const Vector &data);

    const Vector &getData() const;
    void setData(const Vector &data);
    size_t getLabel() const;
    void setLabel(size_t label);
    void stripLabel();
    bool hasLabel() const;
private:
    Vector data_;
    std::optional<size_t> label_;
};

class DataSet {
public:
    DataSet();
    DataSet(const std::vector<DataPoint> &data);

    void pushBack(const DataPoint &point);
    void reserve(size_t n);

    DataPoint &operator[](size_t idx);
    const DataPoint &operator[](size_t idx) const;
    DataSet extractRandomBatch(size_t n_pts);
    
    void stripLabels();

    size_t size() const;
private:
    std::vector<DataPoint> data_;
    UniformGenerator rng_;
};

}

#endif /* LEARN_INCLUDE_DATA_H_ */