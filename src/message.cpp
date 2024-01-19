
#include "logging/message.hpp"
#include <stdexcept>

namespace logging {
    
    Message::Message(const char* format, std::source_location source) : m_format(format),
                                                                        m_source(source)
                                                                        {
        std::size_t length = strlen(format);
        bool open = false;
        unsigned start = 0u;
        
        unsigned i = 0u;
        while (i < length) {
            bool is_last_character = (i == length - 1u);
            
            if (open) {
                if (format[i] == '}') {
                    open = false;
                }
                else if (format[i] == '{') {
                    // Cannot open a new scope inside an already existing one.
                    throw std::runtime_error("opening scope inside existing scope");
                }
                else if (std::isspace(format[i])) {
                    // No spaces allowed within
                    throw std::runtime_error("invalid format string");
                }
            }
            else {
                if (format[i] == '{') {
                    // Found new format specifier.
                    if (!is_last_character) {
                        if (format[i + 1u] == '{') {
                            // Escaped '{' character, skip.
                            ++i;
                        }
                        else {
                            open = true;
                        }
                    }
                }
                else if (format[i] == '}') {
                    if (!is_last_character) {
                        if (format[i + 1u] == '}') {
                            // Escaped '}' character, skip.
                            ++i;
                        }
                    }
                }
            }
            
            ++i;
        }
        
        if (open) {
            throw std::runtime_error("invalid format string");
        }
    }

    Message::~Message() = default;
    
}