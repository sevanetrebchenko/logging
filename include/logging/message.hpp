
#ifndef LOGGING_MESSAGE_HPP
#define LOGGING_MESSAGE_HPP

#include <string>
#include <source_location> // std::source_location
#include <vector>

namespace logging {

    struct FormatSpecifier {
        unsigned offset;
        unsigned length; // Total length, including braces.
        std::string_view name; // Specifier name.
    };
    
    class Message {
        public:
            struct Formatter;
            
            // Purposefully allow implicit conversions to support a transparent logging public interface.
            Message(const char* format, std::source_location source = std::source_location::current());
            ~Message();
            
            template <typename ...Args>
            [[nodiscard]] std::string format(const Args&... args) const;
            
        private:
            std::string m_format;
            std::source_location m_source;
    };
    
    
    struct Message::Formatter {
        Formatter(const char* format, std::source_location source = std::source_location::current());
        
        // Submits message at call location
        template <typename ...Args>
        void format(const Args&... args) const;
    };

}

// Template definitions.
#include "logging/template/message.tpp"

#endif // LOGGING_MESSAGE_HPP
