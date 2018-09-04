#include "Classifier.h"

#include <forward_list>
#include <unordered_map>
#include <vector>
#include <tuple>

namespace learn {

KNNClassifier::KNNClassifier(const Genome &config) 
    : n_neighbors_(5), norm_(2), use_column_weights_(false) {

    if (config.hasKey("p-norm"))
        norm_ = LNNorm(config.getKey<size_t>("p-norm"));
    
    if (config.hasKey("n_neighbors"))
        n_neighbors_ = config.getKey<size_t>("n_neighbors");
    
    if (config.hasKey("column_weights")) {
        use_column_weights_ = true;
        column_weights_ = Vector(config.getKey<std::vector<double>>("column_weights"));
    }
}

void KNNClassifier::classifyData(DataSet &data) const {
    for (size_t i = 0; i < data.size(); i++)
        classifyPoint(data[i]);
}

void KNNClassifier::classifyPoint(DataPoint &point) const {
    // vector of distances to point and the respective datapoints
    std::forward_list<std::pair<const DataPoint &, double>> distances;
    size_t num_distances = 0;

    // item for item on fitted calculates the distance to point
    for (size_t i = 0; i < fitted_.size(); i++) {
        Vector diff = fitted_[i].getData() - point.getData();
        if (use_column_weights_)
            diff = diff * column_weights_.value();
        double distance = norm_(diff);

        // traverses list and inserts such that the list is sorted from farthest
        // to closest point
        if (distances.empty()) {
            distances.emplace_front(fitted_[i], distance);
            num_distances++;
            continue;
        }

        // // if (distances.front().second < distance) {
        // //     distances.emplace_front(fitted_[i], distance);
        // //     num_distances++;
        // //     continue;
        // // }

        int idx_of_shit = 0;
        for (auto elem = distances.begin(); elem != distances.end(); elem++) { idx_of_shit++; }

        for (auto elem = distances.before_begin(); elem != distances.end(); elem++) {
            auto next = elem;
            next++;

            if (next == distances.end()) {
                distances.insert_after(elem, {fitted_[i], distance});
                num_distances++;
                break;
            }

            if (next->second < distance) {
                distances.insert_after(elem, {fitted_[i], distance});
                num_distances++;
                break;
            }
        }

        // cuts the farthest element when number of neighbors is reached
        if (num_distances > n_neighbors_) {
            distances.pop_front();
            num_distances--;
        }
    }

    // counts the votes for each label
    std::unordered_map<size_t, double> votes;
    size_t l_size = num_distances;
    size_t idx = 1;
    for (auto elem = distances.begin(); elem != distances.end();
         elem++, idx++) {
        size_t label = elem->first.getLabel();
        if (votes.count(label)) {
            votes[label] += 1.0 / (l_size - idx);
        } else {
            votes[label] = 1.0 / (l_size - idx);
        }
    }

    // finds the most voted label
    double score = 0;
    size_t label = 0;
    for (auto i : votes) {
        if (i.second > score) {
            score = i.second;
            label = i.first;
        }
    }

    point.setLabel(label);
}

}