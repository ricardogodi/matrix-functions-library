
// Author: Ricardo Gonzalez
// Project #2

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "prog2.h"
#include <stdbool.h>

/***********************************************
 *                                             **
 *   MATRIX FUNCTIONS                          **
 *                                             **
 *   NOTE:  parameter n ALWAYS expresses the   **
 *     dimensions of the square matrix in      **
 *     question.                               **
 *                                             **
 ***********************************************/
char ** alloc_square_mtx(int n) {
    char **m;
    char i;
    m = malloc(n * sizeof(char*)); // Create array of pointers to rows
    for (i = 0; i < n; i++) {
        m[i] = malloc(sizeof(char) * n);  // Create rows
    }
    return m;
}

void free_square_mtx(char **m, int n) {
    for(int i = 0; i < n; i++) {
        free(m[i]);     // Free rows
    }
    free(m);        // Free array of pointer to rows
}

void pop_mtx_alpha(char **m, int n){
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m[i][j] = rand() % 26 + 'a';
        }
    }
}

void display_mtx(char **m, int n){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c ", m[i][j]);
        }
        printf("\n");
    }
}

void swap_rows(char **m, int n, int r1, int r2){
    char temp;
    for (int i = 0; i < n; i++) {
        temp = m[r1][i];
        m[r1][i] = m[r2][i];
        m[r2][i] = temp;
    }
}

void swap_cols(char **m, int n, int c1, int c2){
    char temp;
    for (int i = 0; i < n; i++) {
        temp = m[i][c1];
        m[i][c1] = m[i][c2];
        m[i][c2] = temp;
    }
}

void rotate_right(char **m, int n){
    char temp;
    for (int i = 0; i < n; i++) {   // rotate with respect to diagonal
        for (int j = 0; j < i; j++) {
            temp = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = temp;
        }
    }
    for (int i = 0; i < n; i++) {   // rotate with respect to middle column
        for (int j = 0; j < n/2; j++) {
            temp = m[i][j];
            m[i][j] = m[i][n - 1 - j];
            m[i][n - 1 - j] = temp;
        }
    }
}

void floating_boulders(char **m, int n, int nb){
    srand(time(NULL));
    int rndm;
    int diff = nb - n*n;
    int arr[n*n];  // to keep track of random numbers
    for (int i = 0; i < n*n; i++) {  // Fill 1D arr with -1's
        arr[i] = -1;
    }
    for (int i = 0; i < n; i++) {  // Fill 2D arr with '.'
        for (int j = 0; j < n; j++) {
            m[i][j] = '.';
        }
    }
    while (nb > diff && nb > 0) {
        rndm = rand() % (n*n);
        if (arr[rndm] != rndm) {
            m[rndm / n][rndm % n] = '#';
            arr[rndm] = rndm;
            nb--;
        }
    }
}

void mountains(char **m, int n){
    srand(time(NULL));
    int rndm;
    for (int i = 0; i < n; i++) {  // Fill 2D arr with '#'
        for (int j = 0; j < n; j++) {
            m[i][j] = '#';
        }
    }
    for (int i = 0; i < n; i++) {
        rndm = rand() % n + 1;
        for (int j = 0; j < rndm; j++) {  // iterate rows
            m[j][i] = '.';
        }
    }
}

void sink(char **m, int n){
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j >= 1; j--) {
            m[j][i] = m[j - 1][i];
        }
    }
    for (int i = 0; i < n; i++) {
        m[0][i] = '.';
    }
}

void gravity(char **m, int n){
    
    int surfaceIndx;
    for (int i = 0; i < n; i++) {
        surfaceIndx = -1;
        for (int j = n - 1; j >= 0; j--) {  // Find the 'surface' index
            if (m[j][i] == '.') {
                surfaceIndx = j;
                break;
            }
        }
        for (int j = surfaceIndx; j >= 0; j--) {  // Find block
            if(m[j][i] != '.') {
                m[surfaceIndx][i] = m[j][i];  // Place it in surface
                m[j][i] = '.';
                surfaceIndx = surfaceIndx - 1;  // Now surface is one index above
            }
        }
    }
}

/***********************************************
 *                                             **
 *   STRING FUNCTIONS                          **
 *                                             **
 ***********************************************/
void str_trim(char* s) {
    int i = 0;
    bool found = false;
    int startIndx = 0;
    int endIndx = 0;
    int size;
    while (s[i] != '\0') {      // Find index of first non-whitespace char
        if (!isspace(s[i]) && !found) {
            startIndx = i;
            found = true;
        }
        i++;
    }
    size = i;  //
    i = size - 1;
    while (i >= 0) {    // Find index of last non-whitespace char
        if (s[i] != ' ') {
            endIndx = i;
            break;
        }
        i--;
    }
    i = 0;
    while (i < (endIndx - startIndx + 1)) { // Move characters to their respective place
        s[i] = s[startIndx + i];
        i++;
    }
    s[endIndx - startIndx + 1] = '\0';  // Place '\0' after index of last non-whitespace char
}

int str_search(char *s, char *pattern) {
    int i, j, k;
    int found = true;
    i = 0;
    while (s[i] != '\0') {
        if(s[i] == pattern[0]) {  // If first char of the subtring matches a char in the string
            j = i;
            k = 0;
            found = true;
            while (pattern[k] != '\0') {  // Traverse substring to check if every char matches
                if (s[j] != pattern[k]) {
                    found = false;
                }
                j++;
                k++;
            }
            if (found) {
                return i;
            }
        }
        i++;
    }
    return -1;
}

#ifndef _LIB  // DO NOT REMOVE THIS LINE!!!
// IT DOESN"T CHANGE HOW YOUR PROGRAM
// WORKS, BUT IT GIVES US A WAY TO CALL
// YOUR FUNCTIONS FROM OUR CODE FOR
// TESTING

/**
 * Write a test driver in main below to exercise and
 *   your function implementations.
 *
 * Think carefully about your test cases!
 */

int* clone(int arr[], int n) {
    int * ptr = malloc(n *sizeof(int));
    for (int i = 0; i < n; i++) {
        ptr[i] =  arr[i];
    }
    return ptr;
}

int main() {
    int n = 6;
    printf("Function name: alloc_square_mtx\n");
    printf("Allocating memory for a %i by %i matrix...\n", n, n);
    char ** m = alloc_square_mtx(n);
    printf("\n");
    
    printf("Function name: pop_mtx_alpha\n");
    pop_mtx_alpha(m, n);
    display_mtx(m, n);
    printf("\n");
    
    printf("Function name: swap_rows\n");
    printf("Swapping rows 0 and 1\n");
    swap_rows(m, n, 0, 1);
    display_mtx(m, n);
    printf("\n");
    
    printf("Function name: swap_cols\n");
    printf("Swapping columns 2 and 3\n");
    swap_cols(m, n, 2, 3);
    display_mtx(m, n);
    printf("\n");
    
    printf("Function name: rotate_right\n");
    rotate_right(m, n);
    display_mtx(m, n);
    printf("\n");
    
    printf("Function name: floating_boulders\n");
    printf("Arbitrary number of blocks: 26\n");
    floating_boulders(m, n, 26);
    display_mtx(m, n);
    printf("\n");
    
    printf("Function name: mountains\n");
    mountains(m, n);
    display_mtx(m, n);
    printf("\n");
    
    printf("Function name: sink\n");
    sink(m, n);
    display_mtx(m, n);
    printf("\n");
    
    printf("Function name: gravity\n");
    printf("Filling array with 'blocks' first:\n");
    floating_boulders(m, n, 20);
    display_mtx(m, n);
    printf("\n");
    gravity(m, n);
    printf("Applying gravity:\n");
    display_mtx(m, n);
    printf("\n");
    
    printf("Function name: alloc_square_mtx\n");
    printf("Dellocating memory of matrix m...\n");
    free_square_mtx(m, n);
    printf("\n");
    
    printf("Function name: str_trim\n");
    char str[20] = {' ',' ','H', 'e', 'l', 'l', 'o',' ',' ',' ',' ',' '};
    printf("C string before trimming:\n");
    printf("'%s'\n", str);
    str_trim(str);
    printf("C string after trimming:\n");
    printf("'%s'\n", str);
    printf("\n");
    
    printf("Function name: str_search\n");
    char s[20] = {'a','b','r','a','c','a','d','a','b','r','a'};
    printf("'%s'\n", s);
    printf("Looking for:\n");
    char pattern[20] = {'c','a','d','a'};
    printf("'%s'\n", pattern);
    printf("return value: %i\n", str_search(s, pattern));
}



#endif        // DO NOT REMOVE THIS LINE!!!

/*
"abcd"                  "ab"             0
*                  "abcd"                  "aa"             -1
*                  "abc bc d"              "bc"             1
*                  "abcd"                  "bcd"            1
*                  "abcd"                  "bcd"            1
*                  "abracadabra"           "dab"            6
*                  "abc"                   "abc"            0
*                  "abc"                   "abcd"           -1
*/




/*
printf("n = %i\n", n);
printf("rndm = %i\n", rndm);

printf("rndm / 4 = %i\n", rndm / 4);
printf("rndm %% 4 = %i\n", rndm % 4);
*/




/*
 void str_trim(char* s) {
     int startIndx;
     int size;
     int i = 0;
     while (s[i] != '\0') {
         if (!isspace(s[i])) {
             startIndx = i;
             break;
         }
         i++;
     }
     s = s + i;  // Pointer arithmetic
     i = 0;
     
     while (s[i] != '\0') {
         i++;
     }
     size = i;
     
     i = size - 1;
     while (i >= 0) {
         if(!isspace(s[i])) {
             s[i + 1] = '\0';
             break;
         }
         i--;
     }
 }
 */
