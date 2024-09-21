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
      fprintf(stderr, "invalid character in string: ");
      printf("%s\n", inputStr);
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
  
  unsigned long nextChar_bit_pos; // 8 bytes of 0s except for one 1 bit that will change position based on nextChar's value

  
  for(i = 0; i < strlen(inputStr); i++) {
    nextChar = inputStr[i];
    nextChar_bit_pos = 1; // reset to 1 to be used later in place of "1" in order to preserve full 8 bytes and prevent overflow

    // printf("checkBitsA_z: %s\n", ulong_to_bin_str(checkBitsA_z));
    // printf("checkBitsexcl_amp: %s\n", ulong_to_bin_str(checkBitsexcl_amp));

    if (nextChar >= 65 && nextChar <= 126) {  // if "A" through "~"
      nextChar_bit_pos = nextChar_bit_pos << (nextChar - 65);

      // printf("nextChar: %c   value: %d   nextChar_bit_pos: %s\n", nextChar, nextChar, ulong_to_bin_str(nextChar_bit_pos));
      // printf("nextChar_bit_pos & checkBitsA_z: %lu\n", nextChar_bit_pos & checkBitsA_z);

      if (nextChar_bit_pos & checkBitsA_z) { // if bitwise ANDing results in anything but 0 then return false, else add nextChar_bit_pos to checkBitsA_z
        // printf("returned false\n");
        return false;
      }
      else {
        checkBitsA_z = nextChar_bit_pos + checkBitsA_z;
      }
    }
    else if (nextChar >= 33 && nextChar <= 64) {  // if "!" through "@"
      nextChar_bit_pos = nextChar_bit_pos << (nextChar - 33);

      // printf("nextChar: %c   value: %d   nextChar_bit_pos: %s\n", nextChar, nextChar, ulong_to_bin_str(nextChar_bit_pos));
      // printf("nextChar_bit_pos & checkBitsexcl_amp: %lu\n", nextChar_bit_pos & checkBitsexcl_amp);
      
      if (nextChar_bit_pos & checkBitsexcl_amp) { // if bitwise ANDing results in anything but 0 then return false, else add nextChar_bit_pos to checkBitsexcl_amp
        // printf("returned false\n");
        return false;
      }
      else {
        checkBitsexcl_amp = nextChar_bit_pos + checkBitsexcl_amp;
      }
    }
  }

  // if through all the characters, then no duplicates found
  return true;
  
}
