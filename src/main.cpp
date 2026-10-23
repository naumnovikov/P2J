#include "reader.h"
#include "writer.h"

#include <iostream>
#include <stdexcept>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input.pcap> [output.json]\n";
        return 1;
    }

    try {
        const std::string inputFile = argv[1];
        const std::string outputFile = (argc >= 3) ? argv[2] : "packets.json";

        reader::Reader reader(inputFile);
        const auto packets = reader.getData();

        if (packets.empty()) {
            std::cerr << "Couldn't get data from file: " << inputFile << '\n';
            return 2;
        }

        writer::Writer writer;
        writer.createReadyJSONFile(packets, outputFile, inputFile);

        std::cout << "Converted " << packets.size() << " packets into " << outputFile << '\n';
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 3;
    }
}