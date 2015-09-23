/* pathgen.c 
 * Inspired by C Programming a Modern Approach 
 * 2nd Edition p. 179
 *
 * A program that genrates a random path walk
 *
 * Copyright (c) 2014 Gregory D. Stula
 * All Rights Reserved 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// matrix/plot dimensions
#define ROWS 10
#define COLS 10

// step array length 
#define STEP_LEN 21

// directions for steps
#define NORTH 0
#define SOUTH 3

#define EAST 1
#define WEST 2


char path[ROWS][COLS] = {{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'}, 
                         {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'}};
// keep track of steps
bool has_stepped[ROWS][COLS] = {{false}};

const char steps[STEP_LEN] = { 'G', 'R', 'E', 'G', 'O', 'R', 'Y', '@', 'd', 'o', 'u', 'g', 
                                                      'l', 'a', 's', '@', 'S', 'T', 'U', 'L', 'A'};

void walk_path(void);
void print_path(void);

int main(void)
{
        walk_path();
        print_path();
        return 0;
}

void walk_path(void)
{
          // For work with 0 - 9
        int max_col = COLS - 1;
        int max_row = ROWS - 1;

        // seed rng
        srand((unsigned) time(NULL));
        
        // starting point
        int i_pos = 0;
        int j_pos = 0;

        bool terminate_early = false;

        for (int i = 0; i < STEP_LEN; i++) {
                // true if no legal moves are left.
                if (terminate_early == true)
                        break;
                                
                char current_step = steps[i];
                path[i_pos][j_pos] = current_step;
                // can't step in taken spot
                has_stepped[i_pos][j_pos] = true;

                // switches for early termination condition
                bool tried[4] = {false, false, false, false};

                for(;;) {
                        int next_move = rand() % 4;
                         // tried all moves, no legal moves, so terminate early
                        if ((tried[NORTH] && tried[SOUTH]) && (tried[EAST] && tried[WEST])) {
                                terminate_early = true;
                                break;
                        // if not 0 or max, and haven't stepped, go ahead and step.
                        } else if (next_move == NORTH) {
                                tried[NORTH] = true;
                                if (i_pos != 0) { 
                                        if (!has_stepped[i_pos - 1][j_pos]) {
                                                i_pos--;
                                                break;
                                        }
                                }
                        } else if (next_move == SOUTH) {
                                tried[SOUTH] = true;
                                if (i_pos != max_row) {
                                        if (!has_stepped[i_pos + 1][j_pos]) {
                                                i_pos++;
                                                break;
                                        }
                                }
                        } else if (next_move == EAST) {
                                tried[EAST] = true;
                                if (j_pos != 0) {
                                        if (!has_stepped[i_pos][j_pos - 1]) {
                                                j_pos--;
                                                break;
                                        }
                                }
                        } else if (next_move == WEST) {
                                tried[WEST] = true;
                                if(j_pos != max_col) {
                                        if (!has_stepped[i_pos][j_pos + 1]) {
                                                j_pos++;
                                                break;
                                        }
                                }
                        }
                }
        }
} 

void print_path(void)
{
        for (int i = 0; i < ROWS; i++) {
                printf("\n");
                for (int j = 0; j < COLS; j++) {
                        printf("%c ", path[i][j]);
                }
        }
        printf("\n");
}
