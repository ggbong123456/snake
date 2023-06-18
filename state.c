#include "state.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_ROW (10)
#define BOARD_COL (10)

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
  
  
