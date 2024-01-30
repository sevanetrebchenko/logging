
#include "logging/format.hpp"

namespace logging {
    namespace internal {
        
        std::unordered_map<std::type_index, std::shared_ptr<Formatter>> formatters {
            // TODO: standard container definitions.
        };
        
        Formatter::~Formatter() = default;
        
    }
}