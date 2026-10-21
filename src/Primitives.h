#ifndef SILNK2D_PRIMITIVES_H
#define SILNK2D_PRIMITIVES_H
#include <raylib.h>
#include <vector>

using namespace std;

class PrimitiveRenderer;

class Point2D {
private:
    int x;
    int y;

public:
    Point2D();
    Point2D(int x, int y);

    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    void setXY(int x, int y);

    void draw(PrimitiveRenderer &renderer, Color color);
};

class LineSegment {
private:
    Point2D start;
    Point2D end;

public:
    LineSegment(Point2D start, Point2D end);

    Point2D getStart();
    Point2D getEnd();

    void setStart(Point2D start);
    void setEnd(Point2D end);

    void draw(PrimitiveRenderer &renderer, Color color, bool isIncremental);
};

class PrimitiveRenderer {
public:
    void drawPoint(Point2D p, Color color);
    void drawLine(Point2D p1, Point2D p2, Color color);
    void drawRectangle(Point2D p, int width, int height, Color color);
    void drawCircle(Point2D p, float radius, Color color);
    void drawTriangle(Point2D p1, Point2D p2, Point2D p3, Color color);

    void drawLineIncremental(Point2D p1, Point2D p2, Color color);
    void drawPolyline(vector<Point2D> &points, Color color, bool isClosed);
};

#endif