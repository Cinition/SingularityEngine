#include <iostream>
#include "Singularity.h"

int main() {
    sy::Singularity app{};

    try {
        app.Update();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}