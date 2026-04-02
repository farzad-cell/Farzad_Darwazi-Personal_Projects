/* MovieAnalyzer.cpp
 * This program analyzes a list of movies by storing their titles
 * and performing operations such as displaying, searching, or
 * processing movie data.
 *
 * By Farzad Darwazi
 * 03/20/2026
 */

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <iomanip>

const int NUM_MOVIES = 10;

using namespace std;

// Type aliases
using TitleArray = array<string, NUM_MOVIES>;
using YearArray = array<int, NUM_MOVIES>;
using RatingArray = array<double, NUM_MOVIES>;

// prototypes
bool readMovieData(TitleArray& Titles, YearArray& Years, RatingArray& Ratings,
	string filename);
string formatTitle(string title);
void displayMovies(const TitleArray& titles, const YearArray& years,
	const RatingArray& ratings, string header);
void sortByRatingDescending(TitleArray& titles, YearArray& years,
	RatingArray& ratings);
void sortByYearAscending(TitleArray& titles, YearArray& years,
	RatingArray& ratings);
void sortByTitleAscending(TitleArray& titles, YearArray& years,
	RatingArray& ratings);
double calculateAverageRating(const RatingArray& ratings);
int countMoviesAboveRating(const RatingArray& ratings, double
	threshold);

int main() {
	TitleArray titles;
	YearArray years;
	RatingArray ratings;

	
	displayMovies(titles, years, ratings, "Original Movie List:");
	
	sortByRatingDescending(titles, years, ratings);
	displayMovies(titles, years, ratings, "Movies Sorted by Rating (Descending):");
	
	sortByYearAscending(titles, years, ratings);
	displayMovies(titles, years, ratings, "Movies Sorted by Year (Ascending):");
	
	sortByTitleAscending(titles, years, ratings);
	displayMovies(titles, years, ratings, "Movies Sorted by Title (Ascending):");
	double averageRating = calculateAverageRating(ratings);
	cout << fixed << setprecision(2);
	cout << "Average Rating: " << averageRating << endl;
	double threshold = 8.0;
	int countAboveThreshold = countMoviesAboveRating(ratings, threshold);
	cout << "Number of movies with rating above " << threshold << ": "
		<< countAboveThreshold << endl;
	return 0;
}

bool readMovieData(TitleArray& Titles, YearArray& Years, RatingArray& Ratings,
	string filename) {

	ifstream inFile(filename);

	for (int i{}; i < NUM_MOVIES; ++i) {
		inFile >> Titles[i] >> Years[i] >> Ratings[i];
	}

	if (!inFile) {
		return false;
	}
	return true;
}

string formatTitle(string title){
	for (int i{}; i < title.length(); ++i) {
		if (title[i] == '_') {
			title[i] = ' ';
		}
	}
	return title;
}

void displayMovies(const TitleArray &titles, const YearArray &years,
	const RatingArray &ratings, string header) {
	
	for (int i{}; i < NUM_MOVIES; ++i) {
		string format = formatTitle(titles[i]);
		cout << setw(30) << left << format << " | " << years[i] << " | " << ratings[i] << endl;

	}
}

void sortByRatingDescending(TitleArray& titles, YearArray& years,
	RatingArray& ratings) {
	
	for (int i{}; i < NUM_MOVIES - 1; ++i) {
		for (int j{}; j < NUM_MOVIES - i - 1; ++j) {

			if (ratings[j] < ratings[j + 1]) {
				double tempR = ratings[j];
				ratings[j] = ratings[j + 1];
				ratings[j + 1] = tempR;

				int tempY = years[j];
				years[j] = years[j + 1];
				years[j + 1] = tempY;


				string tempT = titles[j];
				titles[j] = titles[j + 1];
				titles[j + 1] = tempT;
			}		
		}
	}		
}

void sortByYearAscending(TitleArray& titles, YearArray& years,
	RatingArray& ratings) {
	
	for (int i{}; i < NUM_MOVIES - 1; ++i) {
		for (int j{}; j < NUM_MOVIES - i - 1; ++j) {

			if (years[j] > years[j + 1]) {
				int tempY = years[j];
				years[j] = years[j + 1];
				years[j + 1] = tempY;
				
				double tempR = ratings[j];
				ratings[j] = ratings[j + 1];
				ratings[j + 1] = tempR;

				string tempT = titles[j];
				titles[j] = titles[j + 1];
				titles[j + 1] = tempT;
			}
		}
	}
}

void sortByTitleAscending(TitleArray& titles, YearArray& years,
	RatingArray& ratings) {

	for (int i{}; i < NUM_MOVIES - 1; ++i) {
		for (int j{}; j < NUM_MOVIES - i - 1; ++j) {

			if (titles[j] > titles[j + 1]) {
				string tempT = titles[j];
				titles[j] = titles[j + 1];
				titles[j + 1] = tempT;

				int tempY = years[j];
				years[j] = years[j + 1];
				years[j + 1] = tempY;
				
				double tempR = ratings[j];
				ratings[j] = ratings[j + 1];
				ratings[j + 1] = tempR;
			}
		}
	}
}

double calculateAverageRating(const RatingArray& ratings) {
		double sum = 0.0;

	for (int i{}; i < NUM_MOVIES; ++i) {
		sum += ratings[i];
	}
	return sum / NUM_MOVIES;
}

int countMoviesAboveRating(const RatingArray& ratings, double
	threshold) {
	int count = 0;
	for (int i{}; i < NUM_MOVIES; ++i) {
		if (ratings[i] >= threshold) {
			++count;
		}
	}
	return count;
}


