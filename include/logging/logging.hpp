
#ifndef LOGGING_LOGGING_HPP
#define LOGGING_LOGGING_HPP

#include "logging/message.hpp"
#include <string> // std::string
#include <cstdint> // std::uint8_t
#include <source_location> // std::source_location
#include <unordered_map> // std::unordered_map
#include <functional>

namespace logging {
    
    void init();
    void shutdown();

    template <typename T>
    void add_format_specifier(char specifier, std::function<std::string(const T&)> func);
    
    template <typename ...Ts>
    void info(Message message, Ts...);
    
    void debug(Message message, ...);
    void warning(Message message, ...);
    void error(Message message, ...);
    
}

#endif // LOGGING_LOGGING_HPP
