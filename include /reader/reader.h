#include "PcapFileDevice.h"
#include <string>
#include <vector>

namespace reader{
    using parsedPacket = std::string;
    //     Example of parsed HTTP packet:
    //     Ethernet II, Src: 00:11:22:33:44:55, Dst: 66:77:88:99:aa:bb
    //     IPv4, Src: 192.168.1.10, Dst: 10.0.0.1, TTL: 64, Protocol: TCP
    //     TCP, Src Port: 54321, Dst Port: 80, Seq: 1, Ack: 1, Flags: PSH, ACK
    //     HTTP, Request: GET /index.html HTTP/1.1, Host: example.com

    using pcapVector = std::vector<parsedPacket>;

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