#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CString.h"

// Demo of all the functions in CString.h here!
int main() {
    println("println() prints with a new line with %s like this one %d", "format specifiers", 1234);

    string str = NewStrStatic("I am a static string IE 256 characters long");
    println("str0: %s", str);


    /*These functions initialises your string as well as allocates memory
    They are called when you first define a string and shouldn't be used more than once!*/
    string str0 = InitStr();
    println("str0: %s IE it's empty you can't even see it", str0);

    string str1 = NewStr("I am a dynamically allocated string, no setting of lengths involved. As big as integer allows");
    println("str1: %s", str1);

    string str2 = NewStrLen("I'm a string with a length", 50);
    println("str2: %s", str2);

    string str3 = NewStrLen("Any case of failure (like too low length or negative) exits the program, for example change 100 to 5", 100);
    println("str3: %s", str3);

    string str4 = NewStrLen("Unless you set AllowExit to 1", 50);
    println("str3: %s", str4);

    string str5 = NewStr("ENOUGH OF INITIALISING STRINGS! Let's UPDATE them!");
    println("str5: %s", str5);


    /*These functions update your string, they could be called as much as you wish*/
    RenewStrLen(str5, 100);
    println("str5: %s %s", str5, "ALREADY UPDATED! ITS THE SAME STR WITH NEW LENGTH!!");

    UpdateStr(str5, "I've been updated to another string! Same pointer and everything, with a dynamically renewed length if it's too big or too small!!");
    println("str5: %s", str5);


    /*IO*/
    println("What is your name?");
    string name = ScanStr();
    println("Hello %s", name);
    string hobby = Input("Whats your hobby?");
    println("Your hobby is: %s", hobby);

    return 0;
}