#include "Engine.h"
#include "raylib.h"

Engine::Engine() {
    isRunning = false;
}

bool Engine::initialize(int width, int height, const string &title, int framerate, bool fullscreen) {
    InitWindow(width, height, title.c_str());
    if (fullscreen) {
        ToggleFullscreen();
    }
    SetTargetFPS(framerate);
    isRunning = IsWindowReady();
    return isRunning;
}

void Engine::run() {
    while (!WindowShouldClose() && isRunning) {
        float deltaTime = GetFrameTime();

        if (isKeyPressed(KEY_ESCAPE)) {
            close();
        }

        BeginDrawing();
        screenClear(RED);
        DrawText(TextFormat("MOJANG"), 550, 450, 200, WHITE);
        DrawText(TextFormat("Loading..."), 750, 750, 100, WHITE);
        EndDrawing();
    }
    if (IsWindowReady()) {
        CloseWindow();
    }
}

void Engine::close() {
    isRunning = false;
}

void Engine::screenClear(Color color) {
    ClearBackground(color);
}

void Engine::logMessage(const string &message) {
    printf("%s\n", message.c_str());
}

bool Engine::isKeyPressed(int key) {
    return IsKeyDown(key);
}

bool Engine::isMousePressed(int button) {
    return IsMouseButtonPressed(button);
}

Vector2 Engine::getMousePosition() {
    return GetMousePosition();
}
