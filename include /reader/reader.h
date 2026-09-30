#include "PcapFileDevice.h"
#include "nlohmann/json"
#include <string>
#include <vector>

namespace reader{
    using parsedPacket = std::string;
    using json = nlohmann::json;
    using jsonVector = std::vector<json>;

    class Reader{
        private:
            pcpp::PcapFileReaderDevice* reader;
        public:
            explicit Reader(const std::string& path);
            ~Reader();

            void close();
            jsonVector getData();
    };
}   // namespace reader