
#ifndef LOGGING_LOG_HPP
#define LOGGING_LOG_HPP

#include "logging/level.hpp"
#include "datetime/timestamp.hpp"
#include <source_location> // std::source_location
#include <string_view> // std::string_view

namespace logging {
    
    struct Log {
        Message message; // readonly
        MessageLevel level;
        
        datetime::Timestamp dt;
        datetime::Duration timestamp; // Duration since logging::init()
        
        std::source_location source;
    };
    
}

#endif // LOGGING_LOG_HPP
