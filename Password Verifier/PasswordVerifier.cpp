/*
 * =============================================================================
 * Project: Password Verifier System
 * Author:  Farzad Darwazi
 * Date:    April 2026
 * -----------------------------------------------------------------------------
 * DESCRIPTION:
 * This program performs a deep security audit on user-provided passwords.
 * It utilizes Wide Characters (Unicode) to display a visual status dashboard
 * for five key criteria: length, uppercase, lowercase, digits, and symbols.
 *
 * FEATURES:
 * 1. Unicode Emoji Support: Uses UTF-16 for ?/? visual feedback.
 * 2. Input Hardening: Protects against EOF (Ctrl+Z) infinite loops.
 * 3. Logic: Manual range-checking (ASCII) for high-performance validation.
 *
 * USAGE:
 * - Enter a password to see the status dashboard.
 * - Type '0' to exit the application safely.
 * =============================================================================
 */

// Include necessary headers for I/O, string manipulation, and Windows API
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <fcntl.h> 
#include <io.h>
#include <string>

// Prototypes
bool verifyPassword(std::wstring password);

int main()
{   
    // Set console output to UTF-8 and switch to wide character mode
    SetConsoleOutputCP(CP_UTF8);
    (void)_setmode(_fileno(stdout), _O_U16TEXT);
    (void)_setmode(_fileno(stdin), _O_U16TEXT);
	
    // Main loop to continuously prompt for password input
    while (true) {

        std::wstring password;
        bool found = false;

		// Prompt the user to enter a password
        std::wcout << L"Enter your password: ";
        
		// Check for input failure
        if(!(std::wcin >> password)) {
            std::wcout << L"Invalid input. Please enter a valid password.\n";
			break; 
		}

		// Exit condition
        if (password == L"0") {
            std::wcout << L"Good Bye!\n";
            break;
        }

		// Verify the password and display the result
        found = verifyPassword(password);

		// Display the verification result
        if (found == true) {
            std::wcout << L"\n\tSuccessfully VERIFIED Password\u2705\n\n";
        }
        else
            std::wcout << L"\n\tInvalid. Try again follow the criteria \u274c \n\n";
    }
    return 0;
}
/*
 * =============================================================================
 * Function: verifyPassword
 * -----------------------------------------------------------------------------
 * PRE-CONDITION:
 * 1. The input 'password' is a valid std::wstring.
 * 2. The console is set to _O_U16TEXT mode to support Unicode L"\u2705" and L"\u274c".
 * 3. Status variables (size, upper, lower, digit, special) are initialized to L"\u274c".
 *
 * POST-CONDITION:
 * 1. Returns true if (length >= 8) AND (upper >= 1) AND (lower >= 1)
 * AND (digit >= 1) AND (special >= 1).
 * 2. Returns false if any single criterion remains L"\u274c".
 * 3. A formatted criteria table is printed to the standard wide output (wcout).
 * =============================================================================
 */

bool verifyPassword(std::wstring password) {
	// Initialize all criteria to red cross mark
    std::wstring size = L"\u274c"; std::wstring upper = L"\u274c";
    std::wstring lower = L"\u274c"; std::wstring digit = L"\u274c"; std::wstring special = L"\u274c";

	// Check for password length
    if (password.size() >= 8) {
        size = L"\u2705";
    }

	// Check for uppercase, lowercase, and digit characters
    for (int i = 0; i < password.size(); i++) {
        
        if (password[i] >= L'A' && password[i] <= L'Z') {
            upper = L"\u2705";
            
        }
        if (password[i] >= L'a' && password[i] <= L'z') {
            lower = L"\u2705";
		}
        if(password[i] >= L'0' && password[i] <= L'9')
			digit = L"\u2705";
    }

    // Finding special characters
    for (int i = 0; i < password.size(); i++) {
        if ((password[i] >= L'A' && password[i] <= L'Z') ||
            (password[i] >= L'a' && password[i] <= L'z') ||
            (password[i] >= L'0' && password[i] <= L'9')) {
        }
        else
            special = L"\u2705";
    }

	// Display the criteria and their status
	std::wcout << L"Required Password Criteria:\n" 
        <<L"=============================================\n";
    std::wcout << std::left << std::setw(25) << L"At least 8 characters: " << std::setw(5)
        << size << L"\n";     
    std::wcout << std::left << std::setw(25) << L"At least 1 uppercase: " << std::setw(5)
        << upper << L"\n";
    std::wcout << std::left << std::setw(25) << L"At least 1 lowercase: " << std::setw(5)
        << lower << L"\n";
    std::wcout << std::left << std::setw(25) << L"At least 1 digit: " << std::setw(5)
        << digit << L"\n";
    std::wcout << std::left << std::setw(25) << L"At least 1 special: " << std::setw(5)
        << special << L"\n";
	std::wcout << L"=============================================\n Exit button is 0\n";

    if (size == L"\u2705" && upper == L"\u2705" && lower == L"\u2705" 
                          && digit == L"\u2705" && special == L"\u2705") {
        return true;
    }
    else
		return false;
}


