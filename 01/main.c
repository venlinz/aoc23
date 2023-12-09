#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

char * get_input(const char *filepath);
bool is_digit(char c);
int part1(char *input);
int part2(char *input);
int is_word_digit(char *input);
int get_second_number_for_part2(char *input);
// int combine_numbers(int first_num, int second_num);

#define MAX_FILE_SIZE (24 * 1024)
char input[MAX_FILE_SIZE] = {0};


typedef struct {
    char *number;
    int len;
} NUMBER;

#define NUMBERS_LEN 9
NUMBER NUMBERS[NUMBERS_LEN] = 
{
    { .number = "one", .len = 3, },
    { .number = "two", .len = 3, },
    { .number = "three", .len = 5, },
    { .number = "four", .len = 4, },
    { .number = "five", .len = 4, },
    { .number = "six", .len = 3, },
    { .number = "seven", .len = 5, },
    { .number = "eight", .len = 5, },
    { .number = "nine", .len = 4}
};


int main(void) {
    const char *filepath = "./input.txt";
    char *input = get_input(filepath);
    if (input == NULL)
    {
        return 1;
    }
    int sum = part1(input);
    printf("part1: total sum: %i\n", sum);
    sum = part2(input);
    printf("part2: total sum: %i\n", sum);
    return 0;
}

int part2(char *input) {
    int sum = 0;
    int first_num = 0;
    int second_num = 0;
    int line_count = 0;
    for (int i = 0; input[i] != '\0'; ++i) {
        if (first_num == 0 && (is_digit(input[i]))) {
            first_num = input[i] - '0';
            second_num = first_num;
        }
        if (first_num == 0) {
            first_num = is_word_digit(input + i);
            second_num = first_num;
        }

        if (first_num == 0) {
            continue;
        }

        int second_word_num = get_second_number_for_part2(input + i);
        if (second_word_num) {
            second_num = second_word_num;
        }
        i++;
        while (input[i] != '\0' && input[i] != '\n') i++;
        // printf("ln: %i, fd: %i, sd: %i\n", line_count, first_num, second_num);
        int two_digit_num = first_num * 10 + second_num;
        sum += two_digit_num;
        first_num = 0;
        second_num = 0;
        line_count++;
    }
    return sum;
}

int part1(char *input) {
    int sum = 0;
    int first_num = 0;
    int second_num = 0;
    for (int i = 0; input[i] != '\0'; ++i) {
        if (first_num == 0 && is_digit(input[i])) {
            first_num = input[i] - '0';
            second_num = first_num;
            continue;
        }
        if (is_digit(input[i])) {
            second_num = input[i] - '0';
        }
        if (input[i] == '\n') {
            int two_digit_num = first_num * 10 + second_num;
            sum += two_digit_num;
            first_num = 0;
            second_num = 0;
        }
    }
    return sum;
}

char * get_input(const char *filepath) {
    FILE *f = fopen(filepath, "r");
    if (f == NULL) {
        perror("ERROR");
        return NULL;
    }
    int ret = fseek(f, 0, SEEK_END);
    assert(ret == 0 && "fseek failed");
    size_t filesize = ftell(f);
    printf("filesize of %s: %zu\n", filepath, filesize);
    assert(filesize <= MAX_FILE_SIZE);
    rewind(f);
    ret = fread(input, filesize, 1, f);
    printf("fread returnvalue: %d\n", ret);
    // assert(ret == 1);
    if (!feof(f) && ferror(f)) {
        perror("ERROR: ");
        return NULL;
    }
    fclose(f);
    return input;
}

bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

int is_word_digit(char *input) {
    for (int i = 0; i < NUMBERS_LEN; ++i) {
        if (strncmp(NUMBERS[i].number, input, NUMBERS[i].len) == 0) {
            // printf("number: %s, input: %s\n", NUMBERS[i].number, input);
            return i + 1;
        }
    }
    return 0;
}

int get_second_number_for_part2(char *input) {
    char line[256] = {0};
    int line_len = 0;
    for (int i = 0; *input != '\0' && *input != '\n'; ++i) {
        line[i] = *input++;
        line_len++;
    }
    while (line_len > 3) {
        char last_char = line[line_len - 1];
        if (is_digit(last_char)) {
            return last_char - '0';
        }
        for (int i = 0; i < NUMBERS_LEN; ++i) {
            if (line_len < NUMBERS[i].len) {
                continue;
            }
            char *word_from_last = (char *) line + line_len - NUMBERS[i].len;
            if (strncmp(word_from_last, NUMBERS[i].number, NUMBERS[i].len) == 0) {
                return i + 1;
            }
        }
        line_len--;
    }
    return 0;
}
