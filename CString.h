#ifndef STRINGS_H
#define STRINGS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
// Change to 0 if you don't want the program to halt if a string related issue arrises
int AllowExit = 1;

#define STRING_OVERFLOW "String Overflow! Your string is larger than the allocated length!"
#define ALLOCATION_ERROR "Major Allocation Error!"
#define LENGTH_ZERO "String lengths cannot be zero"
#define LENGTH_NEGATIVE "String lengths cannot be negative"
#define INDEX_OUT_OF_BOUNDS "Index out of bounds! Your string length is shorter than the given index!"

typedef char* string; 

// Exits out of the program if an error occurs
void HandleError(string origin, string errorcode) {
    printf("\n\n********** CSTRING.H ERROR **********\n");
    printf("\033[1;31mERROR AT %s: %s\033[0m\n", origin, errorcode);  // Makes it red, how cool!!!
    printf("*************************************\n\n");
    if (AllowExit == 1) exit(EXIT_FAILURE);
}

// Allocates 256 lines of characters and initialises string to ""
string InitStr() {
    string str = (string)malloc(sizeof(char) * 257); // 257 the 7th is null terminated char
    if (str == NULL) HandleError("INITSTR()", ALLOCATION_ERROR);
    str[0] = '\0';
    return str;
}

// Allocates lines of characters based on length and initialises string to ""
string InitStrLen(int length) {
    if (length < 0) HandleError("INITSTRLEN()", LENGTH_NEGATIVE);
    if (length == 0) HandleError("INITSTRLEN()", LENGTH_ZERO);

    string str = (string)malloc(sizeof(char) * length);
    if (str == NULL) HandleError("INITSTR()", ALLOCATION_ERROR);
    str[0] = '\0';
    return str;
}

// Rewritten strlen to fit strings.h CamlCase standard
size_t StrLen(string str) {
    return strlen(str);
}

// Runs through each character to count the total length
int Length(string str) {
    int i = 0;
    while (str[i] != '\0') i++;
    return i;
}

// Dynamically allocates a string by calculating its size before allocation and initialises string to val
string NewStr(string val) {
    int length = strlen(val);
    if (length == 0) HandleError("NEWSTR()", LENGTH_ZERO);

    string str = (string)malloc(sizeof(char) * (length + 1));
    if (str == NULL) HandleError("NEWSTR()", ALLOCATION_ERROR);

    strncpy(str, val, length);
    str[length] = '\0'; 
    return str;
}

// Allocates 256 lines of characters for the string and initialises string to val
string NewStrStatic(string val) {
    string str = (string)malloc(sizeof(char) * 257);
    if (str == NULL) HandleError("NEWSTRSTATIC()", ALLOCATION_ERROR);
    if (strlen(val) > 257) HandleError("NEWSTRSTATIC()", STRING_OVERFLOW);
    strncpy(str, val, 256);
    str[256] = '\0'; 
    return str;
}


// Allocates lines of character for the string based on length and initialises string to val
string NewStrLen(string val, int length) {
    if (length < 0) HandleError("NEWSTRLEN()", LENGTH_NEGATIVE);
    if (length == 0) HandleError("NEWSTRLEN()", LENGTH_ZERO);
    if (strlen(val) > length) HandleError("NEWSTRLEN()", STRING_OVERFLOW);

    string str = (string)malloc(sizeof(char) * (length + 1));
    if (str == NULL) HandleError("NEWSTRLEN()", ALLOCATION_ERROR);
    str[length] = '\0';
    strncpy(str, val, length);
    return str;
}

// Resizes the length of a string by reallocating it to the new size
void RenewStrLen(string existingStr, int length) {
    if (length < 0) HandleError("RENEWSTRLEN()", LENGTH_NEGATIVE);
    if (length == 0) HandleError("RENEWSTRLEN()", LENGTH_ZERO);
    if (strlen(existingStr) > length) HandleError("RENEWSTRLEN()", STRING_OVERFLOW);

    existingStr = (string)realloc(existingStr, sizeof(char) * (length + 1));
    if (existingStr == NULL) HandleError("RENEWSTRLEN()", ALLOCATION_ERROR);
    existingStr[length] = '\0';
}


// Updates the string to newstr and dynamically updates the size
void UpdateStr(string oldstr, string newstr) {
    int maxLength = strlen(newstr);
    if (strlen(oldstr) > maxLength) maxLength = strlen(oldstr);

    if (maxLength == 0) HandleError("UPDATESTR()", LENGTH_ZERO);

    RenewStrLen(oldstr, maxLength);
    strncpy(oldstr, newstr, maxLength);
}


/*String Input/Output*/

// Gets format specifiers and prints the string with a new line
void println(string str, ...) {
    va_list args;
    va_start(args, str);
    vprintf(str, args);
    va_end(args);
    printf("\n", str);
}

// Reads a line of string sized 256 characters
string ScanStr() {
    string str = InitStr();
    if (fgets(str, 256, stdin) != NULL) {
        // Changes the new line to null termination
        size_t length = StrLen(str);
        if (str[length - 1] == '\n') {
            str[length - 1] = '\0';
        }
    }
    return str;
}

// Reads a line of string sized at length 
string ScanStrLen(int length) {
    if (length < 0) HandleError("SCANSTRLEN()", LENGTH_NEGATIVE);
    if (length == 0) HandleError("SCANSTRLEN()", LENGTH_ZERO);

    string str = InitStrLen(length);
    if (fgets(str, length, stdin) != NULL) {
        // Changes the new line to null termination
        size_t length = StrLen(str);
        if (str[length - 1] == '\n') {
            str[length - 1] = '\0';
        }
    }
    return str;
}

// prints the prompt and reads a line of string sized at 256 characters
string Input(string prompt) {
    printf("%s\n", prompt);
    string str = InitStr();
    if (fgets(str, 256, stdin) != NULL) {
        // Changes the new line to null termination
        size_t length = StrLen(str);
        if (str[length - 1] == '\n') {
            str[length - 1] = '\0';
        }
    }
    return str;
}

/*
string concatenate(string str1, string str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    string str1_newsize = NewStrLen(len1 + len2 + 1);
    str1_newsize = str1;
    strcat(str1_newsize, str2);
    return str1_newsize;
}*/

// Gets the character of a string at the given index
char CharAtIndex(string str, int index) {
    if (index > (strlen(str) - 1)) HandleError("CHARATINDEX()", INDEX_OUT_OF_BOUNDS);
    return str[index];
}

/*TYPE TO STRING CONVERSION*/
// Converts a char to string sized at 256 characters
string CharToString(char val) {
    string str = InitStr();
    sprintf(str, "%c", val);
    return str;
}
// Converts an integer to a string
string IntToStr(int val) {
    string str = InitStr();
    sprintf(str, "%d", val);
    return str;
}
// Converts a float to a string
string FloatToStr(float val) {
    string str = InitStr();
    sprintf(str, "%f", val);
    return str;
}
// Converts a double to a string
string DoubleToStr(float val) {
    string str = InitStr();
    sprintf(str, "%lf", val);
    return str;
}

// Compares between string and checks if they are equivalent
bool StrEquals(string str1, string str2) {
    int length1 = strlen(str1); int length2 = strlen(str2);
    if(length1 != length2) return false;
    for (int i = 0; i < length1; i++) {
        if (str1[i] != str2[i]) {
            return false;
        }
    }
    return true;
}




#endif // STRING_H