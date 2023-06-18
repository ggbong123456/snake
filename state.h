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


game_state_t* creat_default_state();
void free_state(game_state_t *state);
void printf_board(game_state_t *state,FILE* fp);
void save_board(game_state_t *state,char* filename);
void update_state(game_state_t *state, int (*add_food)(game_state_t *state));
game_state_t *load_board(char *filename);
game_state_t *initialize_snakes(game_state_t *state);



#endif
