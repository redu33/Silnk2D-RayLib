#include "Engine.h"

#include <complex>
#include <functional>
#include <iostream>

bool Engine::init(){
    SetTraceLogLevel(7);

    logInfo("Inicjalizacja silnika...");

    if (config.fullscreen) {
        SetConfigFlags(FLAG_FULLSCREEN_MODE);
    }

    if (config.width <= 0 || config.height <= 0) {
        logError("Nie udalo sie zainicjalizowac silnika.");
        logError("Niepoprawna rozdzielczosc.");
        return false;
    }

    InitWindow(config.width, config.height, config.title.c_str());

    if (!IsWindowReady()) {
        logError("Nie udalo sie zainicjalizowac silnika.");
        return false;
    }

    if (config.FPS > 0) {
        SetTargetFPS(config.FPS);
    } else {
        logError("Nie udalo sie zainicjalizowac silnika.");
        logError("Niepoprawna liczba klatek na sekunde.");
        return false;
    }

    logInfo("Silnik zostal poprawnie zainicjalizowany.");
    return true;
}

void Engine::run(){
    logInfo("Uruchomiono glowna petle.");
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        handleInput();
        updateLogic(deltaTime);
        renderScreen();
    }
    logInfo("Zakonczono glowna petle.");
}

void Engine::shutdown(){
    if (!IsWindowReady()) {
        return;
    }
    logInfo("Zamykanie, zwalnianie zasobow.");
    CloseWindow();
    logInfo("Poprawnie zamknieto.");
}

void Engine::clnScreen(Color color){
    ClearBackground(color);
}

void Engine::logError(const string &logMessage){
    if (config.logs) {
        cerr << "BLAD: " << logMessage << endl;
    }
}

void Engine::logInfo(const string &logMessage){
    if (config.logs) {
        cout << "INFO: " << logMessage << endl;
    }
}

bool Engine::isKeyDown(int key){
    return (config.enableKeyboard && IsKeyDown(key));
}

bool Engine::isKeyPressed(int key){
    return (config.enableKeyboard && IsKeyPressed(key));

}

bool Engine::isMouseDown(int button){
    return (config.enableMouse && IsMouseButtonDown(button));

}

bool Engine::isMousePressed(int button){
    return (config.enableMouse && IsMouseButtonPressed(button));

}

void Engine::handleInput(){
    if (config.enableKeyboard) {
        if (isKeyPressed(KEY_ONE)) {
            config.clearColor = RED;
        }
        if (isKeyPressed(KEY_TWO)) {
            config.clearColor = GREEN;
        }
        if (isKeyPressed(KEY_THREE)) {
            config.clearColor = BLUE;
        }
    }
    if (config.enableMouse) {
        if (isMousePressed(MOUSE_BUTTON_LEFT)) {
            Vector2 pos = GetMousePosition();
            logInfo("Przycisnieto w " + to_string((int)pos.x) + ", " + to_string((int)pos.y) + ".");
        }
    }
}

void Engine::updateLogic(float deltaTime){
    // todo
}

void Engine::renderScreen(){
    BeginDrawing();
    clnScreen(config.clearColor);
    DrawText("Sterowanie: LPM - mysz, 1/2/3 - kolor tla, ESC - wyjscie", 10, 10, 16, BLACK);
    DrawFPS(10, 35);
    Point2D p(100,100);
    Point2D p2(300,300);
    PrimitiveRenderer renderer;
    renderer.drawLine(p, p2, BLACK);
    EndDrawing();
}
