#include "Primitives.h"
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

void Point2D::draw(PrimitiveRenderer &renderer, Color color){
    renderer.drawPoint(*this, color);
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

void PrimitiveRenderer::drawLineIncremental(Point2D p1, Point2D p2, Color color){
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
            drawPoint({(int)round(x), (int)round(y)}, color);
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
            drawPoint({(int)round(x), (int)round(y)}, color);
            x += m;
        }
    }
}

void PrimitiveRenderer::drawPolyline(vector<Point2D> &points, Color color, bool isClosed) {
    if (points.size() < 2) {
        return;
    }

    for (int i = 0; i < points.size() - 1; i++) {
        LineSegment segment(points[i], points[i + 1]);
        segment.draw(*this, color, true);
    }

    if (isClosed) {
        LineSegment segment(points.back(), points.front());
        segment.draw(*this, color, true);
    }
}

LineSegment::LineSegment(Point2D start, Point2D end) {
    this->start = start;
    this->end = end;
}

Point2D LineSegment::getStart() {
    return start;
}

Point2D LineSegment::getEnd() {
    return end;
}

void LineSegment::setStart(Point2D start) {
    this->start = start;
}

void LineSegment::setEnd(Point2D end) {
    this->end = end;
}

void LineSegment::draw(PrimitiveRenderer &renderer, Color color, bool isIncremental){
    if (isIncremental) {
        renderer.drawLineIncremental(this->start, this->end, color);
    } else {
        renderer.drawLine(this->start, this->end, color);
    }
}
