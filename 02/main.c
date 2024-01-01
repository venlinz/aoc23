#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "/Users/venkat-20297/code/clib/strings.h"

char * lines(char **string);
void chop_by_delim(char **string, char *delim);
char * get_input(const char *filepath);
char ** tokenize_by_delim(char **string, char *delim, char **tokens);

bool check_is_game_possible(char *line);
bool validate_color_count(char *color, char *count_str);


#define MAX_RED_CUBES 12
#define MAX_GREEN_CUBES 13
#define MAX_BLUE_CUBES 14 


int part1(char *input);
int part2(char *input);

#define MAX_FILE_SIZE (24 * 1024)
char input[MAX_FILE_SIZE] = {0};

int main(void) {
    const char *filepath = "./input.txt";
    char *input = get_input(filepath);
    if (input == NULL)
    {
        return 1;
    }
    int sum1 = part1(input);
    printf("part1: total sum: %i\n", sum1);
    // int sum2 = part2(input);
    // printf("part2: total sum: %i\n", sum2);
    return 0;
}

int part1(char *input) {
    int sumation_of_possible_game_nos = 0;
    char *line = NULL;
    int game_number = 1;
    while ((line = lines(&input)) != NULL) {
        bool is_possible = check_is_game_possible(line);
        if (is_possible) {
            sumation_of_possible_game_nos += game_number;
        }
        game_number++;
    }
    return sumation_of_possible_game_nos;
}

// int part2(char *input) {
//     return 0;
// }

char * get_input(const char *filepath) {
    FILE *f = fopen(filepath, "r");
    if (f == NULL) {
        perror("ERROR");
        return NULL;
    }
    int ret = fseek(f, 0, SEEK_END);
    assert(ret == 0 && "fseek failed");
    size_t filesize = ftell(f);
    assert(filesize <= MAX_FILE_SIZE);
    rewind(f);
    ret = fread(input, filesize, 1, f);
    // assert(ret == 1);
    if (!feof(f) && ferror(f)) {
        perror("ERROR: ");
        return NULL;
    }
    fclose(f);
    return input;
}

bool check_is_game_possible(char *line) {
    // printf("%s\n", line);
    chop_by_delim(&line, ":");
    char *games[16] = {0};
    tokenize_by_delim(&line, ";", (char **) games);
    bool is_game_possible = true;
    for (int i = 0; games[i] != NULL; ++i) {
        // printf("  cube set: %s\n", games[i]);
        char *cubes[6] = {0};
        tokenize_by_delim(&games[i], ",", (char **) cubes);
        for (int i = 0; cubes[i] != NULL; ++i) {
            cubes[i] = trim(&cubes[i]);
            // printf("    cube: %s\n", cubes[i]);
            char *tuple[2] = {0};
            tokenize_by_delim(&cubes[i], " ", (char **)tuple);
            char *cube_count = tuple[0];
            char *cube_color = tuple[1];
            // printf("      cube color: %s, cube count: %s\n", cube_color, cube_count);
            bool is_valid = validate_color_count(cube_color, cube_count);
            is_game_possible &= is_valid;
        }
    }
    return is_game_possible;
}

bool validate_color_count(char *color, char *count_str) {
    long count = strtol(count_str, NULL, 10);
    if (strncmp(color,  "red", 3) == 0) {
        return MAX_RED_CUBES >= count;
    }
    if (strncmp(color,  "blue", 4) == 0) {
        return MAX_BLUE_CUBES >= count;
    }
    if (strncmp(color,  "green", 5) == 0) {
        return MAX_GREEN_CUBES >= count;
    }
    return false;
}

char * lines(char **string) {
    char *line = strsep(string, "\n");
    if (line != NULL && line[0] == '\n') {
        return NULL;
    } else if (strlen(line) == 0) {
        return NULL;
    }
    return line;
}

void chop_by_delim(char **string, char *delim) {
    strsep(string, delim);
}

char ** tokenize_by_delim(char **string, char *delim, char **tokens) {
    char *token = NULL;
    for (size_t i = 0; (token = strsep(string, delim)) != NULL; ++i) {
        tokens[i] = token;
    }
    return tokens;
}
