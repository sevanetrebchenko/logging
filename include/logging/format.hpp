
#ifndef LOGGING_FORMAT_HPP
#define LOGGING_FORMAT_HPP

#include <string> // std::string
#include <functional> // std::function

namespace logging {
    
    namespace format {
        
        // Namespace clashes with std::format if using namespace std; is used, so don't :)
        
        template <typename T>
        struct arg {
            arg(const std::string& name, const T& value);
            ~arg();
        };
        
        // Register a formatting function for a given type.
        template <typename T>
        void register_type_formatter(std::function<std::string(const T&)> formatter);
        
    }
    

    
}

// Template definitions.
#include "logging/template/format.tpp"

#endif // LOGGING_FORMAT_HPP
