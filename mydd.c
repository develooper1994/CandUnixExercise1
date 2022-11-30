#define _GNU_SOURCE
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

// syntatic constants
#define DEFINE_BLOCK_SIZE   512
#define MIN_BLOCK_SIZE      1
#define DEFINE_BLOCK_COUNT  0

// global constants

// function prototypes
int operand_matches (char const *, char const *, char);
int operand_is(const char*, const char*);

void print_usage();
void exit_sys(const char*, ...);

int main(int argc, char* argv[]){
    // error check
    if (argc<3) {
        exit_sys("not enough arguments\n");
    }
    if (!strncmp(argv[1], "help", 5)) {
        print_usage();
    }
    int bs_flag=0, c_flag=0;
    char* params[argc];
    size_t nparams = 0;

    static char* input_file = NULL;
    static char* output_file = NULL;
    long block_size = DEFINE_BLOCK_SIZE, block_count = DEFINE_BLOCK_COUNT;

    for (int idx = 1; idx < argc; ++idx) {
        const char* name = argv[idx];
        char* val = strchr(name, '=');
        if(val == NULL){
            exit_sys("unreconized operand %s\n", name);
        }
        val++;

        if(operand_is(name, "if")){
            input_file = val;
        }
        else if(operand_is(name, "of")){
            output_file = val;
        }
        else {
            if(operand_is(name, "bs")){
                block_size = strtol(val, NULL, 10);
            }
            else if(operand_is(name, "c")){
                block_count = strtol(val, NULL, 10);
            }
        }
    }
    if(block_size<0 || block_count<0)
        exit_sys("Please enter a positive value");

    // copy file
    int fd_in, fd_out;
    fd_in = open(input_file, O_RDONLY);
    if(fd_in<0)
        exit_sys("input file cannot open!\n");
    struct stat st;
    if(fstat(fd_in, &st)<0)
        exit_sys("fstat");
    off_t len = st.st_size;
    __mode_t perms = st.st_mode;

    fd_out = open(output_file, O_WRONLY|O_CREAT|O_TRUNC, perms);
    if(fd_out<0)
        exit_sys("output file cannot open!\n");

    ssize_t ret=0;
    size_t block_counter=0;
    do {
        ret = copy_file_range(fd_in, NULL,
                              fd_out, NULL,
                              block_size, 0);
        if (ret<0) {
            exit_sys("copy_file_range");
        }
        len-=ret;
        ++block_counter;
    } while (len>0 && ret >0 && block_counter<block_count);

    return EXIT_SUCCESS;
}

// function bodies

// https://github.com/coreutils/coreutils/blob/master/src/dd.c
// Return "not zero" if STR is of the form "PATTERN" or "PATTERNDELIM...".
int operand_matches (char const *str, char const *pattern, char delim){
    while (*pattern) {
        if(*str++ != *pattern++) {
            return 0;
        }
    }
    return !*str || *str == delim;
}
// OPERAND is of the form "X=...".  Return "not zero" if X is NAME.
int operand_is(const char* operand, const char* name){
    return operand_matches(operand, name, '=');
}

void print_usage(){
    printf("mydd if=<source> of=<destination> bs=<block size>[default:%d] c=<block count>[default:%d]", DEFINE_BLOCK_SIZE, DEFINE_BLOCK_COUNT);
}

void exit_sys(const char* msg , ...){
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
    //perror(msg);
    print_usage();
    exit(EXIT_FAILURE);
}