#include "reader.h"

// ============================================================
// 1. Базовые заголовки (Packet++, Pcap++, Common++)
// ============================================================
#include "Packet.h"                // базовый класс Packet, агрегирует слои
#include "RawPacket.h"             // сырые данные пакета (нужен для чтения)
#include "ProtocolType.h"          // enum ProtocolType для идентификации протоколов

// ============================================================
// 2. Канальный уровень (L2)
// ============================================================
#include "EthLayer.h"              // Ethernet II
#include "EthDot3Layer.h"          // IEEE 802.3 Ethernet
#include "LLCLayer.h"              // LLC (Logical Link Control)
#include "NullLoopbackLayer.h"     // Null/Loopback
#include "PacketTrailerLayer.h"    // trailer / padding
#include "PPPoELayer.h"            // PPPoE (Session + Discovery)
#include "SllLayer.h"              // SLL (Linux cooked capture)
#include "StpLayer.h"              // STP (Spanning Tree Protocol)
#include "VlanLayer.h"             // VLAN (802.1Q)
#include "VxlanLayer.h"            // VXLAN
#include "WakeOnLanLayer.h"        // Wake on LAN (WoL)

// ============================================================
// 3. Сетевой уровень (L3) и выше
// ============================================================
#include "ArpLayer.h"              // ARP
#include "GreLayer.h"              // GRE (v0, v1) и PPTP
#include "IcmpLayer.h"             // ICMP
#include "IcmpV6Layer.h"           // ICMPv6 (включая Echo)
#include "IgmpLayer.h"             // IGMP
#include "IPv4Layer.h"             // IPv4
#include "IPv6Layer.h"             // IPv6
#include "MplsLayer.h"             // MPLS
#include "NdpLayer.h"              // NDP (Neighbor Discovery Protocol)
#include "GtpLayer.h"              // GTP (v1)

// ============================================================
// 4. Транспортный уровень (L4)
// ============================================================
#include "TcpLayer.h"              // TCP
#include "UdpLayer.h"              // UDP

// ============================================================
// 5. Прикладной уровень и протоколы сессий (L5–L7)
// ============================================================
#include "SdpLayer.h"              // SDP
#include "SipLayer.h"              // SIP (Request + Response)
#include "SSLLayer.h"              // SSL/TLS (parsing only)
#include "BgpLayer.h"              // BGP
#include "DhcpLayer.h"             // DHCP
#include "DhcpV6Layer.h"           // DHCPv6
#include "DnsLayer.h"              // DNS
#include "FtpLayer.h"              // FTP (Request + Response)
#include "HttpLayer.h"             // HTTP (Request + Response)
#include "NtpLayer.h"              // NTP (v3, v4)
#include "RadiusLayer.h"           // RADIUS
#include "SomeIpLayer.h"           // SOME/IP (включая TP и SD)
#include "SSHLayer.h"              // SSH (parsing only)
#include "TelnetLayer.h"           // Telnet

// ============================================================
// 6. IPSec (парсинг без редактирования)
// ============================================================
// AuthenticationHeaderLayer и ESPLayer не имеют отдельных заголовков —
// они объявлены внутри соответствующих файлов, но в документации
// указаны как «parsing only (no editing capabilities)».

// ============================================================
// 7. Запасной слой для неизвестных данных
// ============================================================
#include "PayloadLayer.h"          // unknown layer / payload

#include <memory>

namespace reader {
    Reader::Reader(const std::string& path) {
        reader = std::make_unique<pcpp::PcapFileReaderDevice>(path);
    }

    Reader::~Reader() {
        if (reader->isOpened()) {
            close();
        }
    }

    void Reader::close() {
        reader->close();
    }

    pcapVector Reader::getData(){
        if (!reader->isOpened()) {
            return {};
        }

        pcapVector readData;
        pcpp::RawPacket rawPacket;
        while (reader->getNextPacket(rawPacket)){
            pcpp::Packet parsedPacket(&rawPacket);
            readData.push_back(parsedPacket.toString());
        }

        return readData;
    }

} // namespace reader
