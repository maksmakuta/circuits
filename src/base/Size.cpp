#include "Size.h"

namespace circuits {

    Size::Size() : width(0), height(0) {}
    Size::Size(const int w, const int h) : width(w), height(h) {}
    Size::Size(const int b) : width(b), height(b) {}

}