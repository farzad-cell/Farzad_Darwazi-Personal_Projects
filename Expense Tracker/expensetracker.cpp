//
// Created by Farzad Darwazi on 9/26/2025.
//

#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

int main() {

    string date;
    string category;
    float cost, expense, total = 0.0;

    map<string, map<string, float>> sort;

    cout<<"Welcome to expenseTracker!"<<endl;
    cout<<endl<<"Please enter number of expenses: ";
    cin>>expense;


    for (int i = 1; i <= expense; i++) {
        cout<<"Please enter requirements for expense #"<< i <<endl;

        cout << setprecision(2) << fixed;

        cout<<"Please enter date (mm-dd-yyyy): ";
        cin>>date;

        cout<< endl << "Please enter category: ";
        cin>>category;

        cout <<"Please enter the cost: ";
        cin>>cost;
        cout << endl;

        sort[date][category] += cost;

        total += cost;
        }
    cout<<"----------------------------"<<endl;
    cout<<"Spending(s):"<<endl;

    for (auto &s : sort) {
        cout << s.first <<endl;
        for (auto  &t: s.second) {
            cout << t.first << ": $" << t.second <<endl;
        }
    }
    cout<<endl<<"----------------------"<<endl;
    cout<<"Total expense $"<<total<<endl;
    }

