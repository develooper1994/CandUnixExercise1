/*
AUTHOR: Mustafa Selçuk Çağlar
mycat [-t(text)|-x(hex)|-o(octal)] [-c or --bytes < number >, default: 10] [-n or --lines < number >, default: 10] [-d or --order < ascending ==1 | descending order !=1 >, default: ascending] [files]

Seçenekler:
[argümansız]
-t (text) (default) (thick)
-o (octal) (thick)
-x (hex) (thick)
-h or --help (thick)
-v or --verbose (thick)
[argümanlı]
-c or --bytes, default: 10 (thick)
-n or --lines, default: 10 (thick)
-d or --order < ascending ==0 (thick) | descending order !=0 (TODO: working on it) >, default: ascending

Burada -t "text olarak yazdır",
-o "ocatal olarak yazdır,
-x "hex olarak yazdır anlamına gelmektedir. Bu seçeneklerden yalnızca bir tanesi belirtilebilir ve bu seçeneklerden hiçbiri belirtilmemişse -t seçeneği belirtilmiş gibi işlem yapılmalıdır.
--bytes isteğe bağlı (optional) argüman alabilen uzun bir seçenektir. Dosyanın başındaki ilk n satırı yazdırır. Bu uzun seçeneğin default değeri 10'dur. --verbose seçeneği birden fazla dosyanın yazdırıldığı durumda dosya isimlerinin de basılmasını sağlamaktadır. Programın örnek bir gerçekleştirim şöyle olabilir:
*/

#define VERSION_MAJOR "1"
#define VERSION_MINOR "0"
#define VERSION_PATCH "0"
#define VERSION VERSION_MAJOR "." VERSION_MINOR "." VERSION_PATCH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "doublevector.h"

// symbolic constants
#define DEFAULT_LINE          10
#define DEFAULT_BYTE_LENGHT   10
#define HEX_OCTAL_LINE_LENGHT 16

// order
#define ASCENDING_ORDER       1 // ascending order ==0
#define DESCENDING_ORDER      0 // descending order !=0
#define DEFAULT_ORDER         ASCENDING_ORDER

// enumurate
#define DEFAULT_ENUMERATE     1 // enumurate ==0

#define PRINT_OCTAL           0
#define PRINT_HEX             1
#define PRINT_TEXT            2
#define DEFAULT_PRINT         PRINT_TEXT

#define DELIM   '\n'

// function prototypes
void print_help();
long filesize(FILE* fp);
// ascending order
int print_text(FILE *fp, const long n, int ch);
int print_hex_octal(FILE* fp, const long n, int ch, int hexflag);
// descending order
int print_text_last(FILE* fp, const long n, int ch);
//int print_hex_octal_last(FILE* f, const long n, int ch, int hexflag);

int main(int argc, char *argv[]){
    // ----------------------------- <print like linux head command> -----------------------------------
    // create options, flags and arguments and other variables
    int result=0;
    int err_flag=0, t_flag=0, o_flag=0, x_flag=0, verbose_flag=0,
          bytes_flag=0,    lines_flag=0,    order_flag=0;
    char *bytes_arg=NULL, *lines_arg=NULL, *order_arg=NULL;

    struct option long_options[] = {
        // optional_argument
        {"bytes", optional_argument, NULL, 'c'},
        {"lines", optional_argument, NULL, 'n'},
        {"order", optional_argument, NULL, 'd'},
        // no_argument
        {"enumurate", no_argument, NULL, 'e'},
        {"verbose", no_argument, NULL, 'v'},
        {"version", no_argument, NULL, 'V'},
        {"help", no_argument, NULL, 'h'},
        {0,0,0,0}
    };
    char options[] = "xotvVhc:n:d:";
    FILE* fp;
    char* filename;
    int index=0;
    long nbyte=DEFAULT_BYTE_LENGHT, nline=DEFAULT_LINE, order=DEFAULT_ORDER;

    opterr=0;
    // parse command line arguments
    do{
        result = getopt_long(argc, argv, options, long_options, NULL);
        switch(result){
            // no_argument
            case 'x':
                x_flag = 1;
                break;
            case 'o':
                o_flag = 1;
                break;
            case 't': // default
                t_flag = 1;
                break;
            case 'v':
                verbose_flag = 1;
                break;
            case 'V':
                printf("%s\n", VERSION);
                exit(EXIT_SUCCESS);
                break;
            case 'h':
                print_help();
                exit(EXIT_SUCCESS);
            // optional_argument
            case 'c':
                bytes_flag = 1;
                bytes_arg = optarg;
                break;
            case 'n':
                lines_flag = 1;
                lines_arg = optarg;
                break;
            case 'd':
                order_flag = 1;
                order_arg = optarg;
                break;
            case '?':
                // parsing error check
                if(optopt != 0)
                    fprintf(stderr, "invalid switch -%c\n", optopt);
                else if(optopt == 'c') // --bytes
                    fprintf(stderr, "-c or --bytes option without argument\n");
                else if(optopt == 'n') // --lines
                    fprintf(stderr, "-n or --lines option without argument\n");
                else if(optopt == 'd') // --order
                    fprintf(stderr, "-d or --order option without argument\n");
                else
                    fprintf(stderr, "invalid switch --%s\n", argv[optopt - 1]); // not a portable way to check
                err_flag = 1;
                break;
            // note don't use default statement
        }
    }while(result != -1);

    // switch error check
    if(x_flag + o_flag + t_flag > 1){
        fprintf(stderr, "only one option must be specified from -o, -t, -x\n");
        err_flag = 1;
        //exit(EXIT_FAILURE);
    }
    if(bytes_flag + lines_flag > 1){
        fprintf(stderr, "only one option must be specified from -c, -n\n");
        err_flag = 1;
        //exit(EXIT_FAILURE);
    }
    if(optind == argc){
        // argc and optind only equal to 1 only if nothing specified
        fprintf(stderr, "At least one argument must be specified\n");
        print_help();
        err_flag = 1;
        //exit(EXIT_FAILURE);
    }

    // exit according to error check
    if(err_flag!= 0){ exit(EXIT_FAILURE); }

    // set defaults
    // default flags
    if(x_flag + o_flag + t_flag == 0){
        // non of them specified. default = text(t_flag)
        t_flag = 1;
    }
    if(bytes_flag + lines_flag == 0){
        // non of them specified. default = lines(lines_flag)
        lines_flag = 1;
    }
    //default values
    if(bytes_flag){
        nbyte = bytes_arg != NULL ?
        strtol(bytes_arg, NULL, 10) :
        DEFAULT_BYTE_LENGHT;
    }
    if(lines_flag){
        nline = lines_arg != NULL ?
        strtol(lines_arg, NULL, 10) :
        DEFAULT_LINE;
    }
    if(order_flag){
        order = order_arg != NULL ?
        strtol(order_arg, NULL, 10) :
        DEFAULT_ORDER;
    }

    // process according to flags
    for(index = optind; index < argc; ++index){
        // open files if file couldn't open continue to next file
        filename = argv[index];
        fp = fopen(filename, "rb");
        if(fp == NULL){
            fprintf(stderr, "Cannot open file %s\n", filename);
            continue;
        }
        // print filenames
        if(verbose_flag){
            printf("=====> %s <=====\n\n", filename);
        }

        // how do you want to print?
        int ch = lines_flag ? DELIM : 0; // line_flag
        long n  = lines_flag ? nline : nbyte;
        printf("ch: %d || n: %ld || order: %ld \n", ch, n, order);
        if (order == 1) {
            if(t_flag) // default
                result = print_text(fp, n, ch);
            else if(x_flag)
                result = print_hex_octal(fp, n, ch, PRINT_HEX);
            else if(o_flag)
                result = print_hex_octal(fp, n, ch, PRINT_OCTAL);
        }
        else {
            if(t_flag)
                result = print_text_last(fp, n, ch);
            /*
            else if(x_flag)
                result = print_hex_octal_last(fp, n, ch, PRINT_HEX);
            else if(o_flag)
                result = print_hex_octal_last(fp, n, ch, PRINT_OCTAL);
            */
        }

        if(index != argc -1)
            putchar('\n');
        // read error
        if(!result)
            fprintf(stderr, "cannot read the file %s\n", filename);

        fclose(fp);
    }

    exit(EXIT_SUCCESS);
}

void print_help(){
    fprintf(stdout, "Version: %s\nmycat [-t(text)|-x(hex)|-o(octal)] [-c or --bytes < number >, default: 10] [-n or --lines < number >, default: 10] [-d or --order < ascending ==1 | descending order !=1 >, default: ascending] [files]\n", VERSION);
}

long filesize(FILE* fp) {
    fseek(fp, 0, SEEK_END); // seek to end of file
    long size = ftell(fp); // get current file pointer
    fseek(fp, 0, SEEK_SET); // seek back to beginning of file
    return size;
}



// ----------------------------- <print like linux head command> -----------------------------------
// text
int print_text(FILE *fp, const long n, int ch){
    // n == -1 => print all file
    long byte_count = 0, line_count = 0;
    const long file_size = filesize(fp);
    rewind(fp);

    long read_until=n;
    //if(read_until<0) read_until = file_size + n + 1;

    if(read_until == -1){
        // print all file
        for(; (file_size - byte_count > 0); ++byte_count){
            ch = fgetc(fp);
            putchar(ch);
        }
    }
    else{
        if(ch == DELIM){
            // line_count < read_until
            for(; (read_until - line_count > 0) && (file_size - byte_count > 0); ++byte_count){
                if(ch == DELIM) ++line_count;
                ch = fgetc(fp);
                putchar(ch);
            }
        }
        else {
            // byte_count < read_until
            for(; (read_until - byte_count > 0) && (file_size - byte_count > 0); ++byte_count){
                ch = fgetc(fp);
                putchar(ch);
            }
        }
    }

    return !ferror(fp);
}

// hex - octal
int print_hex_octal(FILE* fp, const long n, int ch, int hexflag){
    // n == -1 => print all file
    int line_mod=0;
    long byte_count=0;
    const char *off_str, *ch_str;

    off_str = hexflag ? "%07X" : "%012o";
    ch_str = hexflag? "%02X%c" : "%03o%c";

    const long file_size = filesize(fp);
    rewind(fp);

    long read_until=n;
    //if(read_until<0) read_until = file_size + n + 1;

    if(read_until == -1){
        // print all file
        for(; byte_count < file_size; ++byte_count){
            ch = fgetc(fp);

            line_mod = byte_count % HEX_OCTAL_LINE_LENGHT;
            if(line_mod == 0)
                printf(off_str, byte_count);
            printf(ch_str, ch, line_mod == HEX_OCTAL_LINE_LENGHT - 1 ? '\n': ' ');
        }
    }
    else{
        int line_mod_count = 0;
        if(ch==DELIM){
            for(; (line_mod_count < read_until) && (line_mod_count < file_size); ++byte_count){
                ch = fgetc(fp);

                line_mod = byte_count % HEX_OCTAL_LINE_LENGHT;
                if(line_mod == 0)
                    printf(off_str, byte_count);
                printf(ch_str, ch, line_mod == HEX_OCTAL_LINE_LENGHT - 1 ? '\n': ' ');

                if(ch == DELIM) ++line_mod_count;
            }
        }
        else {
            // byte_count < read_until
            for(; (line_mod_count < read_until) && (byte_count < file_size); ++byte_count){
                ch = fgetc(fp);

                line_mod = byte_count % HEX_OCTAL_LINE_LENGHT;
                if(line_mod == 0)
                    printf(off_str, byte_count);
                printf(ch_str, ch, line_mod == HEX_OCTAL_LINE_LENGHT - 1 ? '\n': ' ');
            }
        }
    }

    line_mod = byte_count % HEX_OCTAL_LINE_LENGHT;
    if(line_mod != 0)
        putchar('\n');

    return !ferror(fp);
}
// ----------------------------- </print like linux head command> -----------------------------------
// ----------------------------- <print like linux tail command> -----------------------------------

int print_text_last(FILE* fp, const long n, int ch){
    // TODO: SEGFAULT!
    // n == -1 => print all file
    long byte_count=0, line_count=0;
    const long file_size = filesize(fp);
    fseek(fp, -1, SEEK_END); // read from end of file

    DoubleVector* container = CreateDoubleVector(DEFAULT_DATA_SIZE);

    long read_until=n;
    //if(read_until<0) read_until = file_size + n + 1;
    printf("ch: %d || n: %ld\n", ch, read_until); // debug

    if(n == -1){
        // print all file
        puts("<print all file>"); // debug
        for(; file_size - byte_count > 0; ++byte_count){
            ch = fgetc(fp);
            fseek(fp, -2, SEEK_CUR);
            //puts("<all AppendDoubleVector>"); // debug
            AppendDoubleVector(container, ch);
            //puts("</all AppendDoubleVector>"); // debug
        }
        PrintDoubleVectorReverse(container);
    }
    else {
        if (ch == DELIM) {
            // line_count < read_until
            for(; (read_until - line_count > 0) && (file_size - byte_count > 0); ++byte_count) {
                if (ch == DELIM) ++line_count;
                ch = fgetc(fp);
                fseek(fp, -2, SEEK_CUR);
                puts("<line AppendDoubleVector>"); // debug
                AppendDoubleVector(container, ch);
                puts("</line AppendDoubleVector>"); // debug
            }
            PrintDoubleVectorReverse(container);
        }
        else {
            // byte_count < read_until
            for(; (read_until - byte_count > 0) && (file_size - byte_count > 0); ++byte_count) {
                ch = fgetc(fp);
                fseek(fp, -2, SEEK_CUR);
                puts("<byte AppendDoubleVector>"); // debug
                AppendDoubleVector(container, ch);
                //puts("</byte AppendDoubleVector>"); // debug
            }
            PrintDoubleVectorReverse(container);
        }
    }

    DestroyDoubleVector(container);
    return !ferror(fp);
}


// ----------------------------- </print like linux tail command> -----------------------------------

// https://www.geeksforgeeks.org/print-last-10-lines-of-a-given-file/
/* Function to print last n lines of a given string */
void print_last_lines(char *str, int n){
    /* Base case */
    if (n <= 0)
       return;
 
    size_t cnt  = 0; // To store count of '\n' or DELIM
    char *target_pos   = NULL; // To store the output position in str
 
    /* Step 1: Find the last occurrence of DELIM or '\n' */
    target_pos = strrchr(str, DELIM);
 
    /* Error if '\n' is not present at all */
    if (target_pos == NULL){
        fprintf(stderr, "ERROR: string doesn't contain '\\n' character\n");
        return;
    }
 
    /* Step 2: Find the target position from where we need to print the string */
    while (cnt < n){
        // Step 2.a: Find the next instance of '\n'
        while (str < target_pos && *target_pos != DELIM)
            --target_pos;
 
         /* Step 2.b: skip '\n' and increment count of '\n' */
        if (*target_pos ==  DELIM)
            --target_pos, ++cnt;
 
        /* str < target_pos means str has less than 10 '\n' characters,
           so break from loop */
        else break;
    }
 
    /* In while loop, target_pos is decremented 2 times, that's why target_pos + 2 */
    if (str < target_pos)
        target_pos += 2;
 
    // Step 3: Print the string from target_pos
    printf("%s\n", target_pos);
}


// AUTHOR: Mustafa Selçuk Çağlar
