#include <algorithm>

#include "Data.h"

namespace learn {

DataSet::DataSet() {}
DataSet::DataSet(const std::vector<DataPoint> &data) : data_(data) {}

void DataSet::pushBack(const DataPoint &point) {
    data_.push_back(point);
}

void DataSet::reserve(size_t n) {
    data_.reserve(n);
}

DataPoint &DataSet::operator[](size_t idx) {
    return data_[idx];
}

const DataPoint &DataSet::operator[](size_t idx) const {
    return data_.at(idx);
}

DataSet DataSet::extractRandomBatch(size_t n_pts) {
    std::vector<DataPoint> batch;
    batch.reserve(n_pts);

    for (size_t i = 0; i < n_pts; i++) {
        size_t idx = rng_.getSize(0, data_.size() - 1);

        batch.push_back(data_[idx]);

        // deletes selected element in a way that does not require displacing
        // all items after the deleted item
        std::iter_swap(data_.begin() + idx, data_.end() - 1);
        data_.pop_back();
    }

    return DataSet(batch);
}

void DataSet::stripLabels() {
    for (auto item : data_)
        item.stripLabel();
}

size_t DataSet::size() const {
    return data_.size();
}

}