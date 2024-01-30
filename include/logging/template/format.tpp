
#ifndef LOGGING_FORMAT_TPP
#define LOGGING_FORMAT_TPP

#include <memory> // std::unique_ptr
#include <unordered_map> // std::unordered_map
#include <typeindex>

namespace logging {
    
    namespace internal {
        
        struct Formatter {
            virtual ~Formatter();
            virtual std::string format(const void* object) const = 0;
        };
        
        template <typename T>
        class TypeFormatter final : public Formatter {
            public:
                explicit TypeFormatter(std::function<std::string(const T&)> formatter);
                ~TypeFormatter() override;
            
            private:
                [[nodiscard]] std::string format(const void* object) const override;
                std::function<std::string(const T&)> m_formatter;
        };
        
        // TypeFormatter definitions
        template <typename T>
        TypeFormatter<T>::TypeFormatter(std::function<std::string(const T&)> formatter) : Formatter(),
                                                                                          m_formatter(std::move(formatter))
                                                                                          {
        }
        
        template <typename T>
        TypeFormatter<T>::~TypeFormatter() = default;

        template <typename T>
        std::string TypeFormatter<T>::format(const void* object) const {
            return m_formatter(*reinterpret_cast<const T*>(object));
        }
        
        extern std::unordered_map<std::type_index, std::shared_ptr<Formatter>> formatters;
        
        template <typename T>
        std::shared_ptr<Formatter> get_type_formatter() {
            using Type = std::remove_cv<typename std::remove_reference<T>::type>::type;
            auto iter = formatters.find(typeid(Type));
            return iter == formatters.end() ? std::shared_ptr<Formatter>(nullptr) : iter->second;
        }
        
    }
    
    template <typename T>
    void register_type_formatter(std::function<std::string(const T&)> formatter) {
        using namespace internal;
        using Type = std::remove_cv<typename std::remove_reference<T>::type>::type;
        formatters[typeid(Type)] = std::make_shared<TypeFormatter<T>>(std::move(formatter)); // Potential overwrite.
    }

}

#endif // LOGGING_FORMAT_TPP
