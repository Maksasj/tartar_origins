#include "to_app.h"

int main() {
    to::TOApp app;

    app.init();
    app.load();
    app.run();
    app.cleanup();
    app.terminate();

    return 0;
}