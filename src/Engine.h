#ifndef SILNK2D_ENGINE_H
#define SILNK2D_ENGINE_H
#include <raylib.h>
#include <string>

using namespace std;

class Engine {
private:
    bool isRunning;
public:
    Engine();
    bool initialize(int width, int height, const string &title, int framerate, bool fullscreen);
    void run();
    void close();
    void screenClear(Color color = RED);
    void logMessage(const string &message);
    bool isKeyPressed(int key);
    bool isMousePressed(int button);
    Vector2 getMousePosition();
};


#endif