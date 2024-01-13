
#ifndef LOGGING_MESSAGE_HPP
#define LOGGING_MESSAGE_HPP

#include <source_location> // std::source_location

namespace logging {
    
    struct Message {
        // Purposefully allow implicit conversions
        Message(const char* format, std::source_location source = std::source_location::current());
        ~Message();
        
        const char* format; // C-style format string
        std::source_location source;
    };

}

#endif // LOGGING_MESSAGE_HPP
