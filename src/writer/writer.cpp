#include "writer.h"
#include <fstream>

namespace writer{
    void Writer::createJSONFile(const jsonVector& jsonData) {
        json root;
        root["meta"] = {
            {"source_file", "capture.pcap"},
            {"captured_at", "2026-09-30T12:00:00Z"},
            {"packet_count", jsonData.size()}
        };
        root["packets"] = json::array();
        for (auto& j : jsonData)
            root["packets"].push_back(std::move(j));

        std::ofstream out("packets.json");
        out << root.dump(2);
        close(out);
    }
}   // namespace writer