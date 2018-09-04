#ifndef LEARN_INCLUDE_READER_H_
#define LEARN_INCLUDE_READER_H_

#include <string>

#include "Data.h"

namespace learn {

class CSVReader {
public:
    CSVReader();
    DataSet parseFile(const std::string &filename) const;
};

}

#endif /* LEARN_INCLUDE_READER_H_ */