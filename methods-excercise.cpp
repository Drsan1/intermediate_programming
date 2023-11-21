#include <cassert>
#include <iostream>

/*
 * Doimplementujte metody struktury Rectangle
 */

struct Point {
    int x;
    int y;
};

struct Rectangle {
    Point topLeft;
    Point bottomRight;

    int width() const {
        return abs(topLeft.x - bottomRight.x);
    }
    int height() const {
        return abs(bottomRight.y - topLeft.y);
    }
    int area() const {
        return height() * width();
    }
    bool contains(const Point& p) const {
        if (p.x >= topLeft.x && p.x <= bottomRight.x) {
            if (p.y >= topLeft.y && p.y <= bottomRight.y) {
                return true;
            }
        }
        return false;
    }
    void move(int dx, int dy) {
        topLeft.x = topLeft.x + dx;
        topLeft.y = topLeft.y + dy;
        bottomRight.x = bottomRight.x + dx;
        bottomRight.y = bottomRight.y + dy;
    }
};

int main() {
    Rectangle r = { { 0, 0 }, { 10, 10 } };
    const Rectangle& cr = r;
    assert(cr.width() == 10);
    assert(cr.height() == 10);
    assert(cr.area() == 100);
    assert(cr.contains({ 5, 5 }));
    assert(!cr.contains({ -1, -1 }));
    assert(!cr.contains({ 11, 11 }));

    r.move(1, 1);
    assert(cr.contains({ 5, 5 }));
    assert(!cr.contains({ -1, -1 }));
    assert(cr.contains({ 11, 11 }));

    std::cout << "All tests passed!\n";
}
