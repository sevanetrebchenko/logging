
#include "logging/logging.hpp"
#include <string>

int main() {
    logging::add_format_specifier<double>('c', [](const double& value) -> std::string {
    });
    logging::info("asdf %i", 10);
    return 0;
}