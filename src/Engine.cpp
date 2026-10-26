#include "Engine.h"

#include <complex>
#include <functional>
#include <iostream>

bool Engine::init(){
    SetTraceLogLevel(7);

    logInfo("Inicjalizacja silnika.");

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
        shapesToDraw.clear();
        if (isKeyDown(KEY_ONE)) shapesToDraw.push_back(Shape::LINE);
        if (isKeyDown(KEY_TWO)) shapesToDraw.push_back(Shape::RECTANGLE);
        if (isKeyDown(KEY_THREE)) shapesToDraw.push_back(Shape::CIRCLE);
        if (isKeyDown(KEY_FOUR)) shapesToDraw.push_back(Shape::ELLIPSE);
        if (isKeyDown(KEY_FIVE)) shapesToDraw.push_back(Shape::TRIANGLE);
        if (isKeyDown(KEY_SIX)) shapesToDraw.push_back(Shape::POLYGON);
    }
    if (config.enableMouse) {
        if (isMousePressed(MOUSE_BUTTON_LEFT)) {
            Vector2 pos = GetMousePosition();
            logInfo(to_string((int)pos.x) + ", " + to_string((int)pos.y));
        }
    }
}

void Engine::updateLogic(float deltaTime){
    // todo
}

void Engine::renderScreen(){
    BeginDrawing();
    clnScreen(config.clearColor);
    PrimitiveRenderer renderer;

    for (Shape shape : shapesToDraw) {
        switch (shape) {
            case Shape::LINE:
                renderer.drawLine(Point2D(300, 200), Point2D(500, 400), RED);
                break;
            case Shape::RECTANGLE:
                renderer.drawRectangle(Point2D(300, 200), 200, 200, GREEN);
                break;
            case Shape::CIRCLE:
                renderer.drawCircle(Point2D(400, 300), 100, BLUE);
                break;
            case Shape::ELLIPSE:
                renderer.drawEllipse(Point2D(400, 300), 150, 80, YELLOW);
                break;
            case Shape::TRIANGLE:
                renderer.drawTriangle(Point2D(300, 200), Point2D(500, 200), Point2D(400, 400), ORANGE);
                break;
            case Shape::POLYGON:
                vector<Point2D> wielokat = {
                Point2D(400, 200),
                Point2D(500, 270),
                Point2D(460, 380),
                Point2D(340, 380),
                Point2D(300, 270)
            };
                renderer.drawPolygon(wielokat, MAGENTA);
                break;
        }
    }
    EndDrawing();


    // todo zad. 3 i reszta z 3 instr
}