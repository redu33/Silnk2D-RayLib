#include "Primitives.h"
#include "Engine.h"
#include <math.h>

using namespace std;

Point2D::Point2D(){
    this->x = 0;
    this->y = 0;
}
Point2D::Point2D(int x, int y) {
    this->x = x;
    this->y = y;
}
int Point2D::getX() { return x; }
int Point2D::getY() { return y; }
void Point2D::setX(int x) { this->x = x; }
void Point2D::setY(int y) { this->y = y; }
void Point2D::setXY(int x, int y) {
    this->x = x;
    this->y = y;
}
void Point2D::draw(PrimitiveRenderer &renderer, Color color){
    renderer.drawPoint(*this, color);
}



void PrimitiveRenderer::drawPoint(Point2D p, Color color) {
    DrawPixel(p.getX(), p.getY(), color);
}
void PrimitiveRenderer::drawRectangle(Point2D p, int width, int height, Color color) {
    vector<Point2D> punkty = {
        Point2D(p.getX(), p.getY()),
        Point2D(p.getX() + width, p.getY()),
        Point2D(p.getX() + width, p.getY() + height),
        Point2D(p.getX(), p.getY() + height)
    };
    drawPolyline(punkty, color, true);
}
void PrimitiveRenderer::drawCircle(Point2D p, int R, Color color) {
    int x0 = p.getX();
    int y0 = p.getY();
    float step = 1.0f / R;

    for (float a = 0; a <= M_PI / 2.0f; a += step) {
        int x = R * cos(a) + 0.5f;
        int y = R * sin(a) + 0.5f;
        drawPoint({x0 + x, y0 + y}, color);
        drawPoint({x0 - x, y0 + y}, color);
        drawPoint({x0 + x, y0 - y}, color);
        drawPoint({x0 - x, y0 - y}, color);
    }
}
void PrimitiveRenderer::drawEllipse(Point2D p, int rx, int ry, Color color){
    int x0 = p.getX();
    int y0 = p.getY();
    int maxR = max(abs(rx), abs(ry));
    float step = 1.0f / maxR;

    for (float a = 0; a <= M_PI / 2.0f; a += step) {
        int x = rx * cos(a) + 0.5f;
        int y = ry * sin(a) + 0.5f;
        drawPoint({x0 + x, y0 + y}, color);
        drawPoint({x0 - x, y0 + y}, color);
        drawPoint({x0 + x, y0 - y}, color);
        drawPoint({x0 - x, y0 - y}, color);
    }
}
void PrimitiveRenderer::drawTriangle(Point2D p1, Point2D p2, Point2D p3, Color color) {
    vector<Point2D> punkty = {p1, p2, p3};
    drawPolyline(punkty, color, true);
}
void PrimitiveRenderer::drawPolygon(vector<Point2D> &points, Color color){
    if (points.size() < 3) {
        return;
    }
    drawPolyline(points, color, true);
}

void PrimitiveRenderer::drawLine(Point2D p1, Point2D p2, Color color){
    int dx = p2.getX() - p1.getX();
    int dy = p2.getY() - p1.getY();

    if (abs(dx) >= abs(dy)) {
        if (p1.getX() > p2.getX()) {
            swap(p1, p2);
            dx = p2.getX() - p1.getX();
            dy = p2.getY() - p1.getY();
        }
        float m = (float)dy / (float)dx;
        float y = (float)p1.getY();

        for (int x = p1.getX(); x <= p2.getX(); x++) {
            drawPoint({x, (int)(y + 0.5f)}, color);
            y += m;
        }
    } else {
        if (p1.getY() > p2.getY()) {
            swap(p1, p2);
            dx = p2.getX() - p1.getX();
            dy = p2.getY() - p1.getY();
        }
        float m = (float)dx / (float)dy;
        float x = (float)p1.getX();

        for (int y = p1.getY(); y <= p2.getY(); y++) {
            drawPoint({(int)(x + 0.5f), y}, color);
            x += m;
        }
    }
}
void PrimitiveRenderer::drawPolyline(vector<Point2D> &points, Color color, bool isClosed) {
    if (points.size() < 2) {
        return;
    }
    for (int i = 0; i < points.size() - 1; i++) {
        drawLine(points[i], points[i + 1], color);
    }
    if (isClosed) {
        drawLine(points[points.size() - 1], points[0], color);
    }
}



LineSegment::LineSegment(Point2D start, Point2D end) {
    this->start = start;
    this->end = end;
}
Point2D LineSegment::getStart() { return start; }
Point2D LineSegment::getEnd() { return end; }
void LineSegment::setStart(Point2D start) { this->start = start; }
void LineSegment::setEnd(Point2D end) { this->end = end; }
void LineSegment::draw(PrimitiveRenderer &renderer, Color color){
    renderer.drawLine(this->start, this->end, color);
}