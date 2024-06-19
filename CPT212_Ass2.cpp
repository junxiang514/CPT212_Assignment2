#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#define CHAR_RANGE 256 // Define the range of possible characters (ASCII)

// Function to create the bad character table for the Boyer-Moore algorithm
void createBadCharTable(const string &pattern, int badCharTable[CHAR_RANGE]) {
    int patternSize = pattern.size(); //calclate the size of the boolean

    // Initialize all characters' occurrences to -1
    for (int i = 0; i < CHAR_RANGE; ++i) {
        badCharTable[i] = -1; //initialize the value to -1
    }

    // Fill the table with the last occurrence of each character in the pattern
    for (int i = 0; i < patternSize; ++i) {
        badCharTable[(int)pattern[i]] = i;
    }
}

// Function to perform the Boyer-Moore string search using the bad character heuristic
void boyerMooreSearch(const string &text, const string &pattern) {
    int textSize = text.size();     // Length of the text
    int patternSize = pattern.size(); // Length of the pattern
    int badCharTable[CHAR_RANGE];   // Bad character table

    // Preprocess the pattern to fill the bad character table
    createBadCharTable(pattern, badCharTable);

    int shift = 0; // Shift of the pattern with respect to the text
    bool found = false; // Flag to check if pattern is found

    while (shift <= (textSize - patternSize)) {
        int j = patternSize - 1; // Index of the last character of the pattern

        // Decrease index j while characters of pattern and text are matching
        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }

        // If the pattern is found at the current shift
        if (j < 0) {
            cout << "Pattern found at index " << shift << endl; // show the index where the pattern was found
            found = true; // update the found boolean

            // Shift the pattern so that the next character in text aligns with the last occurrence of it in the pattern
            shift += (shift + patternSize < textSize) ? patternSize - badCharTable[text[shift + patternSize]] : 1;
        } else {
            // Shift the pattern so that the bad character in text aligns with the last occurrence of it in the pattern
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

    // Prompt the user to enter the text
    cout << "Enter the text: ";
    getline(cin, text);

    // Prompt the user to enter the pattern
    cout << "Enter the pattern: ";
    getline(cin, pattern);
    
    // Perform the Boyer-Moore search
    boyerMooreSearch(text, pattern);
    return 0;
}

