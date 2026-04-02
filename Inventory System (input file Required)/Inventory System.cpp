//InventorySystem.cpp
/*
 * This program demonstrates C-style arrays, pointers, pointer arithmetic,
 * and output parameters. Reads inventory data from a file and provides
 * various operations including sorting and searching.
 */
 // Farzad Darwazi

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <string>
#include <locale>
#include <algorithm>

// Constants
const int MAX_PRODUCTS = 20;
const int MAX_NAME_LENGTH = 50;

// Function prototypes
int loadInventory(int* ids, std::string names[], int* quantities, double
    * prices, const char* filename);
void displayInventory(const int* ids, const std::string names[], const int
    * quantities, const double* prices, int count);
double calculateTotalValue(const int* quantities, const double
    * prices, int count);
int findProductByID(const int* ids, int count, int searchID);
void updateQuantity(int* quantities, int index, int newQuantity);
int countLowStock(const int* quantities, int count, int threshold);
void findMinMax(const double* prices, int count, double* minPrice,
    double* maxPrice);
void sortByPrice(int* ids, std::string names[], int* quantities, double
    * prices, int count);
void insertProduct(int* ids, std::string names[], int* quantities, double
    * prices, int& count, int newID, const std::string& newName, int newQuantity, double newPrice);


int main()
{
	// Declare parallel arrays for inventory data
    int ids[MAX_PRODUCTS];
    std::string names[MAX_PRODUCTS];
    int quantities[MAX_PRODUCTS];
    double prices[MAX_PRODUCTS];
    
	// Variables for statistics
    double minValue = 0.0;
    double maxValue = 0.0;
	
    // Load inventory data from file
    int found = loadInventory(ids, names, quantities, prices, "inventory.txt");
	
    // Check if loading was successful
    if (found == -1) {
        std::cout << "Error loading 'inventory.txt'." << std::endl;
        return 1;
    }
    else
        std::cout << "Loaded " << found << " products from 'inventory.txt'.\n" << std::endl;
	// Sort inventory by price for better display
    while (true) {
		// Display menu options to the user
        std::cout << "Menu:\n"
            << "1. Display Inventory\n"
            << "2. Find Product by ID\n"
            << "3. Low Stock Item\n"
            << "4. Statistics\n"
			<< "5. Insert New Product\n"
            << "0. Exit\n";
        std::cout << "Enter your choice (0-5): ";

		// Get user input for menu choice
        int user_pick{};
        std::cin >> user_pick;
        std::cout << std::endl;

		// Handle user choice with input validation
        if (user_pick == 0) {
            std::cout << "Exiting program. Goodbye!" << std::endl;
            break;
        }
		// Validate user input for menu choice
        if (user_pick < 0 || user_pick > 5) {
            std::cout << "Invalid option. Please try again. (0-4)\n" << std::endl;
            continue;
        }
		// Execute selected menu option
        switch (user_pick) {

        case 1: {
              // Display the current inventory in a formatted table
              displayInventory(ids, names, quantities, prices, found);
              break;
        }
        case 2: {
            // Prompt user to enter a product ID and search for it in the inventory
            std::cout << "FIND PRODUCT BY ID\n"
                << "==============================================\n";

            // Get product ID from user input
            int searchID{};
            std::cout << "\nEnter product ID: ";
            std::cin >> searchID;
            std::cout << std::endl;
            int index = findProductByID(ids, found, searchID);

            // If product is found, display its details; otherwise, show not found message
            if (index != -1) {
                std::cout << "Product Found: \n"
                    << "  ID: " << *(ids + index) << std::endl
                    << "  Name: " << *(names + index) << std::endl
                    << "  Quantity: " << *(quantities + index) << std::endl;
                // Format price and stock value as US currency
                std::cout.imbue(std::locale("en_US.UTF-8"));
                // Display price and stock value with currency formatting
                std::cout << std::fixed << std::setprecision(2) << std::showbase;
                std::cout << "  Price: " << std::put_money(*(prices + index) * 100) << std::endl;
                double stockValue = *(quantities + index) * *(prices + index);
                std::cout << "  Stock Value: " << std::put_money(stockValue * 100)
                    << std::endl << std::noshowbase << std::endl;
                std::cout << "----------------------------------------------\n\n";
                std::cout.imbue(std::locale("C"));
                break;
            }
            else {
                std::cout << "Product with ID " << searchID << " not found.\n\n";
                break;
            }

        }
        
        case 3: {
			// Display products that are below a user-defined stock threshold
            std::cout << "Low Stock Items\n"
                << "==============================================\n";
            int threshold{};
            std::cout << "Enter low stock threshold: ";
            std::cin >> threshold;
            std::cout << std::endl << std::endl;
            std::cout << std::left << std::setw(10) << "ID"
                << std::setw(15) << "Products"
                << std::setw(10) << "QTY"
                << std::setw(20) << "Status"
                << std::endl << "----------------------------------------------\n";
            
			// Find the lowest stock quantity among products below the threshold to determine critical status
            int lowStockIndex = quantities[0];
            std::string lowStockStatus;
            for (int i{}; i < found; ++i) {
                if (*(quantities + i) < lowStockIndex) {
                    lowStockIndex = *(quantities + i);
                }
            }
			// Count how many products are below the threshold and display their details with status
            int lowStockCount = countLowStock(quantities, found, threshold);
            for (int i{}; i < found; ++i) {
                if (*(quantities + i) < threshold) {
                    if (*(quantities + i) == lowStockIndex) {
                        lowStockStatus = "Critical";
                    }
                    else
                        lowStockStatus = "Low Stock";
					
                    // Display product details with low stock status
                    std::cout << std::left << std::setw(10) << *(ids + i)
                        << std::setw(15) << *(names + i)
                        << std::setw(10) << *(quantities + i)
                        << std::setw(20) << lowStockStatus
                        << std::endl;
                }
            }
			// Display total count of products below the threshold
            std::cout << "----------------------------------------------\n";
            std::cout << "Number of products below threshold: " << lowStockCount << "\n\n";
            break;
        }
        case 4: {
            // Display various statistics about the inventory,
            // including total products, total units, total value, price range, and stock levels
            std::cout << "INVENTORY STATISTICS\n"
                << "==============================================\n\n";
            std::cout << std::left << std::setw(25) << "  Total Products: " << std::setw(20) << found << "\n";

            // Calculate total units in stock by summing quantities using pointer arithmetic
            int totalUnits = 0;
            for (int i{}; i < found; ++i) {
                totalUnits += *(quantities + i);
            }
            std::cout << std::left << std::setw(25) << "  Total Units in Stock: " << std::setw(20) << totalUnits << "\n  ";

            // Calculate and display total inventory value using the calculateTotalValue function
            calculateTotalValue(quantities, prices, found);

            std::cout << "\nPrice Range:\n";

            // Find minimum and maximum prices using the findMinMax function
            findMinMax(prices, found, &minValue, &maxValue);

            // Identify the products with the minimum and maximum prices and calculate average price
            std::string minName, maxName;
            double sumPrice{};
            for (int i{}; i < found; ++i) {
                if (minValue == *(prices + i)) {
                    minName = *(names + i);
                }
                if (maxValue == *(prices + i)) {
                    maxName = *(names + i);
                }
                sumPrice += *(prices + i);
            }
            // Calculate average price by dividing total price by number of products
            double avgPrice = sumPrice / found;

            std::cout.imbue(std::locale("en_US.UTF-8"));

            // Display minimum price, maximum price, and average price with currency formatting
            std::cout << std::fixed << std::setprecision(2)
                << "\n  Minimum Price: " << std::showbase << std::put_money(minValue * 100)
                << " (" << minName << ")\n"
                << "  Maximum Price: " << std::put_money(maxValue * 100)
                << " (" << maxName << ")\n"
                << "  Average Price: " << std::put_money(avgPrice * 100) << "\n\n";

            std::cout.imbue(std::locale("C"));
            std::cout << std::noshowbase;

            std::cout << "Stock Levels:\n\n";

            // Count how many products fall into each stock level category based on quantity thresholds
            int critP{};
            int lowP{};
            int normP{};
            int fullP{};
            for (int i{}; i < found; ++i) {

                if (*(quantities + i) < 20) {
                    critP++;
                }
                else if (*(quantities + i) >= 20 && (*(quantities + i) <= 49)) {
                    lowP++;
                }
                else if (*(quantities + i) >= 50 && (*(quantities + i) <= 99)) {
                    normP++;
                }
                else if (*(quantities + i) >= 100) {
                    fullP++;
                }
            }
            // Display count of products in each stock level category with formatted output
            std::cout << std::left // Set global alignment to left for text
                << std::setw(25) << "  Critical (<20): " << std::setw(2) << critP << "product(s)\n"
                << std::setw(25) << "  Low (20-49): " << std::setw(2) << lowP << "product(s)\n"
                << std::setw(25) << "  Normal (50-99): " << std::setw(2) << normP << "product(s)\n"
                << std::setw(25) << "  Full Stock (100+): " << std::setw(2) << fullP << "product(s)\n"
                << std::endl;
            std::cout << "----------------------------------------------\n\n";
            break;
        }  
        case 5: {
            std::cout << "INSERT NEW PRODUCT\n"
				<< "==============================================\n\n";
            int newID{};
            std::string newName;
            int newQuantity{};
            double newPrice{};
            std::cout << "Enter new product ID: ";
            std::cin >> newID;
            std::cout << "Enter new product name: ";
            std::cin >> newName;
            std::cout << "Enter new product quantity: ";
            std::cin >> newQuantity;
            std::cout << "Enter new product price: ";
            std::cin >> newPrice;

            // Insert a new product into the inventory by prompting the user for details and updating arrays
            int ogSize = found;
            insertProduct(ids, names, quantities, prices, found, newID, newName, newQuantity, newPrice);
            if(found > ogSize){
                std::cout << "New product added successfully.\n\n";
			}else
				std::cout << "Failed to add new product. Inventory may be full.\n\n";
            std::cout << "----------------------------------------------\n" << std::endl;
            break;
        }
    } 
    }
    return 0;
}
/**
 * loadInventory
 * ---------------------------------------
 * Reads product data from a file and stores it into arrays.
 *
 * Precondition:
 * - ids, quantities, and prices point to valid arrays
 * - names is a valid string array
 * - filename is a valid file name
 *
 * Postcondition:
 * - arrays are filled with inventory data from the file
 * - returns number of products loaded
 * - returns -1 if file cannot be opened
 *
 * Pointer Concept:
 * - Uses pointers to fill arrays
 * - Demonstrates passing arrays as pointers
 */
int loadInventory(int* ids, std::string names[], int* quantities, double
    * prices, const char* filename) {
    // Load inventory from file
	std::ifstream file(filename);
    
    if(!file)
		return -1; 

    int count;
    file >> count;

    for (int i{}; i < count; ++i) {
        file >> *(ids + i);
		file >> *(names + i);
        file >> *(quantities + i);
		file >> *(prices + i);
    }
	return count;
}
/**
 * displayInventory
 * ---------------------------------------
 * Displays all inventory items in a formatted table.
 *
 * Precondition:
 * - all array pointers are valid
 * - count > 0
 *
 * Postcondition:
 * - inventory is printed to the console
 * - no data is modified
 *
 * Pointer Concept:
 * - Uses pointer arithmetic to traverse arrays
 * - Uses const pointers to prevent modification
 */
void displayInventory(const int* ids, const std::string names[], const int
    * quantities, const double* prices, int count) {
    // Display header for inventory table
	std::cout << "CURRENT INVENTORY\n" 
		      << "=========================================================================="
              << std::endl;
    std:: cout << std::left << std::setw(10) << "ID" 
              << std::setw(20) << "Products" 
              << std::setw(10) << "QTY" 
		<< std::setw(15) << " Price" << std::setw(15) << "Value" << std::endl;
    std::cout << "--------------------------------------------------------------------------"
              << std::endl;
    // Display each product
    for (int i{}; i < count; ++i) {
        double value = *(quantities + i) * *(prices + i);   // Compute stock value using pointers
        std::cout << std::left << std::setw(10) << *(ids + i)   // ID using pointer
            << std::setw(13) << *(names + i)    // Name using pointer
            << std::right
            << std::setw(10) << *(quantities + i);      // Quantity using pointer
        // Format prices and values as US currency
        std::cout.imbue(std::locale("en_US.UTF-8"));
        std::cout << std::fixed << std::setprecision(2)
            << std::showbase << std::setw(13) << std::put_money(*(prices + i) * 100)
            << std::fixed << std::setprecision(2) 
			<< std::setw(15) << std::put_money(value * 100)
            << std::endl;
		std::cout.imbue(std::locale("C"));
        std::cout << std::noshowbase;
	}
    // Display footer and total inventory value

    std::cout << "=========================================================================="
		<< std::endl;
	calculateTotalValue(quantities, prices, count);
	std::cout << std::endl;
}   
/**
 * calculateTotalValue
 * ---------------------------------------
 * Calculates total inventory value by summing
 * (quantity × price) for all products.
 *
 * Precondition:
 * - quantities and prices point to valid arrays
 * - count > 0
 *
 * Postcondition:
 * - returns total inventory value
 *
 * Pointer Concept:
 * - Uses pointer arithmetic in a loop:
 *   *(quantities + i) and *(prices + i)
 */
double calculateTotalValue(const int* quantities, const double
    * prices, int count) {

    double totalValue{};
    for (int i{}; i < count; ++i) {
        // Multiply quantity and price using pointer arithmetic and add to total
        totalValue += *(quantities + i) * *(prices + i);
    }
    std::cout.imbue(std::locale("en_US.UTF-8"));
    std::cout << std::right
        << std::fixed << std::setprecision(2)
        << "Total Inventory Value: "
        << std::showbase << std::put_money(totalValue * 100)
		<< std::noshowbase
        << std::endl;
    std::cout.imbue(std::locale("C"));  // Reset locale

    return totalValue;
}
/**
 * findProductByID
 * ---------------------------------------
 * Searches for a product using its ID.
 *
 * Precondition:
 * - ids points to a valid array
 * - count > 0
 *
 * Postcondition:
 * - returns index of product if found
 * - returns -1 if not found
 *
 * Pointer Concept:
 * - Uses pointer arithmetic to traverse array
 * - Accesses elements using *(ids + i)
 */
int findProductByID(const int* ids, int count, int searchID) {

    for (int i{}; i < count; ++i) {
        // Traverse array using pointer arithmetic and compare IDs

        if (*(ids + i) == searchID) {
            return i; // Return index of found product
        }
    }
	return -1; // Not found
}
/**
 * updateQuantity
 * ---------------------------------------
 * Updates the quantity of a product.
 *
 * Precondition:
 * - quantities points to a valid array
 * - index is within valid range (0 <= index < size)
 *
 * Postcondition:
 * - quantity at given index is updated to newQuantity
 *
 * Pointer Concept:
 * - Uses pointer dereferencing:
 *   *(quantities + index) = newQuantity
 */
void updateQuantity(int* quantities, int index, int newQuantity) {
    // Update the quantity at the given index using pointer dereferencing
        *(quantities + index) = newQuantity;
}
/**
 * countLowStock
 * ---------------------------------------
 * Counts how many products have quantity below a threshold.
 *
 * Precondition:
 * - quantities points to a valid array
 * - count > 0
 * - threshold is a valid integer
 *
 * Postcondition:
 * - returns number of products below threshold
 *
 * Pointer Concept:
 * - Uses pointer arithmetic to traverse array
 * - Accesses elements using *(quantities + i)
 */
int countLowStock(const int* quantities, int count, int threshold) {

	int num{};  // Counter for products below threshold
    for (int i{}; i < count; ++i) {
        // Check each quantity using pointer arithmetic
        if (*(quantities + i) < threshold) {
            num++;  // Increment counter if quantity is below threshold
            
        }
    }
    return num;
}
/**
 * findMinMax
 * ---------------------------------------
 * Finds the minimum and maximum prices in the inventory.
 *
 * Precondition:
 * - prices points to a valid array
 * - minPrice and maxPrice are valid pointers
 * - count > 0
 *
 * Postcondition:
 * - *minPrice contains the lowest price
 * - *maxPrice contains the highest price
 *
 * Pointer Concept:
 * - Uses output parameters (pointers)
 * - Uses pointer arithmetic to traverse array
 */
void findMinMax(const double* prices, int count, double* minPrice,
    double* maxPrice) {
    // Initialize min and max using pointer dereferencing

	double min = *(prices + 0), max = *(prices + 0);
    for (int i{1}; i < count; ++i) {
        // Traverse array using pointer arithmetic
        if(*(prices + i) < min)
			min = *(prices + i);    // Update min if current price is lower
		if (*(prices + i) > max)
			max = *(prices + i);    // Update max if current price is higher
    }
    // Output results using pointers (output parameters)
    *minPrice = min;
	*maxPrice = max;
}
/**
 * sortByPrice
 * ---------------------------------------
 * Sorts all inventory arrays by price (ascending order).
 *
 * Precondition:
 * - all arrays are valid and have the same size
 * - count > 0
 *
 * Postcondition:
 * - arrays are sorted by price (lowest to highest)
 * - all parallel arrays remain synchronized
 *
 * Pointer Concept:
 * - Uses pointer notation for swapping values
 * - Demonstrates working with parallel arrays
 */
void sortByPrice(int* ids, std::string names[], int* quantities, double
    * prices, int count) {

    for (int i{}; i < count; ++i) {
        for (int j{}; j < count - i - 1; ++j) {
            // Compare prices using pointer arithmetic and swap if needed
            if(*(prices + j + 1) < *(prices + j)) {
                // Swap prices and keep all parallel arrays in sync
                std::swap(*(prices + j), *(prices + j + 1));
                std::swap(*(ids + j), *(ids + j + 1));
                std::swap(*(names + j), *(names + j + 1));
                std::swap(*(quantities + j), *(quantities + j + 1));
			}
        }
    }
}
/**
 * insertProduct
 * ---------------------------------------
 * Adds a new product to the inventory arrays.
 *
 * Precondition:
 * - all arrays are valid and have enough space
 *
 * Postcondition:
 * - new product added at the end
 * - count is incremented
 *
 * Pointer Concept:
 * - Uses pointer notation to access and modify array elements
 */
void insertProduct(int* ids, std::string names[], int* quantities, double
	* prices, int& count, int newID, const std::string& newName, int newQuantity, double newPrice) {

    if (count >= MAX_PRODUCTS) {
        std::cout << "Inventory is full. Cannot add more products." << std::endl;
        return;
	}
   
    // Add new product to arrays using pointer notation
    *(ids + count) = newID;
    *(names + count) = newName;
    *(quantities + count) = newQuantity;
    *(prices + count) = newPrice;
	count++; // Increment count of products
}
