#include "Primitives.h"

Point2D::Point2D(int x, int y) {
    this->x = x;
    this->y = y;
}
int Point2D::getX() {
    return x;
}
int Point2D::getY() {
    return y;
}
void Point2D::setX(int x) {
    this->x = x;
}
void Point2D::setY(int y) {
    this->y = y;
}
void Point2D::setXY(int x, int y) {
    this->x = x;
    this->y = y;
}

void PrimitiveRenderer::drawPoint(Point2D p, Color color) {
    DrawPixel(p.getX(), p.getY(), color);
}

void PrimitiveRenderer::drawLine(Point2D p1, Point2D p2, Color color) {
    DrawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), color);
}

void PrimitiveRenderer::drawRectangle(Point2D p, int width, int height, Color color) {
    DrawRectangle(p.getX(), p.getY(), width, height, color);
}

void PrimitiveRenderer::drawCircle(Point2D p, float radius, Color color) {
    DrawCircle(p.getX(), p.getY(), radius, color);
}

void PrimitiveRenderer::drawTriangle(Point2D p1, Point2D p2, Point2D p3, Color color) {
    Vector2 v1 = {(float)p1.getX(), (float)p1.getY()};
    Vector2 v2 = {(float)p2.getX(), (float)p2.getY()};
    Vector2 v3 = {(float)p3.getX(), (float)p3.getY()};
    DrawTriangle(v1, v2, v3, color);
}