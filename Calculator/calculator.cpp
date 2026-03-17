
//Created by Farzad Darwazi on 9/6/2025.


#include <iostream>
#include <cmath>

using namespace std;

int main(){

    double num1, num2, result;
    char op;

    cout << "Welcome to Farzad Darwazi's calculator.\tUse ONLY one operator at a time (+, -, *, /, ^, or 0$ for sqrt).\n Enter (0+0) to exit the calculator" << endl;

    while (true) {
        if (!(cin >> num1 >> op >> num2)) {
            cin.clear();
            cin.ignore(99999, '\n');
            cout << "Invalid operation. Please try again ONLY use numbers and operators. EX, (1+2)" << endl;
            continue;
        }

        if (op == '+' ) {
            result = num1 + num2;
            cout << "Result: " << result << endl;
        }else if (op == '-' ) {
            result = num1 - num2;
            cout << "Result: " << result << endl;
        }else if (op == '*' ) {
            result = num1 * num2;
            cout << "Result: " << result << endl;
        }else if (op == '$' ) {
            if (num2 < 0) {
                cout << "Lol :) Imaginary numbers NOT allowed. Ex, (0$n n>0 0$4,0$16)" << endl;
                continue;
            }
            result = sqrt(num2);
            cout << "Result: " << result << endl;
        }else if (op == '^'){
            result = pow(num1, num2);
            cout << "Result: " << result << endl;
        }else if (op == '/' ) {

            if (num2 == 0) {
                cout << " :D LOL You can NOT divide by zero in math??" << endl;
                continue;
            }
            result = num1 / num2;
            cout << "Result: " << result << endl;
        }

        if (num1 == 0 && op == '+' && num2 == 0) {
            cout << "Thanks for using Farzad's calculator, Bye!" << endl;
            return 0;
        }
    }

}
