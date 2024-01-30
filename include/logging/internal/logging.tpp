
#ifndef LOGGING_LOGGING_TPP
#define LOGGING_LOGGING_TPP

#include "utils/result.hpp"
#include "logging/format.hpp"
#include <string> // std::string
#include <source_location> // std::source_location
#include <tuple> // std::tuple
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <regex> // std::regex

#include <iostream>
#include <iomanip>

namespace logging {
 
	namespace internal {
        
        utils::Response validate_format_string(const std::string& format) {
            bool is_open = false;
            int specifier_start = -1;
            
            for (unsigned i = 0u; i < format.length(); ++i) {
                if (is_open) {
                    if (format[i] == '{') {
                        if (specifier_start == static_cast<int>(i - 1u)) {
                            // Escaped '{' character - '{{'.
                            continue;
                        }
                        else {
                            return utils::Response::NOT_OK("invalid format string - extraneous / unescaped opening brace encountered at position " + std::to_string(i + 1u));
                        }
                    }
                    else if (std::isspace(format[i])) {
                    
                    }
                    else if (format[i] == '}') {
                        is_open = false;
                    }
                }
                else {
                    if (format[i] == '{') {
                    }
                    else if (format[i] == '}') {
                    
                    }
                }
            
        }
        
        
        void invalid_format_string(const std::string& format, std::uint32_t offset, const std::string& message) {
            std::cout << "invalid format string: " << message << std::endl;
            std::cout << format << std::endl;
            std::cout << std::setw(offset + 1u) << std::setfill(' ') << '^' << std::endl;
        }
        
        
		// Log implementation
		template<typename ...Ps>
        Log::Log(logging::MessageLevel level, const std::string& format, std::tuple<Ps...> positional_arguments, std::source_location source) : m_level(level),
                                                                                                                                                m_source(source) {
            // Verify all custom type formatters are present.
            // Note: fundamental (built-in) types do not require custom formatters.
            if (((!std::is_fundamental<Ps>::value && !get_type_formatter<Ps>()) || ...)) {
                throw std::runtime_error("");
            }
            
            // Auto-numbered and positional specifiers are processed
            struct PositionalFormatSpecifier {
                std::uint32_t offset;
            };
            std::vector<PositionalFormatSpecifier> specifiers;
            
            // Validate format string
            bool has_specifier_decorators = false; // True if the format string is composed of only positional / keyword format specifiers, false otherwise.
            bool open = false;
            int start = -1;

            std::stringstream builder { };

            for (unsigned i = 0u; i < format.length(); ++i) {
                if (open) {
                    if (format[i] == '{') {
                        if (start == static_cast<int>(i - 1u)) {
                            // Escaped '{' character, skip.
                            continue;
                        }
                        else {
                        }
                    }
                    else if (format[i] == '}') {
                        open = false;
                        
                        // Get the format specifier without the starting or ending braces.
                        std::string specifier = format.substr(start + 1u, i - start - 1u);
                        
                        if (specifier.empty()) {
                            // Auto-numbered format specifier.
                            if (m_specifiers.empty()) {
                                has_specifier_decorators = false;
                            }
                            else {
                            
                            }
                        }
                        else {
                            if (std::regex_match(specifier, std::regex("^[0-9]+$"))) {
                                // Positional format specifier.
                                unsigned position = strtoul(specifier.c_str(), nullptr, 10);
                                std::cout << "positional " << position << std::endl;
                                
                                if (has_specifier_decorators) {
                                
                                }
                                else {
                                
                                }
                            }
                            else {
                                // Named format specifier.
                                if (std::regex_match(specifier, std::regex("^[a-zA-Z_][a-zA-Z0-9_]*$"))) {
                                
                                }
                                else {
                                    // Specifier name is not valid.
                                }
                            }
                        }
                        
                    }
                }
                else {
                    if (format[i] == '{') {
                        open = true;
                        start = static_cast<int>(i);
                    }
                    else if (format[i] == '}') {
                    
                    }
                }
                
                builder << format[i];
                
                
//
//
//
//                if (open) {
//                    if (format[i] == '{') {
//                        if (i == start - 1) {
//                            // Escaped '{' character, skip.
//                            continue;
//                        }
//                        else {
//                            // Unescaped '{' character.
//                            throw std::runtime_error("");
//                        }
//                    }
//                    else if (format[i] == '}') {
//                        // Closing brace.
//                        open = false;
//                        std::string specifier = format.substr(std::max(start + 1, 0), i - start - 1);
//
//                        if (specifier.empty()) {
//                            // Auto-numbered format specifier.
//                            std::cout << "autonumbered " << std::endl;
//                        }
//                        else {
//                            std::regex expression("^[0-9]+$", std::regex_constants::icase);
//                            if (std::regex_match(specifier, expression)) {
//                                // Positional format specifier.
//                                unsigned position = strtoul(specifier.c_str(), nullptr, 10);
//                                std::cout << "positional " << position << std::endl;
//                            }
//                            else {
//                                // Named format specifier.
//                                std::cout << "named " << specifier << std::endl;
//                            }
//                        }
//                    }
//                    else if (std::isspace(format[i])) {
//                        // Spaces in format specifiers are not allowed.
//                        throw std::runtime_error("");
//                    }
//                }
//                else {
//                    if (format[i] == '{') {
//                        open = true;
//                        start = static_cast<int>(i);
//                    }
//                    else if (format[i] == '}') {
//                        if (i == format.length() - 1u) {
//                            // Closing brace with no matching opening brace or unescaped '}' character.
//                            throw std::runtime_error("reached unexpected eol while parsing");
//                        }
//                        else if (format[i + 1u] == '}') {
//                            // Escaped '}' character, skip.
//                            continue;
//                        }
//                        else {
//                            // Unescaped '}' character.
//                            throw std::runtime_error("");
//                        }
//                    }
//                }
            }

            if (open) {
                throw std::runtime_error("invalid format string");
            }

            // Parse and replace positional arguments


            // Parse and save named positional arguments
		}

	}

	// info implementation
	template<typename ...Ps>
	info<Ps...>::info(std::string format, const Ps& ...positional_arguments, std::source_location source) : internal::Log(MessageLevel::Info, format, std::make_tuple(positional_arguments...), source) {
	}

}

#endif // LOGGING_LOGGING_TPP
