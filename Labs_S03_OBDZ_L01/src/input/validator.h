#ifndef VALIDATOR_H
#define VALIDATOR_H

#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// maximum number of digits for your target data type;
// unsigned int 10
#define DIGITS 10
// Account for sign character, newline, and 0 terminator
#define BUFSIZ (DIGITS)+3 

// Reads unsigned int from console. Reads input until input is invalid. Ctrl + C exits the programm;
unsigned int readUInt32();

// Reads string with length maxLength from console. Reads input until input is invalid. Ctrl + C exits the programm;
char* readString(int maxLength);


#endif // !VALIDATOR_H


