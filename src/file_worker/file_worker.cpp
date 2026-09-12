#include <string>

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
}
