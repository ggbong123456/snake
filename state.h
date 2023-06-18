#ifndef STATE_H
#define STATE_H
#include <stdio.h>
#include <stdbool.h>

typedef struct snake_t{
  unsigned int tail_x;
  unsigned int tail_y;
  unsigned int head_x;
  unsigned int head_y;
  bool live;
}snake_t;

typedef struct game_state_t{
  unsigned int x_size;
  unsigned int y_size;
  char** board;
  unsigned int num_snakes;
  snake_t* snake;
}game_state_t;


#endif
