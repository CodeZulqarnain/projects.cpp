#include <iostream>
#include <iomanip>
using namespace std;

class Distance {
private:
    int feet;
    int inches;

    // Normalize inches so it's always less than 12
    void normalize() {
        if (inches >= 12) {
            feet += inches / 12;
            inches = inches % 12;
        }
    }

public:
    // Constructor with default values
    Distance(int f = 0, int i = 0) : feet(f), inches(i) {
        normalize();
    }

    // Setter
    void setDistance(int f, int i) {
        feet = f;
        inches = i;
        normalize();
    }

    // Getter
    void getDistance() const {
        cout << feet << " feet " << inches << " inches";
    }

    // Operator overloading for addition
    Distance operator+(const Distance& other) const {
        Distance temp(feet + other.feet, inches + other.inches);
        temp.normalize();
        return temp;
    }
};

int main() {
    Distance d1, d2;

    // User input
    int f, i;
    cout << "Enter first distance:\n";
    cout << "Feet: "; cin >> f;
    cout << "Inches: "; cin >> i;
    d1.setDistance(f, i);

    cout << "\nEnter second distance:\n";
    cout << "Feet: "; cin >> f;
    cout << "Inches: "; cin >> i;
    d2.setDistance(f, i);

    // Addition using overloaded +
    Distance total = d1 + d2;

    // Output
    cout << "\nFirst Distance: ";
    d1.getDistance();
    cout << "\nSecond Distance: ";
    d2.getDistance();
    cout << "\nTotal Distance: ";
    total.getDistance();

    cout << "\n";
    return 0;
}