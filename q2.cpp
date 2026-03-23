#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Shape {
protected:
    string color;
    double x, y; // position
    double borderThickness;

public:
    Shape(double x, double y, string color, double border = 1.0)
        : x(x), y(y), color(color), borderThickness(border) {}

    // Virtual functions
    virtual void draw() {
        cout << "Drawing a generic shape.\n";
    }

    virtual double calculateArea() {
        return 0;
    }

    virtual double calculatePerimeter() {
        return 0;
    }

    virtual void display() {
        cout << "Position: (" << x << ", " << y << ")\n";
        cout << "Color: " << color << endl;
        cout << "Border Thickness: " << borderThickness << endl;
    }

    virtual ~Shape() {}
};

// Circle Class
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double x, double y, string color, double r)
        : Shape(x, y, color), radius(r) {}

    void draw() override {
        cout << "Drawing Circle at (" << x << ", " << y << ") with radius " << radius << endl;
    }

    double calculateArea() override {
        return M_PI * radius * radius;
    }

    double calculatePerimeter() override {
        return 2 * M_PI * radius;
    }
};

// Rectangle Class
class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double x, double y, string color, double w, double h)
        : Shape(x, y, color), width(w), height(h) {}

    void draw() override {
        cout << "Drawing Rectangle at (" << x << ", " << y << ") "
             << "Width: " << width << ", Height: " << height << endl;
    }

    double calculateArea() override {
        return width * height;
    }

    double calculatePerimeter() override {
        return 2 * (width + height);
    }
};

// Triangle Class
class Triangle : public Shape {
private:
    double a, b, c; // sides

public:
    Triangle(double x, double y, string color, double a, double b, double c)
        : Shape(x, y, color), a(a), b(b), c(c) {}

    void draw() override {
        cout << "Drawing Triangle at (" << x << ", " << y << ") "
             << "Sides: " << a << ", " << b << ", " << c << endl;
    }

    double calculatePerimeter() override {
        return a + b + c;
    }

    double calculateArea() override {
        // Heron's Formula
        double s = calculatePerimeter() / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
};

// Polygon Class 
class Polygon : public Shape {
private:
    int sides;
    double sideLength;

public:
    Polygon(double x, double y, string color, int n, double length)
        : Shape(x, y, color), sides(n), sideLength(length) {}

    void draw() override {
        cout << "Drawing Polygon at (" << x << ", " << y << ") "
             << "Sides: " << sides << ", Side Length: " << sideLength << endl;
    }

    double calculatePerimeter() override {
        return sides * sideLength;
    }

    double calculateArea() override {
        // Regular polygon area formula
        return (sides * sideLength * sideLength) /
               (4 * tan(M_PI / sides));
    }
};

int main() {
    vector<Shape*> shapes;

    shapes.push_back(new Circle(0, 0, "Red", 5));
    shapes.push_back(new Rectangle(2, 3, "Blue", 4, 6));
    shapes.push_back(new Triangle(1, 1, "Green", 3, 4, 5));
    shapes.push_back(new Polygon(0, 0, "Yellow", 6, 3));

    for (Shape* s : shapes) {
        s->display();
        s->draw();
        cout << "Area: " << s->calculateArea() << endl;
        cout << "Perimeter: " << s->calculatePerimeter() << endl;
        cout << "-------------------------\n";
    }

    // Free memory
    for (Shape* s : shapes) {
        delete s;
    }

    return 0;
}
