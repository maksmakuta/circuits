#ifndef CIRCUITS_STATE_H
#define CIRCUITS_STATE_H

#include <functional>

namespace circuits {

    template<typename T>
    class State {
    public:
        using Callback = std::function<void(const T&)>;

        State() = default;
        explicit State(const T& v) : value(v) {}

        const T& get() const { return value; }

        void set(const T& v) {
            if (v == value) return;
            value = v;
            notify();
        }

        int observe(Callback cb) {
            int id = ++lastId;
            observers[id] = std::move(cb);
            return id;
        }

    private:
        void notify() {
            for (auto& [id, cb] : observers)
                cb(value);
        }

        T value;
        int lastId = 0;
        std::unordered_map<int, Callback> observers;
    };


}

#endif //CIRCUITS_STATE_H