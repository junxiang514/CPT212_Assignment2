#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
#define CHAR_RANGE 256 // Define the range of possible characters (ASCII)

// Function to create the bad character table for the Boyer-Moore algorithm
void createBadCharTable(const string &pattern, int badCharTable[CHAR_RANGE]) {
    int patternSize = pattern.size(); //calclate the size of the boolean

    //initialize the value in the array to -1
    for (int i = 0; i < CHAR_RANGE; ++i) {
        badCharTable[i] = -1; 
    }

    // Fill the table with the last position of each char in the pattern
    for (int i = 0; i < patternSize; ++i) {
        badCharTable[(int)pattern[i]] = i;
    }
}

// Function to perform the Boyer-Moore string search using the bad character heuristic
void boyerMooreSearch(const string &text, const string &pattern) {
    int textSize = text.size();     // Length of the text
    int patternSize = pattern.size(); // Length of the pattern
    int badCharTable[CHAR_RANGE];   // Bad character table

    // Preprocess the pattern to fill in the bad char to the table
    createBadCharTable(pattern, badCharTable);

    int shift = 0; // Initialize the value of the shift
    bool found = false; // Flag to check if pattern is found

    while (shift <= (textSize - patternSize)) {
        int j = patternSize - 1; // Assign the pattern size -1 to the object j.

        // If the pattern and character was match, decrease index j 
        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }

        // Condition when the text was found in the current shift
        if (j < 0) {
            cout << "Pattern found at index " << shift << endl; // show the index where the pattern was found
            found = true; // update the found boolean

            // Align the string such that the next character in the text matches the last occurrence of the same character in the pattern.
            shift += (shift + patternSize < textSize) ? patternSize - badCharTable[text[shift + patternSize]] : 1;
        } else {
            // Align the string such that the next character in the text matches the last occurrence of the same character in the pattern.
            shift += max(1, j - badCharTable[text[shift + j]]);
        }
    }

    // If pattern was not found in the text prompt the information
    if (!found) {
        cout << "The pattern was not found" << endl;
    }
}

int main() {
    string text;    // Input text
    string pattern; // Input pattern

    // Ask the user enter the text for checking
    cout << "Enter the text: ";
    getline(cin, text);

    // Ask the user enter the pattern for searching
    cout << "Enter the pattern: ";
    getline(cin, pattern);
    
    // Perform the Boyer-Moore search
    boyerMooreSearch(text, pattern);
    return 0;
}

