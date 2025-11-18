#ifndef CIRCUITS_SIZE_H
#define CIRCUITS_SIZE_H

namespace circuits {

    struct Size {
        Size();
        Size(int w, int h);

        explicit Size(int b);

        int width, height;
    };

}

#endif //CIRCUITS_SIZE_H