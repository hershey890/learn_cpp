// vehicle class
// car class
// plane class
// flying car class inherits from both car and plane classes
#include <iostream>

using namespace std;

class Vehicle {
public:
    int v = 0;
    int weight = 0;
    virtual ~Vehicle() {};
    virtual int powerOn() = 0;
    virtual int powerOff() = 0;
};

class Car : public virtual Vehicle {
public:
    int c = 1;
    int weight = 500;
    int powerOn() {
        cout << "Car power on" << endl;
        return 0;
    }

    int powerOff() {
        cout << "Car power off" << endl;
        return 0;
    }
};

class Plane : public virtual Vehicle {
public:
    int p = 2;
    int weight = 100;
    int powerOn() {
        cout << "Plane power on" << endl;
        return 0;
    }

    int powerOff() {
        cout << "Plane power off" << endl;
        return 0;
    }
};

class FlyingCar : public Car, public Plane {
public:
    int f = 3;
    int weight = 300;
    int powerOn() {
        cout << "FlyingCar power on" << endl;
        return 0;
    }

    int powerOff() {
        cout << "FlyingCar power off" << endl;
        return 0;
    }
};

int main() {
    FlyingCar fc;
    fc.weight;
    fc.Plane::weight;
    fc.Plane::Vehicle::weight;
    fc.v;
}