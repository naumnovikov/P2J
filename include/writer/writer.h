#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace writer {
using json = nlohmann::json;
using jsonVector = std::vector<json>;

class Writer {
public:
    void createReadyJSONFile(
        const jsonVector& jsonData,
        const std::string& outputFile = "packets.json",
        const std::string& sourceFile = "capture.pcap");
};

} // namespace writer
