
#ifndef LOGGING_LEVEL_HPP
#define LOGGING_LEVEL_HPP

#include <cstdint> // std::uint8_t

namespace logging {
    
    enum class MessageLevel : std::uint8_t {
        Info = 0,
        Debug,
        Warning,
        Error,
        Fatal
    };
    
}

#endif // LOGGING_LEVEL_HPP
