#include "Genetics.h"

namespace learn {

GenomeSpec::~GenomeSpec() {
    for (auto i : vars_)
        delete i;
}

GenomeSpec::GenomeSpec(const GenomeSpec &gs) {
    for (const auto &i : gs.vars_)
        vars_.push_back(i->clone());
}

void GenomeSpec::registerVariable(Variable &var) {
    vars_.push_back(var.clone());
}

void GenomeSpec::registerVariable(Variable *var) {
    vars_.push_back(var);
}

Genome GenomeSpec::getRandomGenome() const {
    Genome g;
    for (auto i : vars_) 
        i->getRandomValue(g);
    return g;
}

Genome GenomeSpec::mixGenes(const Genome &g1, const Genome &g2) const {
    Genome gcopy = g1;
    for (auto i : vars_)
        i->mixVariables(gcopy, g2);
    return gcopy;
}

}