//#include <iostream>
//#include <string>
//#include <algorithm>
//using namespace std;
//#define CHAR_RANGE 256 // Define the range of possible characters (ASCII)
//
//// Function to create the bad character table for the Boyer-Moore algorithm
//void createBadCharTable(const string &pattern, int badCharTable[CHAR_RANGE]) {
//    int patternSize = pattern.size(); //calclate the size of the boolean
//
//    //initialize the value in the array to -1
//    for (int i = 0; i < CHAR_RANGE; ++i) {
//        badCharTable[i] = -1; 
//    }
//
//    // Fill the table with the last position of each char in the pattern
//    for (int i = 0; i < patternSize; ++i) {
//        badCharTable[(int)pattern[i]] = i;
//    }
//}
//
//// Function to perform the Boyer-Moore string search using the bad character heuristic
//void boyerMooreSearch(const string &text, const string &pattern) {
//    int textSize = text.size();     // Length of the text
//    int patternSize = pattern.size(); // Length of the pattern
//    int badCharTable[CHAR_RANGE];   // Bad character table
//
//    // Preprocess the pattern to fill in the bad char to the table
//    createBadCharTable(pattern, badCharTable);
//
//    int shift = 0; // Initialize the value of the shift
//    bool found = false; // Flag to check if pattern is found
//
//    while (shift <= (textSize - patternSize)) {
//        int j = patternSize - 1; // Assign the pattern size -1 to the object j.
//
//        // If the pattern and character was match, decrease index j 
//        while (j >= 0 && pattern[j] == text[shift + j]) {
//            j--;
//        }
//
//        // Condition when the text was found in the current shift
//        if (j < 0) {
//            cout << "Pattern found at index " << shift << endl; // show the index where the pattern was found
//            found = true; // update the found boolean
//
//            // Align the string such that the next character in the text matches the last occurrence of the same character in the pattern.
//            shift += (shift + patternSize < textSize) ? patternSize - badCharTable[text[shift + patternSize]] : 1;
//        } else {
//            // Align the string such that the next character in the text matches the last occurrence of the same character in the pattern.
//            shift += max(1, j - badCharTable[text[shift + j]]);
//        }
//    }
//
//    // If pattern was not found in the text prompt the information
//    if (!found) {
//        cout << "The pattern was not found" << endl;
//    }
//}
//
//int main() {
//    string text;    // Input text
//    string pattern; // Input pattern
//
//    // Ask the user enter the text for checking
//    cout << "Enter the text: ";
//    getline(cin, text);
//
//    // Ask the user enter the pattern for searching
//    cout << "Enter the pattern: ";
//    getline(cin, pattern);
//    
//    // Perform the Boyer-Moore search
//    boyerMooreSearch(text, pattern);
//    return 0;
//}


//Implementation of the library
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#define CHAR_RANGE 256 // Define the range of possible characters (ASCII)

// Function to create the bad character table for the Boyer-Moore algorithm
void createBadCharTable(const string &pattern, int badCharTable[CHAR_RANGE]) {
    int patternSize = pattern.size(); // Calculate the size of the pattern

    // Initialize all occurrences as -1
    for (int i = 0; i < CHAR_RANGE; ++i) {
        badCharTable[i] = -1;
    }

    // Fill the table with the last occurrence of each character in the pattern
    for (int i = 0; i < patternSize; ++i) {
        badCharTable[(int)pattern[i]] = i;
    }
}

// Define a function createGoodSuffixTable that takes a pattern, a goodSuffixTable array, and the patternSize as parameters
void createGoodSuffixTable(const string &pattern, int goodSuffixTable[], int patternSize) {
    // Initialize variables i and j
    int borderPos[patternSize + 1];
    int i = patternSize, j = patternSize + 1;

    // Set borderPos[i] to j
    borderPos[i] = j;

    // Create border positions
    while (i > 0) {
        while (j <= patternSize && pattern[i - 1] != pattern[j - 1]) {
            // Update goodSuffixTable if needed
            if (goodSuffixTable[j] == 0) {
                goodSuffixTable[j] = j - i;
            }
            // Update j using borderPos[j]
            j = borderPos[j];
        }
        // Decrement i and j, set borderPos[i] to j
        i--;
        j--;
        borderPos[i] = j;
    }

    // Reset j to borderPos[0]
    j = borderPos[0];

    // Fill the goodSuffixTable with shift values
    for (i = 0; i <= patternSize; ++i) {
        if (goodSuffixTable[i] == 0) {
            goodSuffixTable[i] = j;
        }
        if (i == j) {
            j = borderPos[j];
        }
    }
}

// Define a function preprocess_case2 that takes a goodSuffixTable array and the patternSize as parameters
void preprocess_case2(int goodSuffixTable[], int patternSize) {
    // Initialize j to goodSuffixTable[0]
    int j = goodSuffixTable[0];
    // Iterate to fill the goodSuffixTable with shift values
    for (int i = 0; i <= patternSize; i++) {
        if (goodSuffixTable[i] == 0) {
            goodSuffixTable[i] = j;
        }
        if (i == j) {
            j = goodSuffixTable[j];
        }
    }
}


// Function to perform the Boyer-Moore string search using both heuristics
void boyerMooreSearch(const string &text, const string &pattern) {
    int textSize = text.size();       // Length of the text
    int patternSize = pattern.size(); // Length of the pattern
    int badCharTable[CHAR_RANGE];     // Bad character table
    int goodSuffixTable[patternSize + 1]; // Good suffix table

    // Initialize the good suffix table with zeros
    for (int i = 0; i <= patternSize; ++i) {
        goodSuffixTable[i] = 0;
    }

    // Preprocess the pattern to fill in the bad character table and good suffix table
    createBadCharTable(pattern, badCharTable);
    createGoodSuffixTable(pattern, goodSuffixTable, patternSize);
    preprocess_case2(goodSuffixTable, patternSize);
    int shift = 0;  // Initialize the shift
    bool found = false; // Flag to check if pattern is found

    // Search through the text using Boyer-Moore algorithm
    while (shift <= (textSize - patternSize)) {
        int j = patternSize - 1; // Initialize j to the last character of the pattern

        // Keep reducing j while characters of the pattern and text are matching
        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }

        // If the pattern is found
        if (j < 0) {
            cout << "Pattern found at index " << shift << endl; // Display the index where the pattern is found
            found = true; // Update the found flag

            // Shift the pattern to align the next character in text with the last occurrence of it in the pattern
            shift += goodSuffixTable[0];
        } else {
            // Shift the pattern such that the next character in text aligns with the last occurrence in the pattern
            shift += max(goodSuffixTable[j + 1], j - badCharTable[text[shift + j]]);
        }
    }

    // If the pattern was not found in the text
    if (!found) {
        cout << "The pattern was not found" << endl;
    }
}

int main() {
    string text;    // Input text
    string pattern; // Input pattern

    // Ask the user to enter the text for checking
    cout << "Enter the text: ";
    getline(cin, text);

    // Ask the user to enter the pattern for searching
    cout << "Enter the pattern: ";
    getline(cin, pattern);
    
    // Perform the Boyer-Moore search
    boyerMooreSearch(text, pattern);

    return 0;
}

