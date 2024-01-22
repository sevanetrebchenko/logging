
#ifndef LOGGING_LOGGING_TPP
#define LOGGING_LOGGING_TPP

#include "logging/message.hpp"
#include <string> // std::string
#include <source_location> // std::source_location
#include <tuple> // std::tuple
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream

namespace logging {

	namespace internal {

		// Log implementation
		template<typename ...Ps>
			Log::Log(logging::MessageLevel level, const std::string& format, std::tuple<Ps...> positional_arguments, std::source_location source) : m_level(level),
																																				    m_source(source) {
				// Validate format string
				bool open = false;
				int start = -1;

				std::stringstream builder { };

				for (unsigned i = 0u; i < format.length(); ++i) {
					if (open) {
						if (format[i] == '{') {
							if (i == start - 1) {
								// Escaped '{' character, skip.
								continue;
							}
							else {
								// Unescaped '{' character.
								throw std::runtime_error("");
							}
						}
						else if (format[i] == '}') {
							// Closing brace.
							open = false;
							std::string specifier = format.substr(std::max(start, 0), i - start);

							if (specifier.empty()) {

							}
							else {
								bool is_number = true;
								for (char c : specifier) {
									if (!std::isdigit(c)) {
										is_number = false;
										continue;
									}
								}

								if (is_number) {

								}
								else {
									// Named format specifier.
								}
							}

							else if (std::stoi(specifier)) {

							}

							m_specifiers.emplace_back(specifier);
						}
						else if (std::isspace(format[i])) {
							// Spaces in format specifiers are not allowed.
							throw std::runtime_error("");
						}
					}
					else {
						if (format[i] == '{') {
							open = true;
							start = static_cast<int>(i);
						}
						else if (format[i] == '}') {
							if (i == format.length() - 1u) {
								// Closing brace with no matching opening brace or unescaped '}' character.
								throw std::runtime_error("reached unexpected eol while parsing");
							}
							else if (format[i + 1u] == '}') {
								// Escaped '}' character, skip.
								continue;
							}
							else {
								// Unescaped '}' character.
								throw std::runtime_error("");
							}
						}
					}
				}

				if (open) {
					throw std::runtime_error("invalid format string");
				}

				// Parse and replace positional arguments


				// Parse and save named positional arguments
		}

		template<typename ...Ps>
		template<typename ...Ns>
		void Log<Ps...>::format(const Ns& ... named_arguments) const {
		}

	}

	// info implementation
	template<typename ...Ps>
	info<Ps...>::info(std::string format, const Ps& ...positional_arguments, std::source_location source) : internal::Log<Ts...>(format, args..., source) {
	}

}

#endif // LOGGING_LOGGING_TPP
