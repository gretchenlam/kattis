#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double aCalculate(double a, int d){
    return (a * cosh(d / (2 * a)) - a);
}

double aApproximate(int d, int s){
    double min = 0;
    double max = 1000000000000;
    double mid = (min + max) / 2;
    double aCalculated = aCalculate(mid, d);
    
    while(max - min > 0.0000000000001){
        mid = (min + max) / 2;
        aCalculated = aCalculate(mid, d);
        if (s < aCalculated){
            min = mid;
        }else if(s > aCalculated){
            max = mid;
        }else{
            return mid;
        }
    }
    return mid;
}

int main(){
    int d, s = 0;
    cin >> d >> s;
    double a = aApproximate(d, s);
    
    double l = (2 * a * sinh(d / (2 * a)));
    
    cout << fixed << setprecision(9);
    cout << l;
    
    return 0;
}