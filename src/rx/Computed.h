#ifndef CIRCUITS_COMPUTED_H
#define CIRCUITS_COMPUTED_H

#include <functional>

#include "State.h"

namespace circuits {

    template<typename T>
    class Computed {
    public:
        using Func = std::function<T()>;

        explicit Computed(Func fn) : fn(std::move(fn)), value(fn()) {}

        void bind(State<T>& st) {
            st.observe([this](auto&) {
                value = fn();
                notify();
            });
        }

        const T& get() const { return value; }

        int observe(std::function<void(const T&)> cb) {
            int id = ++idCounter;
            observers[id] = std::move(cb);
            return id;
        }

    private:
        void notify() {
            for (auto& [id, cb] : observers)
                cb(value);
        }

        Func fn;
        T value;
        int idCounter = 0;
        std::unordered_map<int, std::function<void(const T&)>> observers;
    };

}

#endif //CIRCUITS_COMPUTED_H