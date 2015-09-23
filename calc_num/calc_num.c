/* C Programming a Modern Approach Second Edition
 * Chapter 10 page 239 - 240.
 *
 * December 15th, 2014
 *
 * Copyright (c) 2014 Gregory D. Stula
 * All rights reserved.
 *
 * This useless software is licenced to whoever receives it. 
 * You can do whatever you want with this software in both
 * binary and source code forms. There are no restrictions.
 *
 */
/****************************************************************
 * const int segments: a global multi dimensional array that    *
 *                    represents the seven segment displays     *
 *                    used in LED displays in calculators       *
 *                                                              *
 *     char digits: a global multi dimensional array            *
 *                   (each segmented digit is 4 chars high).    *         
 *      _        _    _           _     _    _     _    _       *
 *     | |   |   _|   _|   |_|   |_    |_     |   |_|  |_|      *           
 *     |_|   |  |_    _|     |    _|   |_|    |   |_|   _|      *
 *                                                              *
 *                                                              * 
 *                         seg0_                                *
 *                        seg5|_|seg1 middle:seg6               *
 *                        seg4|_|seg2                           *
 *                          seg3                                *
 *                                                              *
 ****************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAX_DIGITS 10
#define DIGIT_ROWS 4
#define DIGIT_COLS 4 * MAX_DIGITS

const int segments[10][7] =    {{1, 1, 1, 1, 1, 1, 0},  // zero
                                {0, 1, 1, 0, 0, 0, 0},  // one
                                {1, 1, 0, 1, 1, 0, 1},  // two
                                {1, 1, 1, 1, 0, 0, 1},  // three
                                {0, 1, 1, 0, 0, 1, 1},  // four
                                {1, 0, 1, 1, 0, 1, 1},  // five
                                {1, 0, 1, 1, 1, 1, 1},  // six
                                {1, 1, 1, 0, 0, 0, 0},  // seven
                                {1, 1, 1, 1, 1, 1, 1},  // eight
                                {1, 1, 1, 1, 0, 1, 1}}; // nine

char digits[DIGIT_ROWS][DIGIT_COLS] = {{' '}};                                

// prototypes
void clear_digits(void);
void process_digit(int digit, int position);
void print_digits(void);

int main(void)
{
        char input;
        int current_digit, digits_processed;

        clear_digits();

        printf("Welcome to Calculator Numbers!\nDigits please: ");
        
        digits_processed = 0;

        while ((input = getchar()) != '\n') {
                if (digits_processed == MAX_DIGITS) 
                        break;
                // skip all non digit characters
                if (input < '/' || input > ':') 
                        continue;

                current_digit = atoi(&input);
                process_digit(current_digit, digits_processed);
                digits_processed++;
        }
        print_digits();
}

void clear_digits(void)
{       
        for (int i = 0; i < DIGIT_ROWS; i++) {
                for (int j = 0; j < (DIGIT_COLS); j++) {
                        digits[i][j] = ' ';
                }
        }
}

void process_digit(int digit, int position)
{   
        if (position > MAX_DIGITS) 
                exit(1);

        // positions run between 0 - MAX_DIGITS - 1
        int current_column = position * DIGIT_ROWS ;

        /* {{' ', '_', ' ', ' '},
            {'|', '_', '|', ' '},
            {'|', '_', '|', ' '}
            {' ', ' ', ' ', ' '}}; */

        /***************************************************** 
         * Define the seven segment locations relative to
         * to the current column we are on in the digits array.
         * Segment definitions come from the book, they are
         * not necessarily intuitive.
         * NOTE: Row 3 is always spaces.
         *****************************************************/
        int seg0 = current_column + 1; // row = 0
        int seg1 = current_column + 2; // row = 1
        int seg2 = current_column + 2; // row = 2
        int seg3 = current_column + 1; // row = 2
        int seg4 = current_column;     // row = 2   
        int seg5 = current_column;     // row = 1
        int seg6 = current_column + 1; // row = 1

        // write the 7 segments
        for (int i= 0; i < 7; i++) { 
                if (segments[digit][i]) {
                        switch (i) {
                        case 0: digits[0][seg0] = '_'; break;
                        case 1: digits[1][seg1] = '|'; break;
                        case 2: digits[2][seg2] = '|'; break;
                        case 3: digits[2][seg3] = '_'; break;
                        case 4: digits[2][seg4] = '|'; break;
                        case 5: digits[1][seg5] = '|'; break;
                        case 6: digits[1][seg6] = '_'; break;
                        }
                }
        }
}

void print_digits(void)
{
        for (int i = 0; i < DIGIT_ROWS; i++) {
                printf("\n");
                for (int j = 0; j < (DIGIT_COLS); j++) {
                        printf("%c", digits[i][j]);
                }
        }
        printf("\n");
}
