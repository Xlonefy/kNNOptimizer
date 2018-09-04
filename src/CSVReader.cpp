#include <string>
#include <fstream>

#include "Reader.h"
#include "parser.hpp"

namespace learn {

CSVReader::CSVReader() {}

DataSet CSVReader::parseFile(const std::string &filename) const {
    using Parser = aria::csv::CsvParser;
    
    std::ifstream file(filename);
    Parser csv(file);

    DataSet data;
    for (auto &row : csv)
    {
        size_t line_size = row.size();

        size_t label = 0;
        Vector raw_point(line_size - 1);

        size_t idx = 0;
        for (auto &item : row) {
            if (idx == line_size - 1){
                label = std::stoi(item);
            } else {
                raw_point[idx++] = std::stod(item);
            }
        }

        data.pushBack(DataPoint(raw_point, label));
    }

    return data;
}

}