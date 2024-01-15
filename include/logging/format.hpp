
#ifndef LOGGING_FORMAT_HPP
#define LOGGING_FORMAT_HPP

#include <string> // std::string
#include <functional> // std::function

namespace logging {
    
    template <typename T>
    void add_format_specifier(const std::string& specifier, std::function<std::string(const T&)> formatter);
    
}

// Template definitions.
#include "logging/format.tpp"

#endif // LOGGING_FORMAT_HPP
