
#ifndef LOGGING_LOGGING_HPP
#define LOGGING_LOGGING_HPP

#include "logging/message.hpp"
#include <string> // std::string
#include <source_location> // std::source_location

namespace logging {
    
    void init();
    void shutdown();

    namespace internal {
        
        struct Log {
            public:
                Log() {}
                ~Log() {}
            
            protected:
                template <typename T>
                void parse();
                
                const char* m_format;
                std::source_location m_source;
                
        };
    }

    // Note for all logging functions:
    // Constructor automatically submits the log message for output if the message format string does not contain named arguments.
    // Otherwise, log submit is done by calling format(...) and providing the appropriate named arguments.
    
    template <typename ...Ts>
    struct info : internal::Log {
        info(const char* format, const Ts&..., std::source_location source = std::source_location::current());
        ~info() {}
        
        template <typename ...Args>
        void format(const Args&... args) const {}
    };
    template <typename ...Ts>
    info(const char* format, const Ts&...) -> info<Ts...>;
    
//    void debug(Message message, ...);
//    void warning(Message message, ...);
//    void error(Message message, ...);
    
}

// Template definitions.
#include "logging/template/logging.tpp"

#endif // LOGGING_LOGGING_HPP
