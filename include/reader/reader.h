#pragma once

#include <string>
#include <vector>

#include <nlohmann/json.hpp>

namespace reader {
using json = nlohmann::json;
using jsonVector = std::vector<json>;

class Reader {
public:
    explicit Reader(const std::string& filePath);
    jsonVector getData() const;

private:
    std::string filePath_;
};

} // namespace reader
