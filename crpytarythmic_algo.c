#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10

// Maps characters A-Z to digits 0-9
int charToDigit[26];
// Tracks if a digit is used or not
bool usedDigits[MAX];

// Converts a given word to a number using charToDigit mapping
long long convertToNumber(char *str) {
    long long num = 0;
    for (int i = 0; str[i]; i++) {
        num = num * 10 + charToDigit[str[i] - 'A'];  // Construct the number digit by digit
    }
    return num;
}

// Recursively tries to assign digits to unique characters
bool solvePuzzle(char *str1, char *str2, char *result, int index, char *uniqueChars, int uniqueLen) {
    // If all characters have been assigned digits
    if (index == uniqueLen) {
        long long num1 = convertToNumber(str1);
        long long num2 = convertToNumber(str2);
        long long res = convertToNumber(result);

        // Check if the sum of num1 and num2 equals res
        return (num1 + num2 == res);
    }

    // Try assigning all digits from 0 to 9 to the current character
    for (int digit = 0; digit < MAX; digit++) {
        if (!usedDigits[digit]) {  // Check if the digit is not used
            // Assign the digit to the current character
            usedDigits[digit] = true;
            charToDigit[uniqueChars[index] - 'A'] = digit;

            // Recurse for the next character
            if (solvePuzzle(str1, str2, result, index + 1, uniqueChars, uniqueLen)) {
                return true;  // Solution found
            }

            // Backtrack: Unmark the digit as used
            usedDigits[digit] = false;
        }
    }

    return false;  // No solution found with current assignment
}

// Collects all unique characters from the input words
int extractUniqueChars(char *str1, char *str2, char *result, char *uniqueChars) {
    bool seen[26] = {false};  // Tracks if a character is already counted
    int index = 0;

    // Check each word for unique characters
    char *allStrings[] = {str1, str2, result};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; allStrings[i][j]; j++) {
            int pos = allStrings[i][j] - 'A';
            if (!seen[pos]) {  // If character is not already added
                seen[pos] = true;
                uniqueChars[index++] = allStrings[i][j];  // Add character to the list
            }
        }
    }

    uniqueChars[index] = '\0';  // Null-terminate the string
    return index;  // Return the number of unique characters
}

int main() {
    char str1[20], str2[20], result[20], uniqueChars[27];

    // Take input words from user
    printf("Enter first word: ");
    scanf("%s", str1);

    printf("Enter second word: ");
    scanf("%s", str2);

    printf("Enter result word: ");
    scanf("%s", result);

    // Initialize arrays
    memset(charToDigit, -1, sizeof(charToDigit));  // Mark all characters as unassigned
    memset(usedDigits, false, sizeof(usedDigits));  // Mark all digits as unused

    // Extract unique characters from input words
    int uniqueLen = extractUniqueChars(str1, str2, result, uniqueChars);

    // Try to solve the puzzle
    if (solvePuzzle(str1, str2, result, 0, uniqueChars, uniqueLen)) {
        printf("Solution Found:\n");
        for (int i = 0; i < uniqueLen; i++) {
            printf("%c = %d\n", uniqueChars[i], charToDigit[uniqueChars[i] - 'A']);
        }
    } else {
        printf("No solution exists.\n");
    }

    return 0;
}
