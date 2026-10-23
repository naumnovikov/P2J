#include "reader.h"

#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>

#include "PcapFileDevice.h"
#include "Packet.h"
#include "EthLayer.h"
#include "IPv4Layer.h"
#include "IPv6Layer.h"
#include "TcpLayer.h"
#include "UdpLayer.h"
#include "PayloadLayer.h"

namespace reader {

Reader::Reader(const std::string& filePath)
    : filePath_(filePath) {}

jsonVector Reader::getData() const {
    pcpp::PcapFileReaderDevice reader(filePath_);
    if (!reader.open()) {
        throw std::runtime_error("Failed to open pcap file: " + filePath_);
    }

    jsonVector packets;
    pcpp::RawPacket rawPacket;

    while (reader.getNextPacket(rawPacket)) {
        pcpp::Packet parsedPacket(&rawPacket);
        json packetJson = json::object();

        auto ts = rawPacket.getPacketTimeStamp();
        std::time_t t = ts.tv_sec;
        std::tm tmInfo{};
#ifdef _WIN32
        localtime_s(&tmInfo, &t);
#else
        localtime_r(&t, &tmInfo);
#endif

        std::ostringstream oss;
        oss << std::put_time(&tmInfo, "%Y-%m-%dT%H:%M:%SZ");
        packetJson["timestamp"] = oss.str();

        auto* ethernet = parsedPacket.getLayerOfType<pcpp::EthLayer>();
        if (ethernet) {
            packetJson["ethernet"] = {
                {"src", ethernet->getSourceMac().toString()},
                {"dst", ethernet->getDestMac().toString()}
            };
        }

        auto* ipv4 = parsedPacket.getLayerOfType<pcpp::IPv4Layer>();
        if (ipv4) {
            packetJson["ip"] = {
                {"version", 4},
                {"src", ipv4->getSrcIPv4Address().toString()},
                {"dst", ipv4->getDstIPv4Address().toString()},
                {"protocol", static_cast<int>(ipv4->getProtocol())}
            };
        }

        auto* ipv6 = parsedPacket.getLayerOfType<pcpp::IPv6Layer>();
        if (ipv6) {
            packetJson["ip"] = {
                {"version", 6},
                {"src", ipv6->getSrcIPv6Address().toString()},
                {"dst", ipv6->getDstIPv6Address().toString()}
            };
        }

        auto* tcp = parsedPacket.getLayerOfType<pcpp::TcpLayer>();
        if (tcp) {
            packetJson["transport"] = {
                {"protocol", "TCP"},
                {"src_port", tcp->getSrcPort()},
                {"dst_port", tcp->getDstPort()}
            };
        }

        auto* udp = parsedPacket.getLayerOfType<pcpp::UdpLayer>();
        if (udp) {
            packetJson["transport"] = {
                {"protocol", "UDP"},
                {"src_port", udp->getSrcPort()},
                {"dst_port", udp->getDstPort()}
            };
        }

        auto* payloadLayer = parsedPacket.getLayerOfType<pcpp::PayloadLayer>();
        if (payloadLayer) {
            const auto* payloadData = payloadLayer->getData();
            const size_t payloadSize = payloadLayer->getDataLen();
            packetJson["payload_size"] = static_cast<int>(payloadSize);

            if (payloadData != nullptr && payloadSize > 0) {
                std::ostringstream hexStream;
                for (size_t i = 0; i < payloadSize; ++i) {
                    hexStream << std::hex << std::setw(2) << std::setfill('0')
                              << static_cast<int>(payloadData[i]);
                }
                packetJson["payload_hex"] = hexStream.str();
            }
        }

        packetJson["length"] = static_cast<int>(rawPacket.getRawDataLen());
        packets.push_back(packetJson);
    }

    reader.close();
    return packets;
}

} // namespace reader
