
#include "logging/format.hpp"

namespace logging {
    namespace internal {
        
        std::unordered_map<std::string, std::unique_ptr<Formatter>> formatters { };
        Formatter::~Formatter() = default;
        
    }
}