#include "PcapFileDevice.h"
#include <string>
#include <vector>

namespace reader{
    using pcapVector = std::vector<std::string>;

    class Reader{
        private:
            pcpp::PcapFileReaderDevice* reader;
        public:
            explicit Reader(const std::string& path);
            ~Reader();

            void close();
            pcapVector getData();
    };
}   // namespace reader