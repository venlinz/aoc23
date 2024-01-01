#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <strings.h>

typedef struct {
    char *color;
    int count;
    int color_code;
} CubeSet;

bool check_is_game_possible(char *line);
bool validate_color_count(CubeSet cube);
int get_power_of_minimum_cubes(char *line);
CubeSet get_color(char *cube_str);

#define MAX_RED_CUBES 12
#define MAX_GREEN_CUBES 13
#define MAX_BLUE_CUBES 14 

#define COLOR_RED "red"
#define COLOR_GREEN "green"
#define COLOR_BLUE "blue"

#define COLOR_CODE_RED 1
#define COLOR_CODE_GREEN 2
#define COLOR_CODE_BLUE 3

int part1(char *input);
int part2(char *input);

int main(void) {
    const char *filepath = "./input.txt";
    char *input = read_file_as_string(filepath);
    if (input == NULL)
    {
        return 1;
    }
    char *input_copy = strdup(input);
    int sum1 = part1(input);
    printf("part1: total sum: %i\n", sum1);
    int sum2 = part2(input_copy);
    free(input);
    free(input_copy);
    printf("part2: total sum: %i\n", sum2);
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

int part2(char *input) {
    char *line = NULL;
    int sum_of_power_of_minimum_cubes = 0;
    while ((line = lines(&input)) != NULL) {
        int power_of_minimum_cubes = get_power_of_minimum_cubes(line);
        sum_of_power_of_minimum_cubes += power_of_minimum_cubes;
    }
    return sum_of_power_of_minimum_cubes;
}


bool check_is_game_possible(char *line) {
    chop_by_delim(&line, ":");
    char *games[16] = {0};
    tokenize_by_delims(&line, ";", (char **) games);
    bool is_game_possible = true;
    for (int i = 0; games[i] != NULL; ++i) {
        char *cubes[6] = {0};
        tokenize_by_delims(&games[i], ",", (char **) cubes);
        for (int i = 0; cubes[i] != NULL; ++i) {
            CubeSet single_cube_set = get_color(trim(&cubes[i]));
            bool is_valid = validate_color_count(single_cube_set);
            is_game_possible &= is_valid;
        }
    }
    return is_game_possible;
}

CubeSet get_color(char *cube_str) {
    char *tuple[2] = {0};
    tokenize_by_delims(&cube_str, " ", tuple);
    long count = strtol(tuple[0], NULL, 10);

    int color_code = 0;
    if (strncmp(tuple[1], COLOR_RED, sizeof(COLOR_RED)) == 0) {
        color_code = COLOR_CODE_RED;
    } else if (strncmp(tuple[1], COLOR_BLUE, sizeof(COLOR_BLUE)) == 0) {
        color_code = COLOR_CODE_BLUE;
    } else if (strncmp(tuple[1], COLOR_GREEN, sizeof(COLOR_GREEN)) == 0) {
        color_code = COLOR_CODE_GREEN;
    } else { assert(false && "Unreachable"); }

    CubeSet cubes = {.color = tuple[1], .count = count, .color_code = color_code};
    return cubes;
}

int get_power_of_minimum_cubes(char *line) {
    int min_red_cubes = 0;
    int min_blue_cubes = 0;
    int min_green_cubes = 0;
    chop_by_delim(&line, ":");
    char *multiple_cubesets[32] = {0};
    tokenize_by_delims(&line, ",;", multiple_cubesets);
    for (int i = 0; multiple_cubesets[i] != NULL; ++i) {
        CubeSet single_cube_set = get_color(trim(&multiple_cubesets[i]));
        int color_code = single_cube_set.color_code;
        int cubes_count = single_cube_set.count;
        if (color_code == COLOR_CODE_RED && min_red_cubes <= cubes_count) {
            min_red_cubes = cubes_count;
        } else if (color_code == COLOR_CODE_BLUE && min_blue_cubes <= cubes_count) {
            min_blue_cubes = cubes_count;
        } else if (color_code == COLOR_CODE_GREEN && min_green_cubes <= cubes_count) {
            min_green_cubes = cubes_count;
        }
    }
    return min_blue_cubes * min_red_cubes * min_green_cubes;
}

bool validate_color_count(CubeSet cubes) {
    int color_code = cubes.color_code;
    int count = cubes.count;
    if (color_code == COLOR_CODE_RED) {
        return MAX_RED_CUBES >= count;
    } else if (color_code == COLOR_CODE_BLUE) {
        return MAX_BLUE_CUBES >= count;
    } else if (color_code == COLOR_CODE_GREEN) {
        return MAX_GREEN_CUBES >= count;
    }
    return false;
}
