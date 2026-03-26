// Payroll System.cpp : This file contains the 'main' function. Program 
// execution begins and ends there.
//Farzad Darwazi

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <locale>

// Alieases
using namespace std;
using vecInt = vector<int>;
using vecStr = vector<string>;
using vecDbl = vector<double>;

// Function prototypes
bool loadEmployeeData(vecInt& ids, vecStr& names,
    vecStr& depts, vecDbl& hours, vecDbl& rates,
    string filename);
double calculateGrossPay(double hours, double rate);
double calculateOvertimeHours(double hours);
void displayAllEmployees(const vecInt& ids, const vecStr
    & names, const vecStr& depts, const vecDbl& hours,
    const vecDbl& rates);
void sortByName(vecInt& ids, vecStr& names, vecStr& depts, vecDbl& hours, vecDbl& rates);
void sortByGrossPay(vecInt& ids, vecStr& names, vecStr& depts, vecDbl& hours, vecDbl& rates);
void sortByDepartment(vecInt& ids, vecStr& names, vecStr& depts, vecDbl& hours, vecDbl& rates);
double calculateDepartmentPayroll(const vecStr& depts, const vecDbl& hours, const vecDbl& rates,
       const string& targetDept);
int countEmployeesWithOvertime(const vecDbl& hours);
void displayPayrollSummary(const vecInt& ids, const vecStr& names, const vecStr& depts,
     const vecDbl& hours, const vecDbl& rates);
void addEmployee(vecInt& ids, vecStr& names, vecStr& depts,
    vecDbl& hours, vecDbl& rates);
void removeEmployeeByID(vecInt& ids, vecStr& names, vecStr& depts,
    vecDbl& hours, vecDbl& rates);

int main()
{
    // Create US locale
    locale usLocale("en_US.UTF-8");

    // Imbue cout
    cout.imbue(usLocale);

    vector<int> empIDs;
    vector<string> lastNames;
    vector<string> departments;
    vector<double> hoursWorked;
    vector<double> hourlyRates;




    bool found;
	found = loadEmployeeData(empIDs, lastNames, departments, hoursWorked, hourlyRates,
        "employees.txt");

    if (!found) {
        cout << "Error: Could not load employee data from file." << endl;
        return 1;
    }
    
	cout << "==============================================" << endl;
	cout << "       EMPLOYEE PAYROLL SYSTEM" << endl;
    cout << "==============================================" << endl << endl;
	cout << "MENU" << endl;
	cout << "1. Display all employees (original order)" << endl;
	cout << "2. Sort by name (A-Z)" << endl;
	cout << "3. Sort by gross pay (highest first)" << endl;
	cout << "4. Sort by department" << endl;
	cout << "5. View department payroll breakdown" << endl;
    cout << "6. View payroll summary" << endl;
    cout << "7. Exit" << endl;
    cout << "8. Add a new employee" << endl;
    cout << "9. Remove an employee by ID" << endl;
	cout << "Enter your choice (1-9): " << endl;

    int choice;
    cin >> choice;
    do {
        cout << "MENU" << endl;
        cout << "1. Display all employees (original order)" << endl;
        cout << "2. Sort by name (A-Z)" << endl;
        cout << "3. Sort by gross pay (highest first)" << endl;
        cout << "4. Sort by department" << endl;
        cout << "5. View department payroll breakdown" << endl;
        cout << "6. View payroll summary" << endl;
        cout << "7. Exit" << endl;
        cout << "8. Add a new employee" << endl;
        cout << "9. Remove an employee by ID" << endl;
        cout << "Enter your choice (1-9): " << endl;

		cin >> choice;

        switch (choice) {
        case 1:
            cout << "\nDisplay all employees (original order)" << endl;
            displayAllEmployees(empIDs, lastNames, departments, hoursWorked, hourlyRates);
            break;
        case 2:
            cout << "\nSort by name (A-Z)" << endl;
            sortByName(empIDs, lastNames, departments, hoursWorked, hourlyRates);
            displayAllEmployees(empIDs, lastNames, departments, hoursWorked, hourlyRates);
            break;
        case 3:
            cout << "\nSort by gross pay (highest first)" << endl;
            sortByGrossPay(empIDs, lastNames, departments, hoursWorked, hourlyRates);
            displayAllEmployees(empIDs, lastNames, departments, hoursWorked, hourlyRates);
            break;
        case 4:
            cout << "\nSort by department" << endl;
            sortByDepartment(empIDs, lastNames, departments, hoursWorked, hourlyRates);
            displayAllEmployees(empIDs, lastNames, departments, hoursWorked, hourlyRates);
            break;
        case 5: {
            cout << "\nView department payroll breakdown" << endl;
            // Build a list of unique departments
            vecStr uniqueDepts;
            for (size_t i = 0; i < departments.size(); i++) {
                bool found = false;
                for (size_t j = 0; j < uniqueDepts.size(); j++) {
                    if (departments[i] == uniqueDepts[j]) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    uniqueDepts.push_back(departments[i]);
                }
            }

            // Loop through each unique department
            for (size_t d = 0; d < uniqueDepts.size(); d++) {
                string dept = uniqueDepts[d];
                cout << "Department: " << dept << endl;
                cout << "----------------------------------------------------------------------\n";

                double deptTotal = 0.0;

                // Loop through all employees
                for (size_t i = 0; i < departments.size(); i++) {
                    if (departments[i] == dept) {
                        double otHours = hoursWorked[i] > 40 ? hoursWorked[i] - 40 : 0;
                        double regHours = hoursWorked[i] > 40 ? 40 : hoursWorked[i];
                        double gross = regHours * hourlyRates[i] + otHours * hourlyRates[i] * 1.5;
                        deptTotal += gross;

                        cout << empIDs[i] << " " << lastNames[i] << " "
                            << fixed << setprecision(1) << regHours << " "
                            << otHours << " "
                            << "$" << fixed << setprecision(2) << hourlyRates[i] << " "
                            << "$" << fixed << setprecision(2) << gross << endl;
                    }
                }

                cout << "Department Total: $" << fixed << setprecision(2) << deptTotal << "\n";
            }

            cout << "----------------------------------------------------------------------\n";
            break;
        }
        case 6:
            cout << "\nView payroll summary" << endl;
            displayPayrollSummary(empIDs, lastNames, departments,
                hoursWorked, hourlyRates);
            break;
        case 7:
            cout << "Exiting program. Goodbye!" << endl;
            break;
        case 8:
            addEmployee(empIDs, lastNames, departments, hoursWorked, hourlyRates);
            break;
        case 9:
            removeEmployeeByID(empIDs, lastNames, departments, hoursWorked, hourlyRates);
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 9." << endl;
            break;
        }
        cout << endl;

    } while (choice != 7);
    

	return 0;
}

bool loadEmployeeData(vecInt& ids, vecStr& names,
    vecStr& depts, vecDbl& hours, vecDbl& rates,
    string filename) {

	ifstream inFile(filename);

    if (!inFile) 
        return false;

	int numEmployees;
	inFile >> numEmployees;
	cout << "Loaded " << numEmployees << " from employees.txt" << endl;

    int id;
    string name, dept;
    double empHours, empRate;

    for (int i = 0; i < numEmployees; ++i) {

		inFile >> id >> name >> dept >> empHours >> empRate;

        ids.push_back(id);
        names.push_back(name);
        depts.push_back(dept);
        hours.push_back(empHours);
        rates.push_back(empRate);
    }
    
    inFile.close();
	return true;
}

double calculateGrossPay(double hours, double rate) {

	double minTime = 40.0;
    double overTime = calculateOvertimeHours(hours);
	double regularHours = hours - overTime;
    
	double grossPay = regularHours  * rate + overTime * rate * 1.5;

    return grossPay;
}

double calculateOvertimeHours(double hours) {
    double minTime = 40.0;

    if (hours > minTime) {
        return hours - minTime;
    }
    else {
        return 0.0;
	}   
}

void displayAllEmployees(const vecInt& ids, const vecStr
     & names, const vecStr& depts, const vecDbl& hours,
     const vecDbl& rates) {

	cout.imbue(locale("C"));

    cout << "Employee Payroll Information:" << endl;
	cout << "________________________________________________"
         << "________________________________________________" << endl;


    cout << left
        << setw(8) << "ID"
        << setw(14) << "Last Name"
        << setw(16) << "Department"
        << setw(10) << "Reg Hrs"
        << setw(12) << "Worked Hrs"
        << setw(8) << "OT"
        << setw(17) << "Hourly Rate"
        << setw(19) << "Gross Pay"
        << "\n-------------------------------------------------"
		<< "-----------------------------------------------"
        << endl;
       
    for (size_t i = 0; i < ids.size(); ++i) {

        double grossPay = calculateGrossPay(hours[i], rates[i]);
        double OT = calculateOvertimeHours(hours[i]);
		double regularHours = hours[i] - OT;

        cout << left
            << setw(8) << ids[i]
            << setw(16) << names[i]
            << setw(8) << depts[i]
            << right << fixed << setprecision(1)
            << setw(10) << regularHours
            << setw(12) << hours[i]
            << setw(8) << OT;

			cout.imbue(locale(""));

            cout << right << fixed << setprecision(2)
                 << "        $" << rates[i]   
                 << "        $" << setw(10) << put_money(grossPay * 100); 

			cout.imbue(locale("C"));

            cout << endl;
    }

    cout << "___________________________________________________________"
         << "_____________________________________" << endl;
}

void sortByName(vecInt& ids, vecStr& names, vecStr& depts, vecDbl& hours, vecDbl& rates) {
    
    for(size_t i = 0; i < names.size() - 1; ++i) {
        for(size_t j = 0; j < names.size() - i - 1; ++j) {

            if (names[j] > names[j + 1]) {
                swap(names[j], names[j + 1]);
                swap(ids[j], ids[j + 1]);
                swap(depts[j], depts[j + 1]);
                swap(hours[j], hours[j + 1]);
                swap(rates[j], rates[j + 1]);
            }
        }
	}
}

void sortByGrossPay(vecInt& ids, vecStr& names, vecStr& depts, vecDbl& hours, vecDbl& rates) {

    for(size_t i = 0; i < hours.size() - 1; ++i) {
        for(size_t j = 0; j < hours.size() - i - 1; ++j) {
            double grossPayJ = calculateGrossPay(hours[j], rates[j]);
            double grossPayJPlus1 = calculateGrossPay(hours[j + 1], rates[j + 1]);
            if (grossPayJ < grossPayJPlus1) {
                swap(names[j], names[j + 1]);
                swap(ids[j], ids[j + 1]);
                swap(depts[j], depts[j + 1]);
                swap(hours[j], hours[j + 1]);
                swap(rates[j], rates[j + 1]);
            }
        }
	}
}

void sortByDepartment(vecInt& ids, vecStr& names, vecStr& depts, vecDbl& hours, vecDbl& rates) {
        
    for(size_t i = 0; i < depts.size() - 1; ++i) {
        for(size_t j = 0; j < depts.size() - i - 1; ++j) {
            if (depts[j] > depts[j + 1]) {
                swap(names[j], names[j + 1]);
                swap(ids[j], ids[j + 1]);
                swap(depts[j], depts[j + 1]);
                swap(hours[j], hours[j + 1]);
                swap(rates[j], rates[j + 1]);
            }
        }
	}
}

double calculateDepartmentPayroll(const vecStr& depts, const vecDbl& hours, const vecDbl& rates,
    const string& targetDept) {

	double totalPayroll = 0.0;
    for (size_t i = 0; i < depts.size(); ++i) {
        if (depts[i] == targetDept) {
            totalPayroll += calculateGrossPay(hours[i], rates[i]);
        }
    }
	return totalPayroll;
}

int countEmployeesWithOvertime(const vecDbl& hours) {
        int count = 0;
    for (size_t i = 0; i < hours.size(); ++i) {
        if (hours[i] > 40.0) {
            ++count;
        }
    }
	return count;
}

void displayPayrollSummary(const vecInt& ids, const vecStr& names, const vecStr& depts,
    const vecDbl& hours, const vecDbl& rates) {



    std::cout << "PAYROLL SUMMARY REPORT" << endl;
    cout << "==================================================================" << endl << endl;
    cout << "EMPLOYEE STATISTICS" << endl;
    cout << "____________________________________________" << endl;

    cout << "Total Employees: " << ids.size() << endl;
    cout << "Employees with Overtime: " << countEmployeesWithOvertime(hours) << endl;
    cout << "Employees without OT: " << ids.size() - countEmployeesWithOvertime(hours) << endl 
         << endl;

    cout << "HOURS SUMMARY: " << endl;
    cout << "____________________________________________" << endl;

    double sumregularHours = 0.0;

    for (size_t i = 0; i < hours.size(); ++i) {
        double OT = calculateOvertimeHours(hours[i]);
        double regularHours = hours[i] - OT;
        sumregularHours += regularHours;
    }
    cout << "Total Regular Hours: " << fixed << setprecision(1) << sumregularHours << endl;

    double sumOT{};
    for (size_t i = 0; i < hours.size(); ++i) {
        double OT = calculateOvertimeHours(hours[i]);
        if (OT > 0.0) {
            sumOT += OT;
        }
    }
    cout << "Total Overtime Hours: " << fixed << setprecision(1) << sumOT << endl;

    double sumHours = 0.0;
    for (size_t i = 0; i < hours.size(); ++i) {
        sumHours += hours[i];
    }
    double avgHours = sumHours / ids.size();

    cout << "Total Hours Worked: " << fixed << setprecision(1) << sumHours << endl;
    cout << "Average Hours/Employee: " << fixed << setprecision(1) << avgHours << endl << endl;

    cout << "PAY SUMMARY" << endl;
    cout << "____________________________________________" << endl;

    double regPay;
    double OTPay;
    double totalRegPay = 0.0;
    double totalOTPay = 0.0;
    for (size_t i = 0; i < hours.size(); ++i) {
        OTPay = 0.0;

        if (hours[i] > 40.0) {
            regPay = 40.0 * rates[i];
            OTPay = (hours[i] - 40.0) * rates[i] * 1.5;
        }
        else
            regPay = hours[i] * rates[i];

        totalRegPay += regPay;
        totalOTPay += OTPay;
    }
    cout.imbue(std::locale(""));
    cout << "Total Regular Pay: " << fixed << setprecision(2) << "$" << put_money(totalRegPay * 100)
        << endl;
    cout << "Total Overtime Pay: " << fixed << setprecision(2) << "$" << put_money(totalOTPay * 100)
        << endl;

    double totalGrossPayroll = 0.0;
    for (size_t i = 0; i < hours.size(); ++i) {
        totalGrossPayroll += calculateGrossPay(hours[i], rates[i]);
    }
    cout << "Total Gross Payroll: " << fixed << setprecision(2) << "$" << totalGrossPayroll
        << endl << endl;

    double highestGrossPay = 0.0;
    size_t high = 0;
    for (size_t i = 0; i < hours.size(); ++i) {
        double grossPay2 = calculateGrossPay(hours[i], rates[i]);
        if (grossPay2 > highestGrossPay) {
            highestGrossPay = grossPay2;
            high = i;
        }
    }

    double lowestGrossPay = calculateGrossPay(hours[0], rates[0]);
    size_t low = 0;
    for (size_t i = 0; i < hours.size(); ++i) {
        double grossPay3 = calculateGrossPay(hours[i], rates[i]);
        if (grossPay3 < lowestGrossPay) {
            lowestGrossPay = grossPay3;
            low = i;
        }
    }


    cout << "Highest Paid: " << names[high] << fixed << setprecision(2) << setw(5) << "$"
        << put_money(highestGrossPay * 100)
        << endl;
    cout << "Lowest Paid: " << names[low] << fixed << setprecision(2) << setw(5) << "$"
        << put_money(lowestGrossPay * 100)
        << endl;

    cout << "Average Pay: " << fixed << setprecision(2) << "$" << totalGrossPayroll / hours.size()
        << endl << endl;

    cout << "DEPARTMENT BREAKDOWN" << endl;
    cout << "____________________________________________" << endl;

    // Build a list of unique departments
    vecStr uniqueDepts;
    for (const auto& d : depts) {
        if (find(uniqueDepts.begin(), uniqueDepts.end(), d) == uniqueDepts.end()) {
            uniqueDepts.push_back(d);
        }
    }

    // Loop through each department and calculate stats
    for (const auto& dept : uniqueDepts) {
        double deptPayroll = calculateDepartmentPayroll(depts, hours, rates, dept);

        int deptEmpCount = 0;
        for (const auto& d : depts) if (d == dept) deptEmpCount++;

        double percentOfTotal = (deptPayroll / totalGrossPayroll) * 100;

        cout << left << setw(10) << dept
            << ": " << deptEmpCount << " employees "
            << "$" << fixed << setprecision(2) << deptPayroll
            << " (" << fixed << setprecision(1) << percentOfTotal << "%)" << endl;
    }
}

void addEmployee(vecInt& ids, vecStr& names, vecStr& depts,
    vecDbl& hours, vecDbl& rates) {

    int id;
    string name, dept;
    double empHours, empRate;

    cout << "Enter Employee ID: ";
    cin >> id;
    cout << "Enter Last Name: ";
    cin >> name;
    cout << "Enter Department: ";
    cin >> dept;
    cout << "Enter Hours Worked: ";
    cin >> empHours;
    cout << "Enter Hourly Rate: ";
    cin >> empRate;

    ids.push_back(id);
    names.push_back(name);
    depts.push_back(dept);
    hours.push_back(empHours);
    rates.push_back(empRate);

    cout << "Employee added successfully!\n";
}

void removeEmployeeByID(vecInt& ids, vecStr& names, vecStr& depts,
    vecDbl& hours, vecDbl& rates) {

    int targetID;
    cout << "Enter Employee ID to remove: ";
    cin >> targetID;

    bool found = false;

    for (size_t i = 0; i < ids.size(); ++i) {
        if (ids[i] == targetID) {
            ids.erase(ids.begin() + i);
            names.erase(names.begin() + i);
            depts.erase(depts.begin() + i);
            hours.erase(hours.begin() + i);
            rates.erase(rates.begin() + i);

            cout << "Employee removed successfully!\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Employee ID not found.\n";
    }
}