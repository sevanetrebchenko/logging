
#include "logging/format.hpp"
#include "logging/logging.hpp"

struct Test {
    int a;
};

int main() {
    int hour = 4;
    int minute = 19;
    Test b { };
    
//    logging::info("this is a test formatted string. positional arguments {0} and {1}, named arguments {hour}:{minute}", 10, 20).format(logging::format::arg("hour", hour), logging::format::arg("minute", minute));
    logging::info("{  { } this is a test formatted {} string. positional arguments {0} and {1}, named arguments {hour}:{minute} {", 10, 20, b);
    
    return 0;
}
