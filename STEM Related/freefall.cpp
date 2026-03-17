// Created by Farzad Darwazi on 9/20/2025.

#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

int main() {

    int time, second;
    float height;
    float distance, g = 9.80;

    cout << "Please enter the time of the free fall in (seconds): ";
    cin >> time;
    cout << "Please enter the height of the free fall in (meters): ";
    cin >> height;

    cout <<"Time(seconds) Height(meters)"
             <<"\n****************************" << endl;

    for (second = 0; second <= time; second++) {


        distance = 0.5 * g * pow(second, 2);

        if (distance > height) {

            cout << "!!The fallen distance cannot be greater than the original height!!" << endl;

            break;
        }

        cout << second << "   <----------->   " << distance<< endl;

    }

    return 0;
}
