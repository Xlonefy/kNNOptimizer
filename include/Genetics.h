#ifndef LEARN_INCLUDE_GENETICS_H_
#define LEARN_INCLUDE_GENETICS_H_

#include <string>
#include <vector>
#include <random>
#include <unordered_map>
#include <any>
#include <cassert>

#include "Random.h"

namespace learn {

class Genome {
public:
    Genome() = default;
    Genome(const Genome &g);
    ~Genome();
    bool hasKey(const std::string &key) const;
    template <typename T>
    T &getKey(const std::string &key);
    template <typename T>
    T getKey(const std::string &key) const;
    void swap(Genome &other);
private:
    std::unordered_map<std::string, std::any> value_store_;
};

using std::swap;
void swap(Genome &g1, Genome &g2);

template <typename T>
T &Genome::getKey(const std::string &key) {
    if (!hasKey(key))
        value_store_[key].emplace<T>();
    
    return std::any_cast<T &>(value_store_[key]);
}

template <typename T>
T Genome::getKey(const std::string &key) const {
    assert(hasKey(key));
    return std::any_cast<T>(value_store_.at(key));
}

class Variable {
public:
    Variable(const std::string &name);
    virtual ~Variable() = default;
    const std::string &getName() const;
    virtual void getRandomValue(Genome &genome) const = 0;
    virtual void mixVariables(Genome &g1, const Genome &g2) const = 0;
    virtual Variable *clone() const = 0;
protected:
    std::string name_;
    UniformGenerator rng_;
};


class SizeVar : public Variable {
public:
    SizeVar(size_t min, size_t max, const std::string &name);
    ~SizeVar() = default;
    void getRandomValue(Genome &genome) const;
    void mixVariables(Genome &g1, const Genome &g2) const;
    SizeVar *clone() const;
private:
    size_t min_;
    size_t max_;
};

class IntVar : public Variable {
public:
    IntVar(int min, int max, const std::string &name);
    ~IntVar() = default;
    void getRandomValue(Genome &genome) const;
    void mixVariables(Genome &g1, const Genome &g2) const;
    IntVar *clone() const;
private:
    int min_;
    int max_;
};

class DoubleVar : public Variable {
public:
    DoubleVar(double min, double max, const std::string &name);
    ~DoubleVar() = default;
    void getRandomValue(Genome &genome) const;
    void mixVariables(Genome &g1, const Genome &g2) const;
    DoubleVar *clone() const;
private:
    double min_;
    double max_;
};

class DoubleVectorVar : public Variable {
public:
    DoubleVectorVar(double min, double max, size_t size,
                    const std::string &name);
    ~DoubleVectorVar() = default;
    void getRandomValue(Genome &genome) const;
    void mixVariables(Genome &g1, const Genome &g2) const;
    DoubleVectorVar *clone() const;
private:
    double min_;
    double max_;
    size_t size_;
};


class GenomeSpec {
public:
    GenomeSpec() = default;
    ~GenomeSpec();
    GenomeSpec(const GenomeSpec &gs);
    void registerVariable(Variable &var);
    void registerVariable(Variable *var);
    Genome getRandomGenome() const;
    Genome mixGenes(const Genome &g1, const Genome &g2) const;
private:
    std::vector<Variable *> vars_;
};

}

#endif /* LEARN_INCLUDE_GENETICS_H_ */