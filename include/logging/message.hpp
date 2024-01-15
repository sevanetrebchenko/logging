
#ifndef LOGGING_MESSAGE_HPP
#define LOGGING_MESSAGE_HPP

#include <string>
#include <source_location> // std::source_location
#include <vector>

namespace logging {

    class Message {
        public:
            // Purposefully allow implicit conversions
            Message(const char* format, std::source_location source = std::source_location::current());
            ~Message();
            
            template <typename ...Args>
            [[nodiscard]] std::string format(const Args&... args) const;
        
        private:
            std::string m_format;
            std::vector<std::string_view> m_specifiers;
            std::source_location m_source;
    };

}

// Template definitions.
#include "logging/message.tpp"

#endif // LOGGING_MESSAGE_HPP
