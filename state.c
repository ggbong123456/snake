#include "state.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_ROW (10)
#define BOARD_COL (10)

static char get_board_at(game_state_t* state,int x,int y){
 return state->board[x][y]; 
}

static void set_board_at(game_state_t* state,int x,int y,char ch){
 state->board[x][y]=ch; 
}
game_state_t* creat_default_state(){
  game_state_t* default_state=(game_state_t*)malloc(sizeof(game_state_t));
  default_state->x_size=BOARD_ROW;
  default_state->y_size=BOARD_COL;
  default_state->board=(char**)malloc(sizeof(char*)*BOARD_ROW );
  for(int i=0;i<BOARD_ROW;i++){
    default_state->board[i]=(char*)malloc(sizeof(char)*BOARD_COL);
    if(i==0||i==BOARD_ROW-1){
      memset(default_state->board[i],'#',sizeof(char)*BOARD_COL);
    }
    else{
      memset(default_state->board[i],' ',sizeof(char)*BOARD_COL);
      memset(default_state->board[i],'#',sizeof(char));
      memset(default_state->board[i]+BOARD_COL-1,'#',sizeof(char));
    }
  }
  set_board_at(game_state_t* state,2,9,'*');
  default_state->num_snakes=1;
  default_state->snakes=(snake_t*)malloc(sizeof(snake_t));
  default_state->snakes->tail_x=4;
  default_state->snakes->tail_y=4;
  default_state->snakes->head_x=4;
  default_state->snakes->head_y=4;
  default_state->snakes->live = true;
  set_board_at(game_state_t* state,default_state->snakes->tail_x,default_state->snakes->tail_y,'d');
  set_board_at(game_state_t* state,default_state->snakes->head_x,default_state->snakes->head_y,'>');
  return default_state;
  
}
  
  
  
