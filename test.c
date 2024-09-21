/*
 * This file contains tests for the hasUniqueChars function.
 *
 * Author: Nicholas Lobaugh
 */

#include <stdio.h>    // printf
#include <stdbool.h>  // to define a boolean type and true, false
#include <string.h>   // strcpy  to copy a string
#include <assert.h>


// declaration of function from hasUniqueChars.c
bool hasUniqueChars(char * inputStr);


int main() {

  // ------------------------------------------------------------
  // Examples of declaring string constants
  /* Example 1 */
  char string1[] = "A string declared as an array.\n";

  /* Example 2 */
  char *string2 = "A string declared as a pointer.\n";

  /* Example 3 */
  char string3[128];   // can copy in up to 127 characters
                       // chose 128 because it is a multiple of 8 bytes
  strcpy(string3, "A string constant copied in.\n");

  // You can uncomment these to see how the strings were initialized above.
  // Then you can comment these out again once you see that the 
  // strings were created correctly
  // printf ("%s", string1);
  // printf ("%s", string2);
  // printf ("%s", string3);

  // -------------------------------------------------------------
  // Thorough and exhaustive tests of hasUniqueChars()  
  bool ok;    // holds the result of hasUniqueChars(); used in asserts
  
  // Test 1: a test case that should return false because characters are duplicated
  strcpy(string3, "This should fail (l and s and i and h)");
  ok = hasUniqueChars(string3);
  assert(!(ok));
  
  // Test 2: This should be true and not fail, but won't work until you
  // complete the hasUniqueChars() function
  strcpy(string3, "abcdefghij");
  ok = hasUniqueChars(string3);
  assert(ok);
  
  // TODO: add your tests here

  // Task 3 Test 1: Tests non-duplicated edge cases at ends of ranges separated by multiple spaces. This should be true and not fail.
  strcpy(string3, "!  @  A  ~");
  ok = hasUniqueChars(string3);
  assert(ok);

  // Task 3 Test 2: Tests all printable characters with no duplications. This should be true and not fail.
  strcpy(string3, "!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");
  ok = hasUniqueChars(string3);
  assert(ok);

  // Task 3 Test 3: Tests all printable characters with two duplications ("@" and "a"). This should return false.
  strcpy(string3, "!\"#$%&\'()*+,-./0123456789:;<=>?@@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`aabcdefghijklmnopqrstuvwxyz{|}~");
  ok = hasUniqueChars(string3);
  assert(!(ok));

  // Task 3 Test 4: Tests a nonprintable escape sequence character. This should trigger checkIvalid() and exit the program.
  strcpy(string3, "escape \e");
  ok = hasUniqueChars(string3);

  // NOTE: if you add a \n to any tests, this should cause the
  //       exit failure given. Keep this test last so you can check 
  //       that others pass or fail as you expect them to.
  strcpy(string3, "a b cc\n");
  ok = hasUniqueChars(string3);
  // other examples that should fail that you can place in strings
  // are \0 or \t or \r
  // See problem description for more details about escape sequences
  
  return 0;
}