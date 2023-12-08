#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 14 * 1024

typedef struct {
    const char* str;
    int state;
    int num;
} NumberDFA;

static int transition(NumberDFA* dfa, char c) {
    if(dfa->str[dfa->state + 1] == c) {
        dfa->state += 1;
    } else if(dfa->str[0] == c) {
        dfa->state = 0;
    } else {
        dfa->state = -1;
    }
    
    if(dfa->str[dfa->state + 1] == '\0') {
        dfa->state = -1;
        return dfa->num;
    } else {
        return -1;
    }
}

static int transition_all(NumberDFA* dfas, int count, char c) {
    int num = -1;
    for(int i = 0; i < count; i++) {
        int res = transition(&dfas[i], c);
        if(res != -1) {
            num = res;
        }
    }
    return num;
}

static int to_num(char c) {
    return isdigit(c) ? c - 0x30 : -1;
}

static int compute_number(const char* line) {
    NumberDFA dfas[] = {
        {.str = "one",   .num=1, .state = -1},
        {.str = "two",   .num=2, .state = -1},
        {.str = "three", .num=3, .state = -1},
        {.str = "four",  .num=4, .state = -1},
        {.str = "five",  .num=5, .state = -1},
        {.str = "six",   .num=6, .state = -1},
        {.str = "seven", .num=7, .state = -1},
        {.str = "eight", .num=8, .state = -1},
        {.str = "nine",  .num=9, .state = -1},
    };

    int first = -1, last = -1;

    for(size_t i = 0; i < strlen(line); i++) {
        int dig = transition_all(dfas, sizeof(dfas)/sizeof(dfas[0]), line[i]);
        if (dig == -1) {
            dig = to_num(line[i]);
        }

        if(dig != -1) {
            if(first == -1) {
                first = last = dig;
            } else {
                last = dig;
            }
        }
    }

    return first * 10 + last;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s file.txt\n", argv[0]);
        exit(-1);
    }

    FILE* f = fopen(argv[1], "r");
    if (!f) {
        fprintf(stderr, "Couldn't open file %s: %s\n", argv[1], strerror(errno));
        exit(-1);
    }

    int sum = 0;
    char line[MAX_LINE];
    while(fgets(line, MAX_LINE, f)) {
        sum += compute_number(line);
    }

    printf("%d\n", sum);
    fclose(f);
}
