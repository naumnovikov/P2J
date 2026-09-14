#include "PcapFileDevice.h"
#include <string>

namespace parser{
    class Parser{
        private:
            pcpp::PcapFileReaderDevice reader;
        public:
            explicit Parser(const std::string& path);
            ~Parser();

            void close();
            std::string getParse();
    };
}