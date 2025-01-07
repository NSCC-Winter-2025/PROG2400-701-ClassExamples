#include <iostream>
#include "best_practices_app.h"

int main() {
    BestPracticesApp app;
    app.read_config();
    app.run();

    return 0;
}
