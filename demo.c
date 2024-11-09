#include <stdio.h>
#include <stdlib.h>
#include "CString.h"

// Demo of CString functions
int main() {
    // NewStr allows dynamic allocation which allocates the same exact
    // length of the string argument
    println("Allocation----------------------");
    string str1 = NewStr("Java");
    string str2 = NewStr("C++");
    println("str1: %p | %s", str1, str1);
    println("str2: %p | %s", str2, str2);


    // To change the value of a string, you use UpdateStr which allows updating without 
    // changing the pointer and with dynamic length reallocation
    println("Updating----------------------");
    UpdateStr(str1, "Javascript");
    UpdateStr(str2, "Python");
    println("str1: %p | %s", str1, str1);
    println("str2: %p | %s", str2, str2);

    // You can use StrEquals to check if two strings are equivalent
    println("Updating------Checking if Equals----");
    UpdateStr(str1, "Rust");
    UpdateStr(str2, "Rust");
    println("str1: %p | %s", str1, str1);
    println("str2: %p | %s", str2, str2);

    if (StrEquals(str1, str2)) {
        println("str1 == str2");
    }

    free(str1); free(str2); 

    // You can allocate the same defined variable changing its pointer and size
    println("Allocating String Again----------");
    str1 = NewStrStatic("Rust is better"); // Allocates 256
    str2 = NewStrLen("C++ is better", 15); // Allocates based on length (15 in this case)
    println("str1: %p | %s", str1, str1);
    println("str2: %p | %s", str2, str2);

    // RenewStr allows you to resize the same segment keeping you the same pointer by calling realloc
    // Which is the primary method of resizing strings
    println("Reallocating--------------");
    RenewStrLen(str1, 30);
    RenewStrLen(str2, 30);
    println("str1: %p | %s", str1, str1);
    println("str2: %p | %s", str2, str2);

    free(str1); free(str2);
    return 0;
}