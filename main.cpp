
#include "logging/format.hpp"
#include "logging/logging.hpp"
#include <stdexcept>
#include <iostream>

int main() {
    logging::add_format_specifier<int>("c", [](const int& value) -> std::string {
        return "test";
    });
    
    logging::info("counter value: {}", 0);
    return 0;
}