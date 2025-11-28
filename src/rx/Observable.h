#ifndef CIRCUITS_OBSERVABLE_H
#define CIRCUITS_OBSERVABLE_H

#include <functional>
#include <vector>

namespace circuits {

    template<typename T>
    class Observable {
    public:
        using Observer = std::function<void(const T&)>;

        explicit Observable(const T& value = {}) : m_value(value) {}
        ~Observable() {
            for (auto& observer : m_observers) {
                observer = nullptr;
            }
            m_observers.clear();
        }

        Observable<T>& operator = (const T& value) {
            setValue(value);
            return *this;
        }

        void setValue(const T& value) {
            if (m_value != value) {
                m_value = value;
                for (const auto& observer : m_observers) {
                    observer(m_value);
                }
            }
        }

        T getValue() const {
            return m_value;
        }

        void observe(const Observer& observer) {
            m_observers.push_back(observer);
        }

    private:
        T m_value;
        std::vector<Observer> m_observers;
    };

}

#endif //CIRCUITS_OBSERVABLE_H