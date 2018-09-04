#include "Data.h"

namespace learn {

DataPoint::DataPoint(const Vector &data, size_t label) : data_(data), label_(label) {}
DataPoint::DataPoint(const Vector &data) : data_(data) {}

const Vector &DataPoint::getData() const {
    return data_;
}

void DataPoint::setData(const Vector &data) {
    data_ = data;
}

size_t DataPoint::getLabel() const {
    return label_.value();
}

void DataPoint::setLabel(size_t label) {
    label_ = label;
}

void DataPoint::stripLabel() {
    label_.reset();
}

bool DataPoint::hasLabel() const {
    return static_cast<bool>(label_);
}

}