
#ifndef LOGGING_LOGGING_HPP
#define LOGGING_LOGGING_HPP

#include "logging/level.hpp"
#include <string> // std::string
#include <source_location> // std::source_location
#include <cstdint> // std::uint16_t
#include <vector> // std::vector
#include <tuple> // std::tuple
#include <variant> // std::variant

#define DEFINE_LOG_LEVEL(LEVEL)                                                                                                               \
    template <typename ...Ps>                                                                                                                 \
    struct LEVEL final : internal::Log {                                                                                                      \
        explicit LEVEL(std::string format, const Ps&... positional_arguments, std::source_location source = std::source_location::current()); \
    };                                                                                                                                        \
    template <typename ...Ts>                                                                                                                 \
    LEVEL(std::string, const Ts&...) -> LEVEL<Ts...>

namespace logging {
    namespace internal {

        struct Log {
            public:
				// Formats positional arguments.
				template <typename ...Ps>
                Log(MessageLevel level, const std::string& format, std::tuple<Ps...> positional_arguments, std::source_location source);
                ~Log() {}

				// Formats named arguments.
				template <typename ...Ns>
				void format(const Ns&... named_arguments) const {}
            
            private:
                struct NamedFormatSpecifier {
                    std::uint32_t offset;
                    std::string name;
                };
                
				MessageLevel m_level;
                std::string m_format;
                std::source_location m_source;
				std::vector<NamedFormatSpecifier> m_specifiers;
        };

    }

	void initialize();
	void shutdown();

    // Note for all logging functions:
    // Constructor automatically submits the log message for output if the message format string does not contain named arguments.
    // Otherwise, log submit is done by calling format(...) and providing the appropriate named arguments.
    
    DEFINE_LOG_LEVEL(info);
    DEFINE_LOG_LEVEL(debug);
    DEFINE_LOG_LEVEL(warning);
    DEFINE_LOG_LEVEL(error);
    
}

// Template definitions.
#include "logging/internal/logging.tpp"

#endif // LOGGING_LOGGING_HPP
