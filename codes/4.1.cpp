#include <iostream>
#include <cmath>
using namespace std;

class Circle {
    double radius;
public:
    Circle(double r){
        radius=r;
    }

    double calculateArea() const {
        return 3.14 * radius * radius;
    }

    double getRadius() const {
        return radius;
    }
};

int main() {
    const int numCircles = 3;
    Circle circles[numCircles] = { Circle(3.0), Circle(5.0), Circle(7.5) };

    for (int i = 0; i < numCircles; ++i) {
        cout<< "Circle " << (i + 1)
                  << " Radius: " << circles[i].getRadius()
                  << "Area: " << circles[i].calculateArea() << endl;
    }

    return 0;
}