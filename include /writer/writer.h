#include <vector>
#include <string>
#include <nlohmann/json.hpp>

namespace writer{
    using json = nlohmann::json;
    using jsonVector = std::vector<json>;

    class Writer{
        public:
            void createJSONFile(const jsonVector& jsonData);
    };
}   // namespace writer