#include "state.h"
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]) {
    char *in_filename = NULL;
    char *out_filename = NULL;
    game_state_t *state = NULL;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0 && i < argc - 1) {
            in_filename = argv[i + 1];
            i++;
            continue;
        }
        if (strcmp(argv[i], "-o") == 0 && i < argc - 1) {
            out_filename = argv[i + 1];
            i++;
            continue;
        }
        fprintf(stderr, "Usage: %s [-i filename] [-o filename]\n", argv[0]);
        return 1;
    }
    if (in_filename != NULL) {
        state = load_board(in_filename);
        initialize_snakes(state);
    } else {
        state = create_default_state(); 
    }
    update_state(state, deterministic_food);
    if (out_filename != NULL) {
        save_board(state, out_filename);
    } else {
        print_board(state, stdout);
    }
    free_state(state);
    return 0;
}
