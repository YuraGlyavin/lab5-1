#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

double f(double x) {
    return 2*sin(1/(x*x))/(1+x*x);
}

double rect(double a, double b, double h) {
    double I = 0;
    for(double x = a; x < b; x += h)
        I += f(x)*h;
    return I;
}

double trapez(double a, double b, double h) {
    double result = h*0.5*(a + b);
    int i = 0;
    for(double x = a+h; x < b-h; x = a + h + i*h){
        result += h*f(x);
        i++;
    }
    return result;
}

int main() {
    double eps = 1e-5;
    double a = 1, b = 1;
    do {
    	a /= 2;
    } while(2*atan(a) >= eps/2.);

    double h = 0.1;
    double err;
    do {
        double first = rect(a, b, h);
        h /= 2.;
        double second = rect(a, b, h);
        err = abs(first - second)/3.;
    } while(err >= eps/2.);
    ofstream file;
    file.open("ans1.dat", ios_base::out);
    file << rect(a, b, h) << " " << err << endl;
    file.close();

    h = 0.1;
    do {
        double first = trapez(a, b, h);
        h /= 2.;
        double second = trapez(a, b, h);
        err = abs(first - second)/3.;
    } while(err >= eps/2.);
    file.open("ans2.dat", ios_base::out);
    file << trapez(a, b, h) << " " << err << endl;
    file.close();
    return 0;
}
