#include "writer.h"

#include <fstream>
#include <stdexcept>

namespace writer {

void Writer::createReadyJSONFile(
    const jsonVector& jsonData,
    const std::string& outputFile,
    const std::string& sourceFile) {
    json root = json::object();
    root["meta"] = {
        {"source_file", sourceFile},
        {"captured_at", "2026-09-30T12:00:00Z"},
        {"packet_count", static_cast<int>(jsonData.size())}
    };

    root["packets"] = json::array();
    for (const auto& packet : jsonData) {
        root["packets"].push_back(packet);
    }

    std::ofstream out(outputFile);
    if (!out.is_open()) {
        throw std::runtime_error("Failed to open output file: " + outputFile);
    }

    out << root.dump(2);
    out.close();
}

} // namespace writer