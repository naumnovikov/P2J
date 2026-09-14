#include <iostream>

#include "file_worker.h"

namespace file_worker {
    FileWorker::FileWorker(const std::string& path) {
        if (!path.empty()) {
            fd.open(path, std::ios::binary);
        }
    }

    FileWorker::~FileWorker() {
        close();
    }

    void FileWorker::close() {
        if (fd.is_open()) {
            fd.close();
        }
    }
    std::string FileWorker::read() {
        if (!fd.is_open()) {
            return "";
        }

        fd.seekg(0, std::ios::end);
        std::streamsize size = fd.tellg();

        // If the file is empty or an error occurred, return an empty string
        if (size <= 0) {
            return "";
        }

        fd.seekg(0, std::ios::beg);

        std::string data(static_cast<std::size_t>(size), '\0');
        fd.read(&data[0], size);

        return data;
    }
}
