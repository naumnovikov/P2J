#include "converter.h"

namespace converter{
    jsonVector Converter::convertToJSON(const pcapVector& pcapData) {
        jsonVector jsonData;
        for (const auto& packetStr : pcapData) {
            json jsonPacket;

            
            jsonData.push_back(jsonPacket);
        }
        return jsonData;
    }
}   // namespace converter