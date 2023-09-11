#include <iostream>
#include <math.h>

using namespace std;

constexpr float E = 0.01;
constexpr int delta = 1;

class Polynom {
public:
    double a, b, c, d;

    Polynom(double a, double b, double c, double d) {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
    }

    long double calculate(long double x) {
        return (a * pow(x, 3) + b * pow(x, 2) + c * x + d);
    }
};

double CalcDiscriminant(double a, double b, double c) {
    return (b * b - 4 * a * c);
}

long double bisection(Polynom equation, long double *leftBorder, long double *rightBorder) {
    long double c = (*rightBorder - *leftBorder) / 2;
    long double solution = abs(equation.calculate(c));
    while(solution < E) {
        if (solution < -E) {
            *leftBorder = c;
            c = (*rightBorder - *leftBorder) / 2;
        } else {
            *rightBorder = c;
            c = (*rightBorder - *leftBorder) / 2;
        }
        solution = abs(equation.calculate(c));
    }
    return c;
}

void findRightBorder(Polynom equation, long double *rightBorder, long double *leftBorder) {
    long double k = 1;
    *rightBorder = *leftBorder + k * delta;
    while(equation.calculate(*rightBorder) < 0) {
        *rightBorder = *leftBorder + k * delta;
        k *= 2;
    }
}

void findLeftBorder(Polynom equation, long double *rightBorder, long double *leftBorder) {
    long double k = 1;
    *leftBorder = *rightBorder - k * delta;
    while(equation.calculate(*leftBorder) > 0) {
        *leftBorder = *rightBorder - k * delta;
        k *= 2;
    }
}

int main() {
    double a, b, c, d, Discriminant;
    long double leftBorder = INFINITY, rightBorder = INFINITY;
    cin >> a >> b >> c >> d;
    Polynom equation = *new Polynom(a, b, c, d);
    Polynom derivated = *new Polynom(0, 3, 2 * a, b);

    Discriminant = CalcDiscriminant(derivated.b, derivated.c, derivated.d);
    cout << Discriminant << endl;

    if (Discriminant < -E) {
        if (abs(equation.calculate(0)) < E) {
            cout << "ROOT: 0" << endl;
        } else if (equation.calculate(0) > E) {
            rightBorder = 0;
            findLeftBorder(equation, &rightBorder, &leftBorder);
            bisection(equation, &leftBorder, &rightBorder);
        } else {
            leftBorder = 0;
            findRightBorder(equation, &rightBorder, &leftBorder);
            bisection(equation, &leftBorder, &rightBorder);
        }
    } else {

    }

    return 0;
}