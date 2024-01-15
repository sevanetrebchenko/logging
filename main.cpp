
#include "logging/format.hpp"

int main() {
    logging::add_format_specifier<int>("c", [](const int& value) -> std::string {
        return "test";
    });
    
    return 0;
}