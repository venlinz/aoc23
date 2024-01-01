#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "/Users/venkat-20297/code/clib/strings.h"

char * lines(char **string);
void chop_by_delim(char **string, char *delim);
char * get_input(const char *filepath);

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
    char sets_of_cubes[10][256] = {0};
    int set_count = 0;
    int k = 0;
    chop_by_delim(&line, ":");
    size_t len = strlen(line);
    for (size_t i = 0; i < len; i++) {
        if (line[i] == ';') {
            set_count++;
            i++;
            k = 0;
        } else {
            sets_of_cubes[set_count][k] = line[i];
            k++;
        }
    }
    set_count++;
    bool is_possible = true;
    bool is_valid = false;
    for (int i = 0; i < set_count; ++i) {
        char *set = sets_of_cubes[i];
        char *token = 0;
        while ((token = strsep(&set, ",")) != NULL) {
            char *trimed_token = trim(&token);
            char *color = NULL;
            char *count_str = NULL;
            char *new_token = NULL;
            while ((new_token = strsep(&trimed_token, " ")) != NULL) {
                if (!count_str) {
                    count_str = new_token;
                } else {
                    color = new_token;
                }
            }
            if (color == NULL) {
                printf("color null line: %s\n", line);
            }
            assert(color != NULL);
            assert(count_str != NULL);
            is_valid = validate_color_count(color, count_str);
            is_possible &= is_valid;
        }
    }
    return is_possible;
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

char ** tokenize_by_delim(char **string, char *delim) {
    char **tokens = malloc(sizeof(char **) * 16);
    if (tokens == NULL) {
        fprintf(stderr, "Unable to allocate memory\n");
        return NULL;
    }
    char *token = NULL;
    size_t i = 0;
    while ((token = strsep(string, delim)) != NULL) {
        tokens[i] = token;
    }
    return tokens;
}
