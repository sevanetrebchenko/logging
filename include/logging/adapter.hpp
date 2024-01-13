
#ifndef LOGGING_ADAPTER_HPP
#define LOGGING_ADAPTER_HPP

#include "logging/level.hpp"
#include <string_view> // std::string_view
#include <functional> // std::function

namespace logging {
    
    // stdout
    void enable_stdout(bool enabled);
    void set_stdout_format(std::string_view format);
    
    // stderr
    void enable_stderr(bool enabled);
    void set_stderr_format(std::string_view format);
    
    // Adapters allow for redirecting logs to multiple locations.
    void add_adapter(std::string_view filename, std::string_view format, MessageLevel level);
    void add_adapter(const std::function<void(const std::string_view&)>& callback, std::string_view format, MessageLevel level);
    void add_adapter(const std::function<void(const Log&)>& callback);
    
}

#endif // LOGGING_ADAPTER_HPP
