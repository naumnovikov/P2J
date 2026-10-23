#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <nlohmann/json.hpp>

#include "writer.h"

namespace {

void cleanupFile(const std::string& path) {
    std::remove(path.c_str());
}

} // namespace

TEST(WriterTest, WritesSourceFileAndPacketCount) {
    const std::string outputPath = "writer_test_output_1.json";
    const std::string sourceFile = "sample_capture.pcap";
    cleanupFile(outputPath);

    writer::jsonVector packets;
    packets.push_back({
        {"timestamp", "2026-09-30T12:00:00Z"},
        {"length", 64}
    });

    writer::Writer writer;
    writer.createReadyJSONFile(packets, outputPath, sourceFile);

    std::ifstream in(outputPath);
    ASSERT_TRUE(in.is_open());

    nlohmann::json root;
    in >> root;

    EXPECT_EQ(root["meta"]["source_file"], sourceFile);
    EXPECT_EQ(root["meta"]["packet_count"], 1);
    EXPECT_EQ(root["packets"].size(), 1);

    cleanupFile(outputPath);
}

TEST(WriterTest, WritesEmptyPacketList) {
    const std::string outputPath = "writer_test_output_2.json";
    const std::string sourceFile = "empty_capture.pcap";
    cleanupFile(outputPath);

    writer::jsonVector packets;
    writer::Writer writer;
    writer.createReadyJSONFile(packets, outputPath, sourceFile);

    std::ifstream in(outputPath);
    ASSERT_TRUE(in.is_open());

    nlohmann::json root;
    in >> root;

    EXPECT_EQ(root["meta"]["source_file"], sourceFile);
    EXPECT_EQ(root["meta"]["packet_count"], 0);
    EXPECT_TRUE(root["packets"].is_array());
    EXPECT_EQ(root["packets"].size(), 0);

    cleanupFile(outputPath);
}

TEST(WriterTest, WritesMultiplePackets) {
    const std::string outputPath = "writer_test_output_3.json";
    const std::string sourceFile = "multi_capture.pcap";
    cleanupFile(outputPath);

    writer::jsonVector packets;
    packets.push_back({
        {"timestamp", "2026-09-30T12:00:00Z"},
        {"length", 64}
    });
    packets.push_back({
        {"timestamp", "2026-09-30T12:00:01Z"},
        {"length", 128}
    });
    packets.push_back({
        {"timestamp", "2026-09-30T12:00:02Z"},
        {"length", 256}
    });

    writer::Writer writer;
    writer.createReadyJSONFile(packets, outputPath, sourceFile);

    std::ifstream in(outputPath);
    ASSERT_TRUE(in.is_open());

    nlohmann::json root;
    in >> root;

    EXPECT_EQ(root["meta"]["source_file"], sourceFile);
    EXPECT_EQ(root["meta"]["packet_count"], 3);
    EXPECT_EQ(root["packets"].size(), 3);
    EXPECT_EQ(root["packets"][0]["length"], 64);
    EXPECT_EQ(root["packets"][1]["length"], 128);
    EXPECT_EQ(root["packets"][2]["length"], 256);

    cleanupFile(outputPath);
}

TEST(WriterTest, ProducesJsonObjectWithMetaAndPacketsKeys) {
    const std::string outputPath = "writer_test_output_4.json";
    cleanupFile(outputPath);

    writer::jsonVector packets = {{
        {"timestamp", "2026-09-30T12:00:00Z"},
        {"ip", { {"src", "10.0.0.1"}, {"dst", "10.0.0.2"} }}
    }};

    writer::Writer writer;
    writer.createReadyJSONFile(packets, outputPath, "keys_test.pcap");

    std::ifstream in(outputPath);
    ASSERT_TRUE(in.is_open());

    nlohmann::json root;
    in >> root;

    EXPECT_TRUE(root.contains("meta"));
    EXPECT_TRUE(root.contains("packets"));
    EXPECT_TRUE(root["meta"].contains("source_file"));
    EXPECT_TRUE(root["meta"].contains("packet_count"));
    EXPECT_TRUE(root["packets"].is_array());

    cleanupFile(outputPath);
}
