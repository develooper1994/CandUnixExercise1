/*
mycat [-t(text)|-x(hex)|-o(octal)] [-n or --top < number >, default: 10] [-d or --order < ascending >=0 | descending order <0 >, default: ascending] [-e or --enumurate < enumurate >=0 | not enumurate <0 >, default: not enumurate] [files]

Seçenekler:

[argümansız]
-t (text) (default)
-o (octal)
-x (hex)

-v or --verbose

[argümanlı]
-n or --top, default n = 10
-d or --order < ascending >=0 | descending order <0 >, default order = ascending
-e or --enumurate < enumurate >=0 | not enumurate <0 >, default: not enumurate

Burada -t "text olarak yazdır", 
-o "ocatal olarak yazdır, 
-x "hex olarak yazdır anlamına gelmektedir. Bu seçeneklerden yalnızca bir tanesi belirtilebilir ve bu seçeneklerden hiçbiri belirtilmemişse -t seçeneği belirtilmiş gibi işlem yapılmalıdır.

--top isteğe bağlı (optional) argüman alabilen uzun bir seçenektir. Dosyanın başındaki ilk n satırı yazdırır. Bu uzun seçeneğin default değeri 10'dur. --verbose seçeneği birden fazla dosyanın yazdırıldığı durumda dosya isimlerinin de basılmasını sağlamaktadır. Programın örnek bir gerçekleştirim şöyle olabilir:

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

// symbolic constants
#define DEFAULT_LINE          10
#define HEX_OCTAL_LINE_LENGHT 16

// order
#define ASCENDING_ORDER       0 // ascending order >=0
#define DESCENDING_ORDER      -1 // descending order <0
#define DEFAULT_ORDER         ASCENDING_ORDER

// enumurate
#define ENUMERATE             1 // enumurate >=0

#define PRINT_OCTAL           0
#define PRINT_HEX             1

// function prototypes
int print_text(FILE *f, const int nline);
int print_hex_octal(FILE* f, const int nline, int hexflag);

int print_text_last(FILE *fp, const int nline);
int print_hex_octal_last(FILE* f, const int nline, int hexflag);

int main(int argc, char *argv[])
{
    // create options, flags and arguments and other variables
    int result=0, err_flag=0;
    int t_flag=0, o_flag=0, x_flag=0, top_flag=0, order_flag=0, enumurate_flag=0, verbose_flag=0, help_flag=0;
    char *top_arg, *order_arg, *enumurate_arg;

    struct option long_options[] = {
        {"top", optional_argument, NULL, 'n'},
        {"order", optional_argument, NULL, 'd'},
        {"enumurate", optional_argument, NULL, 'e'},
        {"verbose", no_argument, NULL, 'v'},
        {"help", no_argument, NULL, 'h'},
        {0,0,0,0}
    };
    char options[] = "xotvhn:d:e:";
    FILE* fp;
    int index=0;
    int nline=-1, order=DEFAULT_ORDER;

    opterr=0;
    // parse command line arguments    
    do{
        result = getopt_long(argc, argv, options, long_options, NULL);
        switch(result){
            case 'x':
                x_flag = 1;
                break;
            case 'o':
                o_flag = 1;
                break;
            case 't': // default
                t_flag = 1;
                break;
            case 'n':
                top_flag = 1;
                top_arg = optarg;
                break;
            case 'd':
                order_flag = 1;
                order_arg = optarg;
                break;
            case 'e':
                enumurate_flag = 0;
                enumurate_arg = optarg;
                break;
            case 'v':
                verbose_flag = 1;
                break;
            case 'h':
                help_flag = 1;
                fprintf(stdout, "mycat [-t(text)|-x(hex)|-o(octal)] [-n or --top < number >, default: 10] [-d or --order < ascending >=0 | descending order <0 >, default: ascending] [-e or --enumurate < enumurate >=0 | not enumurate <0 >, default: not enumurate] [files]");
                break;
            case '?':
                // parsing error check
                if(optopt != 0)
                    fprintf(stderr, "invalid switch -%c\n", optopt);
                else if(optopt == 'n') // --top
                    fprintf(stderr, "-n or --top option without argument\n");
                else if(optopt == 'd') // --top
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
    if(optind == argc){
        // argc and optind only equal to 1 only if nothing specified
        fprintf(stderr, "At least one argument must be specified\n");
        err_flag = 1;
        //exit(EXIT_FAILURE);
    }

    // exit according to error check
    if(err_flag!= 0){
        exit(EXIT_FAILURE);
    }

    // set defaults
    if(top_flag){
        // default nline value
        nline = top_arg != NULL ? 
        (int)strtol(top_arg, NULL, 10) :
        DEFAULT_LINE;
    }
    if(order_flag){
        // default order value
        order = order_arg != NULL ? 
        (int)strtol(order_arg, NULL, 10) :
        DEFAULT_ORDER;
    }
    if(enumurate_flag){
        // default not enumurate
        order = order_arg != NULL ? 
        (int)strtol(enumurate_arg, NULL, 10) :
        ENUMERATE;
    }

    // process according to flags
    if(x_flag + o_flag + t_flag == 0){
        // non of them specified. default = text(t_flag)
        t_flag = 1;
    }

    for(index = optind; index < argc; ++index){
        // open files if file couldn't open continue to next file
        char* filename = argv[index];
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
        if(order_flag){
            if(t_flag)
                result = print_text(fp, nline);
            else if(x_flag)
                result = print_hex_octal(fp, nline, PRINT_HEX);
            else if(o_flag)
                result = print_hex_octal(fp, nline, PRINT_OCTAL);
            else
                result = print_text_last(fp, nline);
        }
        else{
            if(t_flag)
                result = print_text_last(fp, nline);
            else if(x_flag)
                result = print_hex_octal_last(fp, nline, PRINT_HEX);
            else if(o_flag)
                result = print_hex_octal_last(fp, nline, PRINT_OCTAL);
            else
                result = print_text_last(fp, nline);
        }

        if(index != argc -1)
            putchar('\n');
        // read error
        if(!result)
            fprintf(stderr, "cannot read the file %s\n", filename);

        fclose(fp);
    }
    
    /*
    // arguments without options. they are filenames
    if(optind != argc){
        puts("arguments without options: ");
    }
    */


    exit(EXIT_SUCCESS);
}


int print_text(FILE *fp, const int nline){
    // nline == -1 => print all file
    int ch=0;
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    int read_until_byte=nline;
    if(read_until_byte<0)
        read_until_byte = file_size - nline;

    if(read_until_byte == -1){
        // print all file
        while((ch = fgetc(fp)) != EOF){
            putchar(ch);
        }
    }
    else{
        for(int count = 0; ((ch = fgetc(fp)) != EOF) && count < read_until_byte; ++count){
            putchar(ch);
        }
    }

    return !ferror(fp);
}

int print_hex_octal(FILE* fp, const int nline, int hexflag){
    // nline == -1 => print all file
    int ch=0, line_mod=0, index=0;
    const char *off_str, *ch_str;

    off_str = hexflag ? "%07X" : "%012o";
    ch_str = hexflag? "%02X%c" : "%03o%c";

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    int read_until_byte=nline;
    if(read_until_byte<0)
        read_until_byte = file_size - nline;

    if(read_until_byte == -1){
        // print all file
        for(index = 0; (ch = fgetc(fp))!=EOF; ++index){
            line_mod = index % HEX_OCTAL_LINE_LENGHT;
            if(line_mod == 0)
                printf(off_str, index);
            printf(ch_str, ch, line_mod == HEX_OCTAL_LINE_LENGHT - 1 ? '\n': ' ');
        }
    }
    else{
        int count = 0;
        for(index = 0; (ch = fgetc(fp)) != EOF && count < read_until_byte; ++index){
            line_mod = index % HEX_OCTAL_LINE_LENGHT;
            if(line_mod == 0)
                printf(off_str, index);
            printf(ch_str, ch, line_mod == HEX_OCTAL_LINE_LENGHT - 1 ? '\n': ' ');

            if(ch=='\n')
                ++count;
        }
    }

    line_mod = index % HEX_OCTAL_LINE_LENGHT;
    if(line_mod != 0)
        putchar('\n');

    return !ferror(fp);
}


int print_text_last(FILE *fp, const int nline){
    // nline == -1 => print all file
    int ch=0;
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    int read_until_byte=nline;
    if(read_until_byte<0)
        read_until_byte = file_size - nline;

    if(read_until_byte == -1){
        // print all file
        while((ch = fgetc(fp)) != EOF){
            putchar(ch);
        }
    }
    else{
        for(int count = 0; ((ch = fgetc(fp)) != EOF) && count < read_until_byte; ++count){
            putchar(ch);
        }
    }

    return !ferror(fp);
}

int print_hex_octal_last(FILE* fp, const int nline, int hexflag){
    // nline == -1 => print all file
    int ch=0, line_mod=0, index=0;
    const char *off_str, *ch_str;

    off_str = hexflag ? "%07X" : "%012o";
    ch_str = hexflag? "%02X%c" : "%03o%c";

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    int read_until_byte=nline;
    if(read_until_byte<0)
        read_until_byte = file_size - nline;

    if(read_until_byte == -1){
        // print all file
        for(index = 0; (ch = fgetc(fp))!=EOF; ++index){
            line_mod = index % HEX_OCTAL_LINE_LENGHT;
            if(line_mod == 0)
                printf(off_str, index);
            printf(ch_str, ch, line_mod == HEX_OCTAL_LINE_LENGHT - 1 ? '\n': ' ');
        }
    }
    else{
        int count = 0;
        for(index = 0; (ch = fgetc(fp)) != EOF && count < read_until_byte; ++index){
            line_mod = index % HEX_OCTAL_LINE_LENGHT;
            if(line_mod == 0)
                printf(off_str, index);
            printf(ch_str, ch, line_mod == HEX_OCTAL_LINE_LENGHT - 1 ? '\n': ' ');

            if(ch=='\n')
                ++count;
        }
    }

    line_mod = index % HEX_OCTAL_LINE_LENGHT;
    if(line_mod != 0)
        putchar('\n');

    return !ferror(fp);
}
