/*
 * hasUniqueChars.c
 * 
 * This file contains the hasUniqueChars() function to check if a string has duplicated characters. 
 * This file also contains two helper functions: the seeBits() function is used to 
 * visualize a binary sequence, the checkInvalid() function checks for non-printing characters.
 * 
 * Author: Nicholas Lobaugh
 */

#include <stdio.h>  // fprintf, printf
#include <stdlib.h> // exit() defined here
#include <string.h> // useful string operations
#include <ctype.h>  //useful character operations
#include <stdbool.h>  // to define a boolean type and true, false
                      // see https://en.wikibooks.org/wiki/C_Programming/stdbool.h

#include "binary_convert.h"



/*
 * This function is for debugging by printing out the value
 * of an input insigned long as a binary string.
 */
void seeBits(unsigned long value, char *debug_text) {
  
  // string to represent binary value of variable value
  char *bin_str;

  bin_str = ulong_to_bin_str(value);
  printf("%s%s\n", debug_text, bin_str);
  free(bin_str);
  
}


/*
 * Given an input string of chars, check for any non-printing
 * characters and print an error and exit if the string has any.
 */
void checkInvalid(char * inputStr) {
  char nextChar;
  int i;
  
  for(i = 0; i < strlen(inputStr); i++) {
    nextChar = inputStr[i];

    // if nextChar is invalid (31 or less or 127 as an ascii char code), then bail out
    if ((nextChar <= 31 ) || (nextChar == 127)) {
      fprintf(stderr, "invalid character in string\n");
      exit(EXIT_FAILURE);
    }
  }
}


/*
 * Takes in an input string of any length as an array of chars 
 * and returns true if every chracter (ignoring spaces) only occurs once in the input string, returns false otherwise.
 * 
 * Prints an error message and exits the program if a non-printable character is detected using checkInvalid.
 */
bool hasUniqueChars(char * inputStr) {
  // bail out quickly if any invalid characters
  checkInvalid(inputStr);
  
  int i;   // loop counter
  
  // unsigned long can handle 64 different chars in a string
  // if a bit at a position is 1, then we have seen that character
  unsigned long checkBitsA_z = 0;   // for checking A through z and {|}~
  unsigned long checkBitsexcl_amp = 0;  // for checking ! though @ 

  char nextChar;         // next character in string to check

  // -------------------------------------------------------------
  // This section contains code to display the initial values of checkBitsA_z
  // and checkBitsexcl_amp, for debugging purposes. 
  // It also illustrates how to use the seeBits function for debugging.
  // Printed values should initially be all zeros
  // TODO: remove or comment out this code when satisfied of function correctness
  
  // char debug_str_A_z[128];
  // strcpy(debug_str_A_z, "checkBitsA_z before: \n");
  // seeBits(checkBitsA_z, debug_str_A_z);
  
  // char debug_str_excl_amp[128];
  // strcpy(debug_str_excl_amp, "checkBitsexcl_amp before: \n");
  // seeBits(checkBitsexcl_amp, debug_str_excl_amp);
  // -------------------------------------------------------------
  
  // TODO: Declare additional variables you need here
  unsigned long nextChar_bit_pos = 0;

  
  for(i = 0; i < strlen(inputStr); i++) {
    nextChar = inputStr[i];

    printf("checkBitsA_z: %s\n", ulong_to_bin_str(checkBitsA_z));
    printf("checkBitsexcl_amp: %s\n", ulong_to_bin_str(checkBitsexcl_amp));

    if (nextChar >= 65 && nextChar <= 126) {  // if "A" through "~"
      nextChar_bit_pos = 1 << (nextChar - 65);
      printf("nextChar: %c  nextChar_bit_pos: %s\n", nextChar, ulong_to_bin_str(nextChar_bit_pos));
      printf("nextChar_bit_pos & checkBitsA_z: %lu\n", nextChar_bit_pos & checkBitsA_z);
      if (nextChar_bit_pos & checkBitsA_z) { // if bitwise ANDing results in anything but 0 then return false, else add nextChar_bit_pos to checkBitsA_z
        printf("returned false\n");
        return false;
      }
      else {
        checkBitsA_z = nextChar_bit_pos + checkBitsA_z;
      }
    }
    else if (nextChar >= 33 && nextChar <= 64) {  // if "!" through "@"
      nextChar_bit_pos = 1 << (nextChar - 33);
      printf("nextChar: %c  nextChar_bit_pos: %s\n", nextChar, ulong_to_bin_str(nextChar_bit_pos));
      printf("nextChar_bit_pos & checkBitsexcl_amp: %lu\n", nextChar_bit_pos & checkBitsexcl_amp);
      if (nextChar_bit_pos & checkBitsexcl_amp) { // if bitwise ANDing results in anything but 0 then return false, else add nextChar_bit_pos to checkBitsexcl_amp
        printf("returned false\n");
        return false;
      }
      else {
        checkBitsexcl_amp = nextChar_bit_pos + checkBitsexcl_amp;
      }
    }


    // -------------------------------------------------------------
    // Below this are examples of debugging print statements you could use
    // Move/use as makes sense for you!
    // Modify to work on checkBitsexcl_amp
    // TODO: Comment out or remove when your function works correctly
    // printf("nextchar int value: %d\n", nextChar);
    // char char_str[2] = "\0";
    // char_str[0] = nextChar;

    // strcpy(debug_str_A_z, "nextchar: ");
    // strcat(debug_str_A_z, char_str);
    // strcat(debug_str_A_z,", checkBitsA_z: \n");
    // seeBits(checkBitsA_z, debug_str_A_z);

    // strcpy(debug_str_excl_amp, "nextchar: ");
    // strcat(debug_str_excl_amp, char_str);
    // strcat(debug_str_excl_amp,", checkBitsexcl_amp: \n");
    // seeBits(checkBitsexcl_amp, debug_str_excl_amp);
    // ------------------------------------------------------------- 
  }

  // if through all the characters, then no duplicates found
  return true;
  
}
