#include "state.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_ROW (10)
#define BOARD_COL (14)

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
void free_state(game_state_t *state){
if(state){
 free(state->snakes);
 for(int i=0;i<state->x_size;i++){
  if(state->board[i]){
   free(board[i]);
  }
 }
 if(state->board){
  free(state->board);
 }
 free(state);
}
}

void printf_board(game_state_t *state,FILE* fp){
 for(int i=0;i<state->x_size;i++){
  for(int j=0;j<state->y_size;j++){
     fprintf(fp,"%c",state[i][j]);
  }
  fprintf(fp,"\n");
 }
}

void save_board(game_state_t *state,char* filename){
 FILE* fp=fopen(filename,'w');
 printf_board(state,fp);
 fclose(fp);
}

static bool is_tail(char c){
 if(c=='w'||c=='s'||c=='a'||c=='d'){
    return true;
 }
else{
    return false;
}
}

static bool is_snake(char c){
 if(is_tail(c)||c=='^'||c=='v'||c=='>'||c=='<'||c=='x'){
     return true;
 }
else{
    return false;
}
}

static char body_to_tail(char c){
 if(x=='^'){
    return 'w';
 }
  else if(x=='v'){
    return 's';
 }
  else if(x=='<'){
    return 'a';
 }
  else if(x=='>'){
    return 'd';
 }
  else{
    return '?';
 }
}

static int incr_x(char c){
 if(c=='>'||c=='d')return 1;
 if(c=='<'||c=='a')return -1;
  return 0;
}

static int incr_y(char c){
 if(c=='^'||c=='w')return -1;
 if(c=='v'||c=='s')return 1;
  return 0;
}

static char next_square(game_state_t* state,int snum){
 if(snum<0||snum>=state->num_snakes){
    printf("snake id incorrect");
    return '?';
 }
 if(!state->snakes[snum].live){
    printf("snake has dead");
    return "?';
 }
 char head_dir=get_board_at(state,state->snakes[snum].head_x,state->snakes[snum].head_y);
 if(incr_x(head_dir)){
  return get_board_at(state,state->snakes[snum].head_x+incr_x(head_dir),state->snakes[snum].head_y);
 }
 if(incr_y(head_dir)){
  return get_board_at(state,state->snakes[snum].head_x,state->snakes[snum].head_y+incr_y(head_dir));
 }
 return '?';
}

static void update_head(game_state_t *state, int snum) {
 if(snum<0||snum>=state->num_snakes){
    printf("snake id incorrect");
 }
 if(!state->snakes[snum].live){
    printf("snake has dead");
 }
 char head_dir=get_board_at(state,state->snakes[snum].head_x,state->snakes[snum].head_y);
 if(incr_x(head_dir)){
  set_board_at(state,state->snakes[snum].head_x+incr_x(head_dir),state->snakes[snum].head_y,head_dir);
  state->snakes[snum].head_x+=incr_x(head_dir);
 }
 if(incr_y(head_dir)){
  set_board_at(state,state->snakes[snum].head_x,state->snakes[snum].head_y+incr_y(head_dir),head_dir);
  state->snakes[snum].head_y+=incr_y(head_dir);
 }
}

static void update_tail(game_state_t *state, int snum) {
  if(snum<0||snum>=state->num_snakes){
    printf("snake id incorrect");
 }
 if(!state->snakes[snum].live){
    printf("snake has dead");
 }
char tail_dir=get_board_at(state,state->snakes[snum].tail_x,state->snakes[snum].tail_y);
set_board_at(state,state->snakes[snum].tail_x,state->snakes[snum].tail_y,' '); 
 if(incr_x(tail_dir)){
  set_board_at(state,state->snakes[snum].tail_x+incr_x(tail_dir),state->snakes[snum].tail_y,body_to_tail(get_board_at(state,state->snakes[snum].tail_x+incr_x(tail_dir),state->snakes[snum].tail_y)));
  state->snakes[snum].tail_x+=incr_x(tail_dir);
 }
 if(incr_y(tail_dir)){
  set_board_at(state,state->snakes[snum].tail_x,state->snakes[snum].tail_y+incr_y(tail_dir),body_to_tail(get_board_at(state,state->snakes[snum].tail_x,state->snakes[snum].tail_y+incr_y(tail_dir))));
  state->snakes[snum].tail_y+=incr_y(tail_dir);
 }
}
  
void update_state(game_state_t *state, int (*add_food)(game_state_t *state)) {
 if (state->num_snakes==0) {
     return;
    }
 for(int i=0;i<state->num_snakes;i++){
     if (!state->snakes[i].live) {
         continue;
        }
    char next=next_square(state,i);
    if(is_snake(next)||next=='#'){
        set_board_at(state,state->snakes[i].head_x,state->snakes[i].head_y,'x');
        state->snakes[i].live=false;
    }
    else if(next=='*'){
        update_head(state,i);
        add_food(state);
    }
    else{
        update_head(state,i); 
        update_tail(state,i);
    }
 }
game_state_t *load_board(char *filename) {
 int row,col;
 char ch;
 FILE* f=fopen(filename,'r');
 for(row=0;;row++){
    if((ch=fgetc(f))==EOF)break;
    for(col=0;;ch=fgetc(f),col++){
        if(ch=='\n'){
            break;
        }
        else{
            continue;
        }
    }
 }
fclose(f);
f=NULL;
ch='\0';
game_state_t *state = (game_state_t *)malloc(sizeof(game_state_t));
state->x_size=row;
state->y_size=col;
state->board = (char **)malloc(sizeof(char *) * row);
    for (int i = 0; i < row; ++i) {
        state->board[i] = (char *)malloc(sizeof(char) * col);
    }
cow=col=0;
FILE* fp=fopen(filename,'r');
 for(row=0;;row++){
    if((ch=fgetc(fp))==EOF)break;
    for(col=0;;ch=fgetc(fp),col++){
        if(ch=='\n'){
            break;
        }
        else{
            state->board[row][col]=ch;
        }
    }
fclose(fp);
return state;
 }
 }

static void find_head(game_state_t *state, int snum) {
  int x=state->snakes[snum].tail_x;
  int y=state->snakes[snum].tail_y;
  int prev_x,prev_y;
  char curr_body;
  while(true){
   curr_body=get_board_at(state,x,y);
    if(!is_snake(curr_body))break;
   prev_x=x;
   prev_y=y;
   int dx = incr_x(curr_body);
   int dy = incr_y(curr_body);
   if(dx){
       x+=dx;
   }
   if(dy){
       y+=dy;
   }
 }
state->snakes[snum].head_x=prev_x;
state->snakes[snum].head_y=prev_y;
}

game_state_t *initialize_snakes(game_state_t *state) {
 state->num_snakes=0;
 state->snakes = (snake_t *)malloc(sizeof(snake_t));
 for(int i=0;i<state->x_size;i++){
    for(int j=0;j<state->y_size,j++){
        char tail_type=get_board_at(state,i,j);
        if(is_tail(tail_type)){
            state->num_snakes++;
            state->snakes = (snake_t *)realloc(sizeof(snake_t)*state->num_snakes);
            state->snakes[state->num_snakes-1].tail_x=row;
            state->snakes[state->num_snakes-1].tail_y=col;
            state->snakes[state->num_snakes-1].live=true;
            find_head(state,num_snakes-1);
        }
    }
 }
 return state;
}
