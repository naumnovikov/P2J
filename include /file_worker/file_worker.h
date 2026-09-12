#include <fstream>
#include <string>

namespace file_worker{
    class FileWorker{
        private:
            std::fstream fd;
        public:
            explicit FileWorker(const std::string& path);
            ~FileWorker();

            void close();
    };
}