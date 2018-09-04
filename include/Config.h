#ifndef LEARN_INCLUDE_CONFIG_H_
#define LEARN_INCLUDE_CONFIG_H_

#include <string>
#include <unordered_map>

#include "Vector.h"

namespace learn {
    
union ConfigValue {
    size_t size;
    double floating_point;
    int integer;
    Vector *vector; // TODO(Xlonefy): will leak memory
};

class Config {
public:
    Config();
    ConfigValue &getKey(const std::string &key);
    ConfigValue getKey(const std::string &key) const;
    bool hasKey(const std::string &key) const;
private:
    std::unordered_map<std::string, ConfigValue> config_;
};

}

#endif /* LEARN_INCLUDE_CONFIG_H_ */