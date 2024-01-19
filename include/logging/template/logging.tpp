
#ifndef LOGGING_LOGGING_TPP
#define LOGGING_LOGGING_TPP

#include "logging/message.hpp"
#include <string> // std::string
#include <cstdint> // std::uint8_t
#include <source_location> // std::source_location
#include <unordered_map> // std::unordered_map
#include <functional>

namespace logging {
    
    // Formatter implementation
    template <typename ...Args>
    void Formatter::format(const Args& ...args) const {
    }
    
    template <typename ...Args>
    Formatter info(Message message, const Args&...) {
    }
    
}

#endif // LOGGING_LOGGING_TPP
