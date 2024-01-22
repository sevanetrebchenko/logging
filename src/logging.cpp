
#include "logging/logging.hpp"

namespace logging {

	namespace internal {

		Log::Log(const char* format, std::source_location source) : m_format(format),
																	m_source(source)
																	{
		}

		Log::~Log() = default;

	}
    
}