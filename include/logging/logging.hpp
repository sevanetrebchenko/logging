
#ifndef LOGGING_LOGGING_HPP
#define LOGGING_LOGGING_HPP

#include "logging/message.hpp"
#include "logging/level.hpp"
#include <string> // std::string
#include <source_location> // std::source_location
#include <cstdint> // std::uint16_t
#include <vector> // std::vector
#include <tuple> // std::tuple

namespace logging {
    namespace internal {

		struct FormatSpecifier {
			std::uint16_t offset; // Offset
			std::string_view specifier;
		};

        struct Log {
            public:
				// Formats positional arguments.
				template <typename ...Ps>
                Log(MessageLevel level, const std::string& format, std::tuple<Ps...> positional_arguments, std::source_location source);
                ~Log();

				// Formats named arguments.
				template <typename ...Ns>
				void format(const Ns&... named_arguments) const;
            
            private:
				MessageLevel m_level;
                std::string m_format;
                std::source_location m_source;
				std::vector<FormatSpecifier> m_specifiers;
        };

    }

	void initialize();
	void shutdown();

    // Note for all logging functions:
    // Constructor automatically submits the log message for output if the message format string does not contain named arguments.
    // Otherwise, log submit is done by calling format(...) and providing the appropriate named arguments.
    
    template <typename ...Ps>
    struct info final : internal::Log<Ps...> {
        explicit info(std::string format, const Ps&... positional_arguments, std::source_location source = std::source_location::current());
    };
    template <typename ...Ts>
    info(std::string, const Ts&...) -> info<Ts...>;

 //    void debug(Message message, ...);
//    void warning(Message message, ...);
//    void error(Message message, ...);
    
}

// Template definitions.
#include "logging/template/logging.tpp"

#endif // LOGGING_LOGGING_HPP
