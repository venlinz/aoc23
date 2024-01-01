#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "/Users/venkat-20297/code/clib/strings.h"

char * get_input(const char *filepath);
bool check_is_game_possible(char *line, int len);
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
    int sum = 0;
    char line[256] = {0};
    int k = 0;
    int line_count = 1;
    for (int i = 0; input[i] != '\0'; ++i) {
        if (input[i] == '\n') {
            line[k] = '\0';
            bool is_possible = check_is_game_possible(line, k);
            if (is_possible)
                sum += line_count;
            k = 0;
            line_count++;
            continue;
        }
        line[k] = input[i];
        k++;
    }
    return sum;
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

bool check_is_game_possible(char *line, int len) {
    char sets_of_cubes[10][256] = {0};
    int set_count = 0;
    int k = 0;
    for (int i = 0; i < len; i++) {
        if (line[i] == ':') {
            i += 2;
            k = 0;
        }
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
    printf("linE: %s, ret: %i\n", line, is_valid);
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
