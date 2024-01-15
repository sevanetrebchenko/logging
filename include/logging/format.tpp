
#ifndef LOGGING_FORMAT_TPP
#define LOGGING_FORMAT_TPP

#include <memory> // std::unique_ptr
#include <unordered_map> // std::unordered_map

namespace logging {
    
    namespace internal {
        
        struct Formatter {
            virtual ~Formatter();
            virtual std::string format(const void* object) const = 0;
        };
        
        template <typename T>
        class TypeFormatter final : public Formatter {
            public:
                explicit TypeFormatter(std::string (*formatter)(const T&));
                ~TypeFormatter() override;
            
            private:
                [[nodiscard]] std::string format(const void* object) const override;
                std::string (*m_formatter)(const T&);
        };
        
        // TypeFormatter definitions
        template <typename T>
        TypeFormatter<T>::TypeFormatter(std::string (*formatter)(const T&)) : Formatter(),
                                                                              m_formatter(std::move(formatter))
                                                                              {
        }
        
        template <typename T>
        TypeFormatter<T>::~TypeFormatter() = default;

        template <typename T>
        std::string TypeFormatter<T>::format(const void* object) const {
            return m_formatter(*reinterpret_cast<const T*>(object));
        }
        
        extern std::unordered_map<std::string, std::unique_ptr<Formatter>> formatters;
        
    }
    
    template <typename T>
    void add_format_specifier(const std::string& specifier, std::string (*formatter)(const T&)) {
        using namespace internal;
        
        // TODO: check for collision with standard format specifier strings
        
        auto iter = formatters.find(specifier);
        if (iter == formatters.end()) {
            formatters[specifier] = std::make_unique<TypeFormatter<T>>(formatter); // Potential
        }
    }

}

#endif // LOGGING_FORMAT_TPP