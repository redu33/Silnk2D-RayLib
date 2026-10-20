#include "Engine.h"

int main(){
    Engine engine;
    if (engine.init()) {
        engine.run();
    }
    engine.shutdown();
    return 0;
}