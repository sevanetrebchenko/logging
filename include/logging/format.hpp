
#ifndef LOGGING_FORMAT_HPP
#define LOGGING_FORMAT_HPP

#include <string> // std::string

namespace logging {
    
    template <typename T>
    void add_format_specifier(const std::string& specifier, std::string (*formatter)(const T&));
    
}

// Template definitions.
#include "logging/format.tpp"

#endif // LOGGING_FORMAT_HPP
