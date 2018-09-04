#include "Config.h"

namespace learn {

Config::Config() {}

ConfigValue &Config::getKey(const std::string &key) {
    return config_[key];
}

ConfigValue Config::getKey(const std::string &key) const {
    return config_.at(key);
}

bool Config::hasKey(const std::string &key) const {
    return config_.count(key) > 0;
}

}