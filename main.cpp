#include <iostream>
#include <math.h>

using namespace std;

constexpr float E = 0.1;
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

long double bisection(Polynom equation, Polynom derivative, long double *leftBorder, long double *rightBorder) {
    long double c;
    c = (*leftBorder + *rightBorder) / 2;
    long double solution = equation.calculate(c);
    while(abs(solution) >= E) {
        if ((solution < -E && derivative.calculate(c) > 0) || (solution > E && derivative.calculate(c) < 0)) {
            *leftBorder = c;
            c = (*leftBorder + *rightBorder) / 2;
        } else {
            *rightBorder = c;
            c = (*leftBorder + *rightBorder) / 2;
        }
        solution = equation.calculate(c);
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

void checkMultiplicity(Polynom equation, long double root, double alpha, double beta) {
    if (pow(abs(equation.b / 3), 2) == abs(equation.c / 3) && abs((equation.c / 3) * (equation.b) / 3) == abs(equation.d)) {
        cout << "ROOT: " << root << " MULTIPLICITY: 3" << endl;
    } else if (root == alpha || root == beta) {
        cout << "ROOT: " << root << " MULTIPLICITY: 2" << endl;
    } else {
        cout << "ROOT: " << root << " MULTIPLICITY: 1" << endl;
    }
}

int main() {
    double a, b, c, d, Discriminant, alpha, beta;
    long double leftBorder = INFINITY, rightBorder = INFINITY, root;
    cin >> a >> b >> c >> d;
    Polynom equation = *new Polynom(a, b, c, d);
    Polynom derivative = *new Polynom(0, 3, 2 * b, c);

    Discriminant = CalcDiscriminant(derivative.b, derivative.c, derivative.d);

    if (Discriminant < -E) {
        if (abs(equation.calculate(0)) < E) {
            cout << "ROOT: 0" << endl;
        } else if (equation.calculate(0) > E) {
            rightBorder = 0;
            findLeftBorder(equation, &rightBorder, &leftBorder);
            root = bisection(equation, derivative, &leftBorder, &rightBorder);
            checkMultiplicity(equation, root, alpha, beta);
        } else {
            leftBorder = 0;
            findRightBorder(equation, &rightBorder, &leftBorder);
            root = bisection(equation, derivative, &leftBorder, &rightBorder);
            checkMultiplicity(equation, root, alpha, beta);
        }
    } else {
        alpha = (-derivative.c - sqrt(Discriminant)) / (2 * derivative.b);
        beta = (-derivative.c + sqrt(Discriminant)) / (2 * derivative.b);
        if (equation.calculate(alpha) < -E && equation.calculate(beta) < -E) {
            leftBorder = beta;
            findRightBorder(equation, &rightBorder, &leftBorder);
            root = bisection(equation, derivative, &leftBorder, &rightBorder);
            checkMultiplicity(equation, root, alpha, beta);
        } else if (equation.calculate(alpha) > E && equation.calculate(beta) > E) {
            rightBorder = alpha;
            findLeftBorder(equation, &rightBorder, &leftBorder);
            root = bisection(equation, derivative, &leftBorder, &rightBorder);
            checkMultiplicity(equation, root, alpha, beta);
        } else if (equation.calculate(alpha) > E && equation.calculate(beta) < -E) {
            rightBorder = alpha;
            findLeftBorder(equation, &rightBorder, &leftBorder);
            root = bisection(equation, derivative, &leftBorder, &rightBorder);
            checkMultiplicity(equation, root, alpha, beta);

            leftBorder = beta;
            findRightBorder(equation, &rightBorder, &leftBorder);
            root = bisection(equation, derivative, &leftBorder, &rightBorder);
            checkMultiplicity(equation, root, alpha, beta);

            rightBorder = beta;
            leftBorder = alpha;
            root = bisection(equation, derivative, &leftBorder, &rightBorder);
            checkMultiplicity(equation, root, alpha, beta);
        } else if (equation.calculate(alpha) > E && abs(equation.calculate(beta)) < E) {
            checkMultiplicity(equation, beta, alpha, beta);
            rightBorder = alpha;
            findLeftBorder(equation, &rightBorder, &leftBorder);
            root = bisection(equation, derivative, &leftBorder, &rightBorder);
            checkMultiplicity(equation, root, alpha, beta);
        } else if (abs(equation.calculate(alpha)) < E && equation.calculate(beta) < -E) {
            checkMultiplicity(equation, alpha, alpha, beta);
            leftBorder = beta;
            findRightBorder(equation, &rightBorder, &leftBorder);
            root = bisection(equation, derivative, &leftBorder, &rightBorder);
            checkMultiplicity(equation, root, alpha, beta);
        } else {
            rightBorder = beta;
            leftBorder = alpha;
            root = bisection(equation, derivative, &leftBorder, &rightBorder);
            checkMultiplicity(equation, root, alpha, beta);
        }
    }
    return 0;
}