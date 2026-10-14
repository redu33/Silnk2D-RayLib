#include "Engine.h"
#include "raylib.h"

int main(){

    const unsigned int width = 800;
    const unsigned int height = 600;
    const string title = "Okno";
    int framerate = 60;
    bool fullscreen = true;

    Engine engine;

    if (engine.initialize(width, height, title, framerate, fullscreen)) {
        engine.run();
    } else {
        return 1;
    }
    return 0;
}