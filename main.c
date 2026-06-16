#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monopoly.h"

int load_properties(const char *filename, PROPERTY *props) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) return -1;

    int count = 0;
    COLOR color = Brown;
    char line[1024]; // zvacseny buffer

    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\r\n")] = '\0';

        if (line[0] == '\0') continue;

        if (line[0] == '[') {
            for (int i = 0; i < NUM_COLORS; i++) {
                if (strncmp(line + 1, property_colors[i], strlen(property_colors[i])) == 0) {
                    color = (COLOR)i;
                    break;
                }
            }
        } else {
            char *start = strchr(line, '"');
            char *end = strrchr(line, '"');
            char *colon = strrchr(line, ':');

            if (start && end && colon && start != end) {
                int len = end - start - 1;
                strncpy(props[count].name, start + 1, len);
                props[count].name[len] = '\0';
                props[count].price = atoi(colon + 1);
                props[count].color = color;
                count++;
            }
        }
    }

    fclose(f);
    return count;
}

int load_board(const char *filename, SPACE *board, PROPERTY *props, int num_props) {
    FILE *f = fopen(filename, "r");
    if (!f) return -1;

    char line[1024];
    fgets(line, sizeof(line), f);
    int num_spaces = atoi(line);

    int prop_idx = 0;
    for (int i = 0; i < num_spaces; i++) {
        fgets(line, sizeof(line), f);
        line[strcspn(line, "\r\n")] = '\0';

        board[i].property = NULL;
        for (int t = 0; t < NUM_SPACE_TYPES; t++) {
            if (strcmp(line, space_types[t]) == 0) {
                board[i].type = (SPACE_TYPE)t;
                break;
            }
        }

        if (board[i].type == Property) {
            if (prop_idx >= num_props) { fclose(f); return -2; }
            board[i].property = &props[prop_idx++];
        }
    }

    fclose(f);
    return num_spaces;
}

int main(int argc, char *argv[]) {
    const char *t_file = NULL, *b_file = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0) t_file = argv[++i];
        else if (strcmp(argv[i], "-b") == 0) b_file = argv[++i];
    }

    PROPERTY props[NUM_PROPERTIES * 2];
    int num_props = NUM_PROPERTIES;
    PROPERTY *active = properties;

    if (t_file) {
        int r = load_properties(t_file, props);
        if (r == -1) { printf("E1\n"); return 0; }
        num_props = r;
        active = props;
    }

    if (b_file) {
        SPACE board[NUM_SPACES * 4];
        int r = load_board(b_file, board, active, num_props);
        if (r == -1) { printf("E1\n"); return 0; }
        if (r == -2) { printf("E2\n"); return 0; }

        for (int i = 0; i < r; i++) {
            if (board[i].type == Property) {
                PROPERTY *p = board[i].property;
                printf("%d.  %s  %d  %s\n", i+1, p->name, p->price, property_colors[p->color]);
            } else {
                printf("%d.  %s\n", i+1, space_types[board[i].type]);
            }
        }
    } else if (t_file) {
        for (int i = 0; i < num_props; i++)
            printf("%s  %d  %s\n", active[i].name, active[i].price, property_colors[active[i].color]);
    }

    return 0;
}