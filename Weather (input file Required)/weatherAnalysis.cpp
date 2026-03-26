// This program reads weather data for seven days from a
// file and stores it using arrays. It then calculates
// statistics and displays a weekly weather report.

// Farzad Darwazi
#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <iomanip>

using namespace std;

const int DAYS_IN_WEEK = 7;

using StringArray = array<string, DAYS_IN_WEEK>;
using DoubleArray = array<double, DAYS_IN_WEEK>;

// Prototypes
bool readWeatherData(StringArray &days, DoubleArray &highs, DoubleArray &lows, DoubleArray &precip, string filename);
double calculateAverage(const DoubleArray &values);
double findMaximum(const DoubleArray &values);
double findMinimum(const DoubleArray &values);
double calculateTotal(const DoubleArray &precip);
string classifyWeek(double avgHigh, double totalPrecip);
void displayDailyReport(const StringArray &days, const DoubleArray &highs, const DoubleArray &lows,
                        const DoubleArray &precip);

int main()
{
	StringArray dayNames{};
	DoubleArray highTemps{};
	DoubleArray lowTemps{};
	DoubleArray precipitation{};

	int dryDays{};

	cout << "===================================================" << endl;
	cout << setw(30) <<"WEEKLY WEATHER REPORT" << endl;
	cout << "===================================================" << endl;

	bool found = readWeatherData(dayNames, highTemps, lowTemps, precipitation, "weather.txt");


	if(!found) {
		cout << "Unable to open weather.txt" << endl;
		return 0;
	}

	double avgHigh = calculateAverage(highTemps);
	double aveLow = calculateAverage(lowTemps);

	double hottest = findMaximum(highTemps);
	double rainiest = findMaximum(precipitation);
	double coldest = findMinimum(lowTemps);

	double totalRainfall = calculateTotal(precipitation);

	for(int i{}; i < DAYS_IN_WEEK; ++i) {

		if(precipitation[i] == 0.0)
			dryDays++;
	}

	string classification = classifyWeek(avgHigh, totalRainfall);;

	displayDailyReport(dayNames, highTemps, lowTemps, precipitation);

	cout << "_______________________________________________________________" << endl;
	cout << "WEEKLY STATISTICS" << endl;

	cout << "\nTemperature Analysis:\n";

	int hottestIndex = 0;
int coldestIndex = 0;
int rainiestIndex = 0;

for(int i{1}; i < DAYS_IN_WEEK; ++i)
{
    if(highTemps[i] > highTemps[hottestIndex])
        hottestIndex = i;

    if(lowTemps[i] < lowTemps[coldestIndex])
        coldestIndex = i;

    if(precipitation[i] > precipitation[rainiestIndex])
        rainiestIndex = i;
}

cout << "\nTemperature Analysis:\n";

cout << "Average High: " << avgHigh << "\u00B0F\n";
cout << "Average Low: " << aveLow << "\u00B0F\n";

cout << "Hottest Day: " << highTemps[hottestIndex]
     << "\u00B0F (" << dayNames[hottestIndex] << ")\n";

cout << "Coldest Night: " << lowTemps[coldestIndex]
     << "\u00B0F (" << dayNames[coldestIndex] << ")\n";

cout << "\nPrecipitation Analysis:\n";

cout << "Total Rainfall: " << totalRainfall << " inches\n";

cout << "Rainiest Day: " << precipitation[rainiestIndex]
     << "\" (" << dayNames[rainiestIndex] << ")\n";

cout << "Dry Days: " << dryDays << " out of 7\n";

cout << "\nWeekly Classification: " << classification << endl;

}

bool readWeatherData(StringArray &days, DoubleArray &highs, DoubleArray &lows, DoubleArray &precip, string filename) {
	ifstream inFile(filename);

	cout << "Reading weather data from weather.txt..." << endl;

	if(!inFile)
		return false;


	for(int i{}; i < DAYS_IN_WEEK; ++i) {
		inFile >> days[i] >> highs[i] >> lows[i] >> precip[i];
	}
	cout << "Successfully loaded " << DAYS_IN_WEEK << " days of weather data." << endl << endl;
	return true;
}

double calculateAverage(const DoubleArray &values) {
	double sum{};

	for(int i{}; i < DAYS_IN_WEEK; ++i) {
		sum += values[i];
	}
	return sum / DAYS_IN_WEEK;

}

double findMaximum(const DoubleArray &values) {
	double max = values[0];

	for(int i{1}; i < DAYS_IN_WEEK; ++i) {

		if(values[i] > max)
			max = values[i];
	}
	return max;

}

double findMinimum(const DoubleArray &values) {
	double min = values[0];

	for(int i{1}; i < DAYS_IN_WEEK; ++i) {

		if(values[i] < min)
			min = values[i];
	}
	return min;
}

double calculateTotal(const DoubleArray &precip) {
	double precipSum{};

	for(int i{}; i < DAYS_IN_WEEK; ++i) {
		precipSum += precip[i];
	}
	return precipSum;
}

string classifyWeek(double avgHigh, double totalPrecip) {

	if(avgHigh >= 80 and totalPrecip < 0.1) {
		return "Hot and Dry";
	} else if(avgHigh >= 80 and totalPrecip >= 0.1) {
		return "Hot and Wet";
	} else if(avgHigh >= 65 and totalPrecip < 0.1) {
		return "Mild and Dry";
	} else if(avgHigh >= 65 and totalPrecip >= 0.1) {
		return "Mild and Wet";
	} else if(avgHigh < 65 and totalPrecip < 0.1) {
		return "Cool and Dry";
	} else
		return "Cool and Wet";
}

void displayDailyReport(const StringArray &days, const DoubleArray &highs, const DoubleArray &lows,
                        const DoubleArray &precip) {
	cout << "_____________________________________________________________\n" << endl;
	cout << setw(25) << "DAILY WEATHER SUMMARY" << endl;
	cout << "_____________________________________________________________\n" << endl;
	cout << "   Day          High(F)    Low(F)    Precip    Temp Range" << endl;
	cout << "______________________________________________________________\n" << endl;

	for(int i{}; i < DAYS_IN_WEEK; ++i) {
		double range = highs[i] - lows[i];

		cout << fixed << setprecision(2)
		     << setw(10) << days[i]
		     << setw(12) << highs[i]
		     << setw(10) << lows[i]
		     << setw(10) << precip[i] << "\""
		     << setw(10) << range << "B0"
		     << endl;
	}

}



